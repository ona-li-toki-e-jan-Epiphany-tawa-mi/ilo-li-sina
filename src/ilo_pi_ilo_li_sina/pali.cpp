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

    std::shared_ptr<KasiPiNimiWawa> paliENimiWawa(SonaPali& sonaPali) {
        auto kasiPiNimiWawa = std::make_shared<KasiPiNimiWawa>();

        try {
            kasiPiNimiWawa->nimiWawa = nimiPiNimiWawaTawaNimiWawa.at(sonaPali.alasaIjo->ijo);
        
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

        for (sonaPali.alasaIjo++; sonaPali.alasaIjo != sonaPali.ijoKipisi.end(); sonaPali.alasaIjo++)
            switch (sonaPali.alasaIjo->nimiIjo) {
                case NimiIjo::NIMI_WAWA:
                    kasiPiNimiWawa->ijoPiNimiWawa.push_back(
                            std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali)));
                    break;

                case NimiIjo::POKI:
                    break; // TODO

                case NimiIjo::POKI_NIMI:
                    break; // TODO

                case NimiIjo::POKI_PI_IJO_PI_NIMI_WAWA:
                    assert( sonaPali.alasaIjo->ijo == ")" 
                         && "ijo 'POKI_PI_IJO_PI_NIMI_WAWA' lon pini poki li wile ')'!");
                    goto liPini;

                case NimiIjo::LINJA_SIN:
                    goto liJoAlaEPini;
            }
    
    liJoAlaEPini:
        kepeken::tokiEIke({ sonaPali.lonLipu
                          , sonaPali.alasaIjo->lonIjo
                          , ante_toki::nimiTawaJan("ike.pali.nimi_wawa.li_jo_ala_e_pini")});
        sonaPali.liLipuPona = false;

        return nullptr;

    liPini:
        if ( kasiPiNimiWawa->nimiWawa.nanpaLiliPiIjoWile != -1 
          && kasiPiNimiWawa->ijoPiNimiWawa.size() < kasiPiNimiWawa->nimiWawa.nanpaLiliPiIjoWile) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::anteENimi(ante_toki::anteENimi( 
                                        ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nanpa_ijo_lili")
                                        , "%s", sonaPali.alasaIjo->ijo)
                                        , "%d", std::to_string(kasiPiNimiWawa->nimiWawa.nanpaLiliPiIjoWile))});
            sonaPali.liLipuPona = false;

            return nullptr;
        }

        if ( kasiPiNimiWawa->nimiWawa.nanpaSuliPiIjoWile != -1 
          && kasiPiNimiWawa->ijoPiNimiWawa.size() < kasiPiNimiWawa->nimiWawa.nanpaLiliPiIjoWile) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::anteENimi(ante_toki::anteENimi( 
                                        ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nanpa_ijo_suli")
                                        , "%s", sonaPali.alasaIjo->ijo)
                                        , "%d", std::to_string(kasiPiNimiWawa->nimiWawa.nanpaSuliPiIjoWile))});
            sonaPali.liLipuPona = false;

            return nullptr;
        }

        return kasiPiNimiWawa
    }

    std::shared_ptr<KasiPiNimiWawa> paliEPanaLonPoki(SonaPali& sonaPali) {}// TODO

    KasiLipu pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu) {
        KasiOpen openKasi;
        
        auto alasaIjo = ijoKipisi.begin();
        SonaPali sonaPali = {ijoKipisi, lonLipu, alasaIjo};

        for (; alasaIjo != ijoKipisi.end(); alasaIjo++) {
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