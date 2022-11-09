#include "lawa.hpp"

#include <array>
#include <cstring>
#include <cassert>

#include "../../ijo_kepeken/ike.hpp"
#include "../../ante_toki/ante_toki.hpp"

namespace ilo {
    void KasiOpen::lawa(SonaLawa& sonaLawa) const noexcept(false) {
        lawaELipu(*this, sonaLawa.pokiAli, sonaLawa.lonLipu);
        sonaLawa.pokiPali.push("");
    }

    void KasiPini::lawa(SonaLawa& sonaLawa) const {
        sonaLawa.pokiPali.push("");
    }

    void KasiPiPokiNimi::lawa(SonaLawa& sonaLawa) const {
        sonaLawa.pokiPali.push(this->nimi);
    }

    void KasiPoki::lawa(SonaLawa& sonaLawa) const noexcept(false) {
        try {
            sonaLawa.pokiPali.push(sonaLawa.pokiAli.at(this->nimiPoki));

        } catch (const std::out_of_range& liLonAla) {
            kepeken::tokiEIke({ sonaLawa.lonLipu
                              , this->lonKasi
                              , ante_toki::anteENimi(ante_toki::nimiTawaJan(
                                        "ike.lawa.poki_nimi.li_lukin_kama_jo_tan_poki_pi_sona_ala")
                                      , "%s", this->nimiPoki)});

            throw std::runtime_error("li kama jo e nimi tan poki la li lukin kepeken e poki pi lon ala!");
        }
    }

    void KasiPiNimiWawa::lawa(SonaLawa& sonaLawa) const noexcept(false) {
#ifndef NDEBUG
        size_t suliPiPokiPali = sonaLawa.pokiPali.size(); // li lon tawa assert() taso.
#endif

        // li alasa e ijo tan pini tawa open tawa ni: ni li pona e pali pi nimi wawa sin pi toki 
        //      "ilo li sina".
        for (auto alasaIjo = this->ijoPiNimiWawa.rbegin() 
                ; alasaIjo != this->ijoPiNimiWawa.rend()
                ; alasaIjo++)
            (*alasaIjo)->lawa(sonaLawa);

        assert( sonaLawa.pokiPali.size() - suliPiPokiPali == this->ijoPiNimiWawa.size()
             && "li lawa e ijo pi nimi wawa la nanpa ijo ike lon poki pali!");


#ifndef NDEBUG
        suliPiPokiPali = sonaLawa.pokiPali.size(); // li lon tawa assert() taso.
#endif

        sonaLawa.lonPiKasiPiTenpoNi = &this->lonKasi;
        this->nimiWawa->lawa(sonaLawa, this->ijoPiNimiWawa.size());

        assert( suliPiPokiPali - sonaLawa.pokiPali.size() == this->ijoPiNimiWawa.size() - 1
             && "li lawa e nimi wawa la nanpa ijo ike lon poki pali!");
    }

    void KasiPiNimiWawaTawa::lawa(SonaLawa& sonaLawa) const noexcept(false) {
#ifndef NDEBUG
        size_t suliPiPokiPali = sonaLawa.pokiPali.size(); // li lon tawa assert() taso.
#endif

        // li alasa e ijo tan pini tawa open tawa ni: ni li pona e pali pi nimi wawa sin pi toki 
        //      "ilo li sina".
        for (auto alasaIjo = this->ijoPiNimiWawa.rbegin() 
                ; alasaIjo != this->ijoPiNimiWawa.rend()
                ; alasaIjo++)
            (*alasaIjo)->lawa(sonaLawa);

        assert( sonaLawa.pokiPali.size() - suliPiPokiPali == this->ijoPiNimiWawa.size()
             && "lawa e ijo pi nimi wawa tawa la nanpa ijo ike lon poki pali!");


#ifndef NDEBUG
        suliPiPokiPali = sonaLawa.pokiPali.size(); // li lon tawa assert() taso.
#endif

        sonaLawa.lonPiKasiPiTenpoNi = &this->lonKasi;
        if (this->nimiWawaTawa->lawa(sonaLawa, this->ijoPiNimiWawa.size())) 
            sonaLawa.kasiPiTenpoNi = this->lonTawaTawa - 1;

        assert( suliPiPokiPali - sonaLawa.pokiPali.size() == this->ijoPiNimiWawa.size() - 1
             && "li lawa e nimi wawa tawa la nanpa ijo ike lon poki pali!");
    }

    void KasiPiPanaLonPoki::lawa(SonaLawa& sonaLawa) const noexcept(false) {
#ifndef NDEBUG
        size_t suliPiPokiPali = sonaLawa.pokiPali.size(); // li lon tawa assert() taso.
#endif

        this->ijoPana->lawa(sonaLawa);

        assert( sonaLawa.pokiPali.size() - suliPiPokiPali == 1
             && "lawa e nimi wawa tawa la nanpa ijo ike lon poki pali!");


        sonaLawa.pokiAli[this->nimiPoki] = std::move(sonaLawa.pokiPali.top());
        sonaLawa.pokiPali.pop();

        sonaLawa.pokiPali.push("");
    }



    void panaEPokiOpenLonPokiAli( std::unordered_map<std::string, std::string>& pokiAli
                                , const std::string& lonLipu) {
        static const std::array<std::string, 3> pokiOSPiNimiJan = {"USER", "USERNAME", "LOGNAME"};
        const char* nimiJan = nullptr;

        for (auto& poki : pokiOSPiNimiJan) {
            nimiJan = getenv(poki.c_str());

            if (nimiJan != nullptr && strcmp(nimiJan, "") != 0)
                break;
        }


        pokiAli["__nanpa_Ilo_Li_Sina"] = "1.0.0";
        pokiAli["__nimi_Ilo_Li_Sina"]  = kepeken::kamaJoENimiPiILO_LI_SINA();
        pokiAli["__nimi_lipu"]         = lonLipu;
        pokiAli["__nimi_jan"]          = nimiJan != nullptr ? nimiJan : "";
        pokiAli["_"]                   = "";
    }



    void lawaELipu(const KasiOpen& lipuWawa, const std::string& lonLipu) noexcept(false) {
        std::unordered_map<std::string, std::string> pokiAli;
        lawaELipu(lipuWawa, pokiAli, lonLipu);
    }

    void lawaELipu(const KasiOpen& lipuWawa
             , std::unordered_map<std::string, std::string>& pokiAli
             , const std::string& lonLipu) noexcept(false) {
        std::stack<std::string> pokiPali;
        size_t kasiPiTenpoNi = 0;
        SonaLawa sonaLawa = {lonLipu, pokiAli, pokiPali, kasiPiTenpoNi, nullptr};

        for (; kasiPiTenpoNi < lipuWawa.kasiLonAnpa.size(); kasiPiTenpoNi++) {
            lipuWawa.kasiLonAnpa.at(kasiPiTenpoNi)->lawa(sonaLawa);

            // linja li pini la ona li wile pana e ijo 1 taso - ijo ona. ni ala la ike li lon.
            assert( pokiPali.size() == 1
                 && "lawa e nimi wawa la nanpa ijo ike lon poki pali!");
            pokiPali.pop();
        }
    }
}