#include "pali.hpp"

#include <cassert>

#include "nimi_wawa.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace ilo {
    struct SonaPali {
        std::list<Ijo>&           ijoKipisi;
        const std::string&        lonLipu;
        std::list<Ijo>::iterator& alasaIjo;

        bool liLipuPona = true;
    };

    std::shared_ptr<KasiPiPokiNimi> paliEPokiNimi(SonaPali& sonaPali) {
        auto kasiPiPokiNimi = std::make_shared<KasiPiPokiNimi>();

        kasiPiPokiNimi->nimi.swap(sonaPali.alasaIjo->ijo);
        sonaPali.alasaIjo++;

        return kasiPiPokiNimi;
    }

    std::shared_ptr<KasiPoki> paliEPoki(SonaPali& sonaPali) {
        auto kasiPiPoki = std::make_shared<KasiPoki>();

        kasiPiPoki->nimiPoki.swap(sonaPali.alasaIjo->ijo);
        sonaPali.alasaIjo++;

        return kasiPiPoki;
    }

    std::shared_ptr<KasiPiNimiWawa> paliENimiWawa(SonaPali& sonaPali) {
        auto kasiPiNimiWawa = std::make_shared<KasiPiNimiWawa>();

        try {
            kasiPiNimiWawa->nimiWawa = &nimiPiNimiWawaTawaNimiWawa.at(sonaPali.alasaIjo->ijo);
        
        } catch (const std::out_of_range& liLonAla) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::anteENimi( ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nimi_pi_sona_ala")
                                                    , "%s", sonaPali.alasaIjo->ijo)});
            sonaPali.liLipuPona = false;
            return nullptr;
        }

        sonaPali.alasaIjo++;
        assert( sonaPali.alasaIjo->nimiIjo == NimiIjo::POKI_PI_IJO_PI_NIMI_WAWA 
             && sonaPali.alasaIjo->ijo == "("
             && "ijo lon sinpin pi nimi wawa li wile open pi ijo 'POKI_PI_IJO_PI_NIMI_WAWA'");

        for (sonaPali.alasaIjo++; sonaPali.alasaIjo != sonaPali.ijoKipisi.end();)
            switch (sonaPali.alasaIjo->nimiIjo) {
                case NimiIjo::NIMI_WAWA:
                    kasiPiNimiWawa->ijoPiNimiWawa.push_back(
                            std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali)));
                    break;

                case NimiIjo::POKI:
                    kasiPiNimiWawa->ijoPiNimiWawa.push_back(
                            std::static_pointer_cast<KasiLipu>(paliEPoki(sonaPali)));
                    break; 

                case NimiIjo::POKI_NIMI:
                    kasiPiNimiWawa->ijoPiNimiWawa.push_back(
                            std::static_pointer_cast<KasiLipu>(paliEPokiNimi(sonaPali)));
                    break;

                case NimiIjo::POKI_PI_IJO_PI_NIMI_WAWA:
                    assert( sonaPali.alasaIjo->ijo == ")" 
                         && "ijo 'POKI_PI_IJO_PI_NIMI_WAWA' lon pini poki li wile ')'!");
                    sonaPali.alasaIjo++;

                    goto liPini;

                case NimiIjo::LINJA_SIN:
                    goto liJoAlaEPini;

                default:
                    assert(false && "pali e nimi wawa la li kama jo e ijo pi wile ala!");
            }
    
    liJoAlaEPini:
        kepeken::tokiEIke({ sonaPali.lonLipu
                          , sonaPali.alasaIjo->lonIjo
                          , ante_toki::nimiTawaJan("ike.pali.nimi_wawa.li_jo_ala_e_pini")});
        sonaPali.liLipuPona = false;

        return nullptr;

    liPini:
        if ( kasiPiNimiWawa->nimiWawa->nanpaLiliPiIjoWile != -1 
          && kasiPiNimiWawa->ijoPiNimiWawa.size() < kasiPiNimiWawa->nimiWawa->nanpaLiliPiIjoWile) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::anteENimi(ante_toki::anteENimi( 
                                        ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nanpa_ijo_lili")
                                        , "%s", sonaPali.alasaIjo->ijo)
                                        , "%d", std::to_string(kasiPiNimiWawa->nimiWawa->nanpaLiliPiIjoWile))});
            sonaPali.liLipuPona = false;

            return nullptr;
        }

        if ( kasiPiNimiWawa->nimiWawa->nanpaSuliPiIjoWile != -1 
          && kasiPiNimiWawa->ijoPiNimiWawa.size() > kasiPiNimiWawa->nimiWawa->nanpaSuliPiIjoWile) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::anteENimi(ante_toki::anteENimi( 
                                        ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nanpa_ijo_suli")
                                        , "%s", sonaPali.alasaIjo->ijo)
                                        , "%d", std::to_string(kasiPiNimiWawa->nimiWawa->nanpaSuliPiIjoWile))});
            sonaPali.liLipuPona = false;

            return nullptr;
        }

        return kasiPiNimiWawa;
    }

    std::shared_ptr<KasiPiPanaLonPoki> paliEPanaLonPoki(SonaPali& sonaPali) {
        auto kasiPiPanaLonPoki = std::make_shared<KasiPiPanaLonPoki>();

        kasiPiPanaLonPoki->nimiPoki.swap(sonaPali.alasaIjo->ijo);
        sonaPali.alasaIjo++;

        switch (sonaPali.alasaIjo->nimiIjo) {
            case NimiIjo::NIMI_WAWA:
                kasiPiPanaLonPoki->ijoPana = std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali));
                break;  

            case NimiIjo::POKI:
                kasiPiPanaLonPoki->ijoPana = std::static_pointer_cast<KasiLipu>(paliEPoki(sonaPali));
                break;  

            case NimiIjo::POKI_NIMI:
                kasiPiPanaLonPoki->ijoPana = std::static_pointer_cast<KasiLipu>(paliEPokiNimi(sonaPali));
                break;  

            default:
                assert(false && "pali e pana lon poki la li kama jo e ijo pi wile ala!");
        }

        sonaPali.alasaIjo++;
        return kasiPiPanaLonPoki;
    }

    KasiLipu pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu) {
        KasiOpen openKasi;
        
        auto alasaIjo = ijoKipisi.begin();
        SonaPali sonaPali = {ijoKipisi, lonLipu, alasaIjo};

        while (alasaIjo != ijoKipisi.end()) {
            while (alasaIjo->nimiIjo == NimiIjo::LINJA_SIN && alasaIjo != ijoKipisi.end())
                alasaIjo++;

            if (alasaIjo->nimiIjo == NimiIjo::NIMI_WAWA) {
                openKasi.kasiLonAnpa.push_back(
                        std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali)));
                continue;
            }

            auto ijoLonSinpin = alasaIjo;
            ijoLonSinpin++;

            if (ijoLonSinpin->nimiIjo == NimiIjo::PANA_LON_POKI) {
                openKasi.kasiLonAnpa.push_back(
                        std::static_pointer_cast<KasiLipu>(paliEPanaLonPoki(sonaPali)));
                continue;
            }
        }

        return openKasi;
    }
}