#include "pali.hpp"

#include <cassert>

#include "nimi_wawa.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace ilo {
    /**
     * @brief li pona e pana ijo tawa nimi wawa pali.
     */
    struct SonaPali {
        const std::string& lonLipu;

        std::list<Ijo>&           ijoKipisi;
        std::list<Ijo>::iterator& alasaIjo;

        bool liLipuPona = true;
    };



    /**
     * @return poki nimi sin tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi pi ijo pi tenpo ni li POKI_NIMI. 
     */
    std::shared_ptr<KasiPiPokiNimi> paliEPokiNimi(SonaPali& sonaPali) {
        auto kasiPiPokiNimi = std::make_shared<KasiPiPokiNimi>();

        kasiPiPokiNimi->nimi.swap(sonaPali.alasaIjo->ijo);
        sonaPali.alasaIjo++;

        return kasiPiPokiNimi;
    }

    /**
     * @return poki sin tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi pi ijo pi tenpo ni li POKI. 
     */
    std::shared_ptr<KasiPoki> paliEPoki(SonaPali& sonaPali) {
        auto kasiPiPoki = std::make_shared<KasiPoki>();

        kasiPiPoki->nimiPoki.swap(sonaPali.alasaIjo->ijo);
        sonaPali.alasaIjo++;

        return kasiPiPoki;
    }

    /**
     * @return nimi wawa sin tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi pi ijo pi tenpo ni li NIMI_WAWA.
     */
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

        // ijo lon sinpin pi nimi wawa li wile open pi poki pi ijo pi nimi wawa. ilo kipisi li pona 
        //      la ni li ike lon tenpo ala.
        sonaPali.alasaIjo++;
        assert( sonaPali.alasaIjo != sonaPali.ijoKipisi.end()
             && sonaPali.alasaIjo->nimiIjo == NimiIjo::POKI_PI_IJO_PI_NIMI_WAWA 
             && sonaPali.alasaIjo->ijo == "("
             && "ijo lon sinpin pi nimi wawa li wile open pi ijo 'POKI_PI_IJO_PI_NIMI_WAWA'");

        for (sonaPali.alasaIjo++; sonaPali.alasaIjo != sonaPali.ijoKipisi.end();)
            switch (sonaPali.alasaIjo->nimiIjo) {
                case NimiIjo::NIMI_WAWA:
                    kasiPiNimiWawa->ijoPiNimiWawa.push_back(
                            std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali)));

                    // li pini pali e linja ni tan ni: ni li ike la ike sona sin li ken ala kama tan linja.
                    if (kasiPiNimiWawa->ijoPiNimiWawa.back() == nullptr)
                        return nullptr;

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
                    // ilo kipisi li pona la ni li ken ala tan ni: ona li kiwen e ni: sitelen '(' li 
                    //      ken lon sinpin pi nimi wawa taso.
                    assert( sonaPali.alasaIjo->ijo == ")" 
                         && "ijo 'POKI_PI_IJO_PI_NIMI_WAWA' lon pini poki li wile ')'!");
                    sonaPali.alasaIjo++;

                    goto liPini;

                case NimiIjo::LINJA_SIN:
                    goto liJoAlaEPini;

                default:
                    assert(false && "pali e nimi wawa la li kama jo e ijo pi wile ala!");
            }
    
        // sin la li alasa e pini lipu la li kama lon ni.
    liJoAlaEPini:
        kepeken::tokiEIke({ sonaPali.lonLipu
                          , sonaPali.alasaIjo->lonIjo
                          , ante_toki::nimiTawaJan("ike.pali.nimi_wawa.li_jo_ala_e_pini")});
        
        sonaPali.liLipuPona = false;
        return nullptr;

    liPini:
        // li kin e ni: nimi wawa li jo e nanpa ijo sama anu suli tawa nanpa lili lili pi ijo wile pi nimi 
        //      wawa.
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

        // li kin e ni: nimi wawa li jo e nanpa ijo sama anu lili tawa nanpa suli suli pi ijo wile pi nimi 
        //      wawa.
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

    /**
     * @return pana sin lon poki tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi lon sinpin pi ijo pi tenpo ni li PANA_LON_POKI.
     */
    std::shared_ptr<KasiPiPanaLonPoki> paliEPanaLonPoki(SonaPali& sonaPali) {
        auto kasiPiPanaLonPoki = std::make_shared<KasiPiPanaLonPoki>();

        // ijo wan pi pana lon poki li wile poki.
        if (sonaPali.alasaIjo->nimiIjo != NimiIjo::POKI) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::nimiTawaJan("ike.pali.poki_nanpa.nimi_poki_li_wile")});
            
            sonaPali.liLipuPona = false;
            return nullptr;
        }

        kasiPiPanaLonPoki->nimiPoki.swap(sonaPali.alasaIjo->ijo);

        // ijo tu sin li wile: sitelen '=' en ijo ante.
        for (; sonaPali.alasaIjo != sonaPali.ijoKipisi.end(); sonaPali.alasaIjo++);
        if ( sonaPali.alasaIjo == sonaPali.ijoKipisi.end() 
          || sonaPali.alasaIjo->nimiIjo == NimiIjo::LINJA_SIN) {
            // li ken ala toki e lon pi ijo ala.
            if (sonaPali.alasaIjo == sonaPali.ijoKipisi.end())
                sonaPali.alasaIjo--;

            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::nimiTawaJan("ike.pali.poki_nanpa.ijo_tawa_poki_li_wile")});
            
            sonaPali.liLipuPona = false;
            return nullptr;
        }

        // nimi ijo li lon ala nimi "case" la li wile ala tan ni: ona li ken ala lon sinpin pi pana lon poki.
        switch (sonaPali.alasaIjo->nimiIjo) {
            case NimiIjo::NIMI_WAWA:
                kasiPiPanaLonPoki->ijoPana = std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali));

                // li pini pali e linja ni tan ni: ni li ike la ike sona sin li ken ala kama tan linja.
                if (kasiPiPanaLonPoki->ijoPana == nullptr)
                    return nullptr;

                break;  

            case NimiIjo::POKI:
                kasiPiPanaLonPoki->ijoPana = std::static_pointer_cast<KasiLipu>(paliEPoki(sonaPali));
                break;  

            case NimiIjo::POKI_NIMI:
                kasiPiPanaLonPoki->ijoPana = std::static_pointer_cast<KasiLipu>(paliEPokiNimi(sonaPali));
                break;  

            default:
                kepeken::tokiEIke({ sonaPali.lonLipu
                                  , sonaPali.alasaIjo->lonIjo
                                  , ante_toki::nimiTawaJan("ike.pali.poki_nanpa.ijo_ike_tawa_poki")});
            
                sonaPali.liLipuPona = false;
                return nullptr;
        }

        sonaPali.alasaIjo++;
        return kasiPiPanaLonPoki;
    }

    KasiOpen pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu) {
        KasiOpen openKasi;
        
        auto alasaIjo = ijoKipisi.begin();
        SonaPali sonaPali = {lonLipu, ijoKipisi, alasaIjo};

        while (alasaIjo != ijoKipisi.end()) {
            while (alasaIjo != ijoKipisi.end() && alasaIjo->nimiIjo == NimiIjo::LINJA_SIN)
                alasaIjo++;
            if (alasaIjo != ijoKipisi.end())
                break;


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


            // linja li jo ala e nimi wawa anu pana lon poki la mi ken pali ala e ona.
            for (; alasaIjo != ijoKipisi.end(); alasaIjo++)
                if (sonaPali.alasaIjo->nimiIjo == NimiIjo::LINJA_SIN) 
                    break;
        }

        if (!sonaPali.liLipuPona)
            throw std::runtime_error("lipu wawa ike!");

        return openKasi;
    }
}