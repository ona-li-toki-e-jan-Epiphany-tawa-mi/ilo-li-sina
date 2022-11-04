#include "pali.hpp"

#include <cassert>

#include "nimi_wawa.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace ilo {
    KasiOpen::KasiOpen() {
        this->lonKasi = {0, 0};
    }

    KasiOpen* KasiOpen::paliSama() const {
        return new KasiOpen(*this);
    }

    std::string KasiOpen::nimiPiNimiKasi() const {
        return "";
    }

    KasiOpen::KasiOpen(KasiOpen&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiOpen& KasiOpen::operator=(KasiOpen&& ante) noexcept {
        if (this != &ante)
            this->kasiLonAnpa = std::move(ante.kasiLonAnpa);

        return *this;
    }

    KasiOpen::KasiOpen(const KasiOpen& ante) {
        for (const auto& kasi : ante.kasiLonAnpa)
            this->kasiLonAnpa.push_back(
                    std::shared_ptr<KasiLipu>(kasi->paliSama()));
    }


    KasiPiPokiNimi* KasiPiPokiNimi::paliSama() const {
        return new KasiPiPokiNimi(*this);
    }

    KasiPiPokiNimi::KasiPiPokiNimi(KasiPiPokiNimi&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPiPokiNimi& KasiPiPokiNimi::operator=(KasiPiPokiNimi&& ante) noexcept {
        if (this != &ante)
            this->nimi = std::move(ante.nimi);

        return *this;
    }
    
    std::string KasiPiPokiNimi::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.poki_nimi";
    }


    KasiPoki* KasiPoki::paliSama() const {
        return new KasiPoki(*this);
    }

    KasiPoki::KasiPoki(KasiPoki&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPoki& KasiPoki::operator=(KasiPoki&& ante) noexcept {
        if (this != &ante)
            this->nimiPoki = std::move(ante.nimiPoki);

        return *this;
    }

    std::string KasiPoki::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.kama_jo_tan_poki";
    }


    KasiPiNimiWawa::KasiPiNimiWawa(const NimiWawa* nimiWawa) 
        : nimiWawa(nimiWawa) {}

    KasiPiNimiWawa* KasiPiNimiWawa::paliSama() const {
        return new KasiPiNimiWawa(*this);
    }

    KasiPiNimiWawa::KasiPiNimiWawa(KasiPiNimiWawa&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPiNimiWawa& KasiPiNimiWawa::operator=(KasiPiNimiWawa&& ante) noexcept {
        if (this != &ante) {
            this->nimiWawa = ante.nimiWawa;
            ante.nimiWawa = nullptr;

            this->ijoPiNimiWawa = std::move(ante.ijoPiNimiWawa);
        }

        return *this;
    }

    std::string KasiPiNimiWawa::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.nimi_wawa";
    }

    KasiPiNimiWawa::KasiPiNimiWawa(const KasiPiNimiWawa& ante) {
        this->nimiWawa = ante.nimiWawa;

        for (const auto& kasi : ante.ijoPiNimiWawa)
            this->ijoPiNimiWawa.push_back(
                    std::shared_ptr<KasiLipu>(kasi->paliSama()));
    }


    KasiPiPanaLonPoki* KasiPiPanaLonPoki::paliSama() const {
        return new KasiPiPanaLonPoki(*this);
    }

    KasiPiPanaLonPoki::KasiPiPanaLonPoki(KasiPiPanaLonPoki&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPiPanaLonPoki& KasiPiPanaLonPoki::operator=(KasiPiPanaLonPoki&& ante) noexcept {
        if (this != &ante) {
            this->nimiPoki = std::move(ante.nimiPoki);
            this->ijoPana  = std::move(ante.ijoPana);
        }

        return *this;
    }

    std::string KasiPiPanaLonPoki::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.pana_lon_poki";
    }

    KasiPiPanaLonPoki::KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante) {
        this->nimiPoki = ante.nimiPoki;
        this->ijoPana  = std::shared_ptr<KasiLipu>(ante.ijoPana->paliSama());
    }



    /**
     * @brief li pona e pana ijo tawa nimi wawa pali.
     */
    struct SonaPali {
        const std::string& lonLipu;
        KasiOpen&          kasiOpen;

        std::list<Ijo>&           ijoKipisi;
        std::list<Ijo>::iterator& alasaIjo;

        std::unordered_map<std::string, std::shared_ptr<KasiLipu>>&                   lonPiNimiTawaTawa;
        std::list<const Ijo&>&                                                        nimiTawaTawaPiTenpoNi;
        std::list<std::pair<const std::string&, std::shared_ptr<KasiPiNimiWawaTawa>>> nimiTawaTawaTawaNimiWawaTawa;

        bool liLipuPona = true;
    };

    /**
     * @brief li tawa e alasa ijo lon linja sin.
     * @attention ike la o kepeken e ni tawa ni: ilo pali li ken awen toki e ike ante lon lipu.
     */
    void tawaLinjaSinLonSinpin(SonaPali& sonaPali) {
            for (; sonaPali.alasaIjo != sonaPali.ijoKipisi.cend(); sonaPali.alasaIjo++)
                if (sonaPali.alasaIjo->nimiIjo == NimiIjo::LINJA_SIN) 
                    break;
    }

    /**
     * @return poki nimi sin tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi pi ijo pi tenpo ni li POKI_NIMI. 
     */
    std::shared_ptr<KasiPiPokiNimi> paliEPokiNimi(SonaPali& sonaPali) {
        auto kasiPiPokiNimi = std::make_shared<KasiPiPokiNimi>();

        kasiPiPokiNimi->nimi = std::move(sonaPali.alasaIjo->ijo);
        kasiPiPokiNimi->lonKasi = sonaPali.alasaIjo->lonIjo;
        sonaPali.alasaIjo++;

        return kasiPiPokiNimi;
    }

    /**
     * @return poki sin tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi pi ijo pi tenpo ni li POKI. 
     */
    std::shared_ptr<KasiPoki> paliEPoki(SonaPali& sonaPali) {
        auto kasiPiPoki = std::make_shared<KasiPoki>();

        kasiPiPoki->nimiPoki = std::move(sonaPali.alasaIjo->ijo);
        kasiPiPoki->lonKasi = sonaPali.alasaIjo->lonIjo;
        sonaPali.alasaIjo++;

        return kasiPiPoki;
    }

    /**
     * @return nimi wawa sin tan lon pi tenpo ni lon poki pi lipu kipisi.
     * @attention o pali e ni lon monsi pi kepeken ni: nimi pi ijo pi tenpo ni li NIMI_WAWA.
     */
    std::shared_ptr<KasiPiNimiWawa> paliENimiWawa(SonaPali& sonaPali) {
        std::shared_ptr<KasiPiNimiWawa> kasiPiNimiWawa = nullptr;
        bool nimiWawaLiLon = false;
        bool liNimiWawaTawa = false;

        try {
            kasiPiNimiWawa = std::make_shared<KasiPiNimiWawa>(
                    &nimiTawaNimiWawa.at(sonaPali.alasaIjo->ijo));
            nimiWawaLiLon  = true;
        
        } catch (const std::out_of_range& liLonAla) {}

        try {
            kasiPiNimiWawa = std::make_shared<KasiPiNimiWawaTawa>(
                    &nimiTawaNimiWawa.at(sonaPali.alasaIjo->ijo));
            
            nimiWawaLiLon  = true;
            liNimiWawaTawa = true;

        } catch (const std::out_of_range& liLonAla) {}

        if (!nimiWawaLiLon) {
            kepeken::tokiEIke({ sonaPali.lonLipu
                              , sonaPali.alasaIjo->lonIjo
                              , ante_toki::anteENimi( ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nimi_pi_sona_ala")
                                                    , "%s", sonaPali.alasaIjo->ijo)});

            sonaPali.liLipuPona = false;
            return nullptr;
        }

        kasiPiNimiWawa->lonKasi  = sonaPali.alasaIjo->lonIjo;


        // ijo lon sinpin pi nimi wawa li wile open pi poki pi ijo pi nimi wawa. ilo kipisi li pona 
        //      la ni li ike lon tenpo ala.
        sonaPali.alasaIjo++;
        assert( sonaPali.alasaIjo != sonaPali.ijoKipisi.end()
             && sonaPali.alasaIjo->nimiIjo == NimiIjo::POKI_PI_IJO_PI_NIMI_WAWA 
             && sonaPali.alasaIjo->ijo == "("
             && "ijo lon sinpin pi nimi wawa li wile open pi ijo 'POKI_PI_IJO_PI_NIMI_WAWA'");

        // nimi wawa li tawa la ni li kama jo e nimi ona tawa tawa.
        if (liNimiWawaTawa) {
            sonaPali.alasaIjo++;
            if ( sonaPali.alasaIjo == sonaPali.ijoKipisi.end() 
                    || sonaPali.alasaIjo->nimiIjo != NimiIjo::POKI) {
                kepeken::tokiEIke({ sonaPali.lonLipu //TODO
                                , sonaPali.alasaIjo->lonIjo
                                , ante_toki::anteENimi( ante_toki::nimiTawaJan("ike.pali.nimi_wawa.nimi_pi_sona_ala")
                                                        , "%s", sonaPali.alasaIjo->ijo)});

                sonaPali.liLipuPona = false;
                return nullptr;
            }

            sonaPali.nimiTawaTawaTawaNimiWawaTawa.push_back({
                    sonaPali.alasaIjo->ijo
                  , std::static_pointer_cast<KasiPiNimiWawaTawa>(kasiPiNimiWawa)});
        }

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

        kasiPiPanaLonPoki->nimiPoki = std::move(sonaPali.alasaIjo->ijo);
        kasiPiPanaLonPoki->lonKasi = sonaPali.alasaIjo->lonIjo;

        // ijo tu sin li wile: sitelen '=' en ijo ante.
        for (int i = 0; i < 2; i++) sonaPali.alasaIjo++;
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

    /**
     * @brief poki nimiTawaTawaPiTenpoNi li kama jo e nimi tawa tawa mute. nimi wawa ona li kama la ni 
     *      li kepeken tawa ni: nimi tawa tawa li tawa nimi wawa.
     * @attention ilo pali li pali e linja la o kepeken e ni.
     */
    void wanEKasiENimiTawa(SonaPali& sonaPali) {
        if (sonaPali.nimiTawaTawaPiTenpoNi.empty())
            return;

        for (const auto& nimiTawaTawa : sonaPali.nimiTawaTawaPiTenpoNi)
            try {
                sonaPali.lonPiNimiTawaTawa.at(nimiTawaTawa.ijo);

                kepeken::tokiEIke({ sonaPali.lonLipu
                                  , nimiTawaTawa.lonIjo
                                  , ante_toki::anteENimi(ante_toki::anteENimi(ante_toki::anteENimi(
                                        ante_toki::nimiTawaJan("ike.pali.nimi_wawa.tawa.nimi_tawa_mute_mute")
                                      , "%s", nimiTawaTawa.ijo)
                                      , "%d", std::to_string(nimiTawaTawa.lonIjo.nanpaLinja))
                                      , "%d", std::to_string(nimiTawaTawa.lonIjo.nanpaSitelenLonLinja))});
                sonaPali.liLipuPona = false;

            } catch (const std::out_of_range& liLonAla) {
                sonaPali.lonPiNimiTawaTawa[nimiTawaTawa.ijo] = sonaPali.kasiOpen.kasiLonAnpa.back();
            }

        sonaPali.nimiTawaTawaPiTenpoNi.clear();
    }

    KasiOpen pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu) {
        KasiOpen openKasi;
        
        auto alasaIjo = ijoKipisi.begin();
        // li poki e kasi lon nimi tawa tawa tawa wan e ona e nimi wawa tawa.
        std::unordered_map<std::string, std::shared_ptr<KasiLipu>> lonPiNimiTawaTawa;
        // li poki e nimi tawa tawa tawa ni: kasi li ken kama jo e nimi tawa tawa ali lon sewi ona.
        std::list<const Ijo&> nimiTawaTawaPiTenpoNi;
        // li poki e nimi wawa tawa en nimi tawa tawa ona tawa wan e nimi wawa tawa e kasi lon nimi tawa 
        //      tawa ona. nimi pi poki ni li suli kin, a a a.
        std::list<std::pair<const std::string&, std::shared_ptr<KasiPiNimiWawaTawa>>> nimiTawaTawaTawaNimiWawaTawa;
        SonaPali sonaPali = {lonLipu, openKasi, ijoKipisi, alasaIjo, lonPiNimiTawaTawa, nimiTawaTawaPiTenpoNi, nimiTawaTawaTawaNimiWawaTawa};

        while (alasaIjo != ijoKipisi.end()) {
            while (alasaIjo != ijoKipisi.end() && alasaIjo->nimiIjo == NimiIjo::LINJA_SIN)
                alasaIjo++;
            if (alasaIjo == ijoKipisi.end())
                break;


            if (alasaIjo->nimiIjo == NimiIjo::NIMI_TAWA_TAWA) {
                nimiTawaTawaPiTenpoNi.push_back(*alasaIjo);
                alasaIjo++;

                if (alasaIjo == ijoKipisi.end())
                    break;
                // nimi tawa tawa li ken taso lon open linja, taso, ona mute li ken lon linja mute. ni
                //  la nimi tawa tawa pi pini ala lon kulupu nimi tawa tawa li wile taso lon linja.
                if (alasaIjo->nimiIjo == NimiIjo::LINJA_SIN)
                    continue;
            }


            if (alasaIjo->nimiIjo == NimiIjo::NIMI_WAWA) {
                openKasi.kasiLonAnpa.push_back(
                        std::static_pointer_cast<KasiLipu>(paliENimiWawa(sonaPali)));

                wanEKasiENimiTawa(sonaPali);

                // ike la li wile tawa linja sin tawa awen toki e ike lon linja ante.
                if (openKasi.kasiLonAnpa.back() == nullptr)
                    tawaLinjaSinLonSinpin(sonaPali);
                continue;
            }

            auto ijoLonSinpin = alasaIjo;
            ijoLonSinpin++;

            if (ijoLonSinpin->nimiIjo == NimiIjo::PANA_LON_POKI) {
                openKasi.kasiLonAnpa.push_back(
                        std::static_pointer_cast<KasiLipu>(paliEPanaLonPoki(sonaPali)));

                wanEKasiENimiTawa(sonaPali);

                // ike la li wile tawa linja sin tawa awen toki e ike lon linja ante.
                if (openKasi.kasiLonAnpa.back() == nullptr)
                    tawaLinjaSinLonSinpin(sonaPali);
                continue;
            }


            // linja li jo ala e nimi wawa anu pana lon poki la li suli ala. mi ken pali e ala li lukin
            //      e linja ante.
            tawaLinjaSinLonSinpin(sonaPali);
        }

        // li wan e nimi tawa tawa e nimi wawa tawa.
        for (auto [nimiTawaTawa, nimiWawaTawa] : nimiTawaTawaTawaNimiWawaTawa) {
            try {
                nimiWawaTawa->kasiTawaTawa = lonPiNimiTawaTawa.at(nimiTawaTawa);
            
            } catch (const std::out_of_range& liLonAla) {
                kepeken::tokiEIke({ sonaPali.lonLipu
                                  , sonaPali.alasaIjo->lonIjo
                                  , ante_toki::nimiTawaJan("ike.pali.nimi_wawa.tawa.nimi_tawa_pi_sona_ala")});
            
                sonaPali.liLipuPona = false;
            }
        }

        if (!sonaPali.liLipuPona)
            throw std::runtime_error("lipu wawa ike!");

        return openKasi;
    }



    /**
	 * @brief li toki e sitelen pi lukin ala lon open pi toki kasi.
	 * 
	 * @param lonInsaPiNanpaNi nanpa ni li nanpa sitelen tawa toki. kasi li lon insa pi kasi pi nanpa ni.
	 */
	void tokiEOpenPiTokiKasi(const unsigned int lonInsaPiNanpaNi) {
		static std::unordered_map<unsigned int, std::string> pokiPiTokiOpen;

		try {
			std::cout << pokiPiTokiOpen.at(lonInsaPiNanpaNi);
		
		} catch (const std::out_of_range liPokiAlaEOpenNi) {
			std::string openSin(lonInsaPiNanpaNi * 8, ' ');
			pokiPiTokiOpen[lonInsaPiNanpaNi] = openSin;
			std::cout << openSin;
		}
	}

	/**
	 * @brief li pana e kasi pi lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasi 				 kasi pi kasi suli tawa pana.
	 * @param lonInsaPiNanpaNi	 kasi li lon insa pi kasi pi nanpa ni.
	 * @param nanpaPiKasiLonSewi kasi li kasi pi nanpa ni lon poki pi lipu wawa anu lon kasi ni.
	 */
	void tokiEKasiPiKasiSuli(const KasiLipu* kasi, const unsigned int lonInsaPiNanpaNi, const size_t nanpaPiKasiLonSewi) {
		tokiEOpenPiTokiKasi(lonInsaPiNanpaNi);

		auto kasiPiPanaLonPoki = dynamic_cast<const KasiPiPanaLonPoki*>(kasi);
        if (kasiPiPanaLonPoki != nullptr) {
            std::cout << ante_toki::nimiTawaJan(kasiPiPanaLonPoki->nimiPiNimiKasi()) << "=\"" 
                      << kasiPiPanaLonPoki->nimiPoki << "\":\n";
            tokiEKasiPiKasiSuli(kasiPiPanaLonPoki->ijoPana.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);

            return;
        }

		auto kasiPoki = dynamic_cast<const KasiPoki*>(kasi);
        if (kasiPoki != nullptr) {
			std::cout << ante_toki::nimiTawaJan(kasiPoki->nimiPiNimiKasi()) << "=\"" 
                      << kasiPoki->nimiPoki << "\"\n";

			return;
		}

		auto kasiPiPokiNimi = dynamic_cast<const KasiPiPokiNimi*>(kasi);
        if (kasiPiPokiNimi != nullptr) {
			std::cout << ante_toki::nimiTawaJan(kasiPiPokiNimi->nimiPiNimiKasi()) << "=\"";
			const std::unordered_map<char, char>& nimiTanSitelenNasa = sitelenNasaTawaNimi();
				
            for (const char sitelen : kasiPiPokiNimi->nimi)
                try {
                    const char sitelenPiNasaAla = nimiTanSitelenNasa.at(sitelen);
                    std::cout << '\\' << sitelenPiNasaAla;

                } catch (const std::out_of_range& liSitelenNasaAla) {
                    std::cout << sitelen;
                }

            std::cout << "\"\n";

			return;
		}

		auto kasiPiNimiWawa = dynamic_cast<const KasiPiNimiWawa*>(kasi);
        if (kasiPiNimiWawa != nullptr) {
            try {
                std::cout << ante_toki::nimiTawaJan(kasiPiNimiWawa->nimiPiNimiKasi()) << "=\"" 
                          << nimiWawaKiwenTawaNimi().at(kasiPiNimiWawa->nimiWawa->nimiWawaKiwen) << '"';
            
            } catch (const std::out_of_range& nimiWawaLiLonAla) {
                assert(false && "pali la li kama jo e lon nullptr anu lon tawa nimi wawa pi sona ala");
            }

            if (kasiPiNimiWawa->ijoPiNimiWawa.size() > 0) {
                std::cout << ":\n";

                for (const std::shared_ptr<KasiLipu>& ijo : kasiPiNimiWawa->ijoPiNimiWawa)
                    tokiEKasiPiKasiSuli(ijo.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);
            
            } else
                std::cout << '\n';

            return;
        }

			
		/*const auto kasiPiNimiTawa = static_cast<const KasiPiNimiTawa*>(kasi);
				std::cout << kasi->kamaJoENimiPiNimiKasi() << "=\"" << kasiPiNimiTawa->kamaJoENimiPiNimiTawa() << "\"\n";
			
				break;
			}

			case NimiKasi::TAWA: {
				const auto kasiTawa = static_cast<const KasiTawa*>(kasi);
				assert(dynamic_cast<const KasiPiNimiTawa*>(pokiTawaLipuWawa.at(kasiTawa->linjaTawaTawa).get()) != nullptr && "kasi li wile nimi tawa. taso, ona li ala ni");
				const auto kasiPiNimiTawa = static_cast<const KasiPiNimiTawa*>(pokiTawaLipuWawa.at(kasiTawa->linjaTawaTawa).get());

				std::cout << kasiTawa->kamaJoENimiPiNimiKasi() << "=\"" << kasiTawa->kamaJoENimiPiKasiTawa() 
					<< "\", \"" << kasiPiNimiTawa->kamaJoENimiPiNimiTawa() << "\" - "
					<< ante_toki::anteENimi(ante_toki::kamaJoENimiTawaJan("toki.nanpa_linja"),
						"%d",
						std::to_string(kasiPiNimiTawa->kamaJoELonKasi().nanpaLinja));
					

				if (kasiTawa->kamaJoEIjoTawaTawa().size() > 0) {//TODO
					std::cout << ":\n";

					for (const auto& ijo : kasiTawa->kamaJoEIjoTawaTawa())
						tokiEKasiPiKasiSuli(pokiTawaLipuWawa, ijo.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);
				
				} else
					std::cout << "\n";

				break;
			}*/

		
		std::cout << ante_toki::nimiTawaJan(kasi->nimiPiNimiKasi()) << '\n'; // TODO
	}

	void tokiELipuPali(const KasiOpen& kasiOpen, const std::string& lonLipu) {
		const std::string sinpin(lonLipu.size() + 2, '-');

		std::cout << '/'  << sinpin  << "\\\n"
			      << "| " << lonLipu << " |\n"
			      << '\\' << sinpin  << "/\n";

		if (!kasiOpen.kasiLonAnpa.empty()) {
			for (auto alasaKasi = kasiOpen.kasiLonAnpa.cbegin()
                    ; alasaKasi != kasiOpen.kasiLonAnpa.cend()
                    ; alasaKasi++) {
				const KasiLipu *const kasi = alasaKasi->get();

				std::cout << ante_toki::anteENimi( ante_toki::nimiTawaJan("toki.nanpa_linja")
                                                 , "%d", std::to_string(kasi->lonKasi.nanpaLinja)) 
					      << ":\n";
				tokiEKasiPiKasiSuli(kasi, 1, kasi->lonKasi.nanpaLinja);
			}

		} else
			std::cout << '\n' << ante_toki::nimiTawaJan("toki.li_jo_e_ala") << "\n\n";

		std::cout << '\\' << sinpin << "/\n";
	}
}