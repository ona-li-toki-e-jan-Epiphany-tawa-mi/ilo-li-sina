#include "lawa.hpp"

#include <array>
#include <cstring>

#include "../../ijo_kepeken/ike.hpp"

namespace ilo {
    void KasiOpen::lawa(SonaLawa& sonaLawa) const {
        lawaELipu(*this, sonaLawa.pokiAli, sonaLawa.lonLipu);
    }

    void KasiPini::lawa(SonaLawa& sonaLawa) const {}

    void KasiPiPokiNimi::lawa(SonaLawa& sonaLawa) const {
        sonaLawa.pokiPali.push(this->nimi);
    }

    void KasiPoki::lawa(SonaLawa& sonaLawa) const {
        sonaLawa.pokiPali.push(sonaLawa.pokiAli[this->nimiPoki]);
    }

    void KasiPiNimiWawa::lawa(SonaLawa& sonaLawa) const {
        for (auto alasaIjo = this->ijoPiNimiWawa.rbegin() 
                ; alasaIjo != this->ijoPiNimiWawa.rend()
                ; alasaIjo++)
            (*alasaIjo)->lawa(sonaLawa);

        this->nimiWawa->lawa(sonaLawa, this->ijoPiNimiWawa.size());
    }

    void KasiPiNimiWawaTawa::lawa(SonaLawa& sonaLawa) const {
        for (auto alasaIjo = this->ijoPiNimiWawa.rbegin() 
                ; alasaIjo != this->ijoPiNimiWawa.rend()
                ; alasaIjo++)
            (*alasaIjo)->lawa(sonaLawa);

        if (this->nimiWawaTawa->lawa(sonaLawa, this->ijoPiNimiWawa.size())) 
            sonaLawa.kasiPiTenpoNi = this->lonTawaTawa - 1;
    }

    void KasiPiPanaLonPoki::lawa(SonaLawa& sonaLawa) const {
        this->ijoPana->lawa(sonaLawa);

        sonaLawa.pokiAli[this->nimiPoki] = sonaLawa.pokiPali.top();
        sonaLawa.pokiPali.pop();
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


        pokiAli["__nanpa_Ilo_Li_Sina"] = "0.0";
        pokiAli["__nimi_Ilo_Li_Sina"]  = kepeken::kamaJoENimiPiILO_LI_SINA();
        pokiAli["__nimi_lipu"]         = lonLipu;
        pokiAli["__nimi_jan"]          = nimiJan != nullptr ? nimiJan : "";
        pokiAli["_"]                   = "";
    }



    void lawaELipu(const KasiOpen& lipuWawa, const std::string& lonLipu) {
        std::unordered_map<std::string, std::string> pokiAli;
        lawaELipu(lipuWawa, pokiAli, lonLipu);
    }

    void lawaELipu(const KasiOpen& lipuWawa
             , std::unordered_map<std::string, std::string>& pokiAli
             , const std::string& lonLipu) {
        std::stack<std::string> pokiPali;
        size_t kasiPiTenpoNi = 0;
        SonaLawa sonaLawa = {lonLipu, pokiAli, pokiPali, kasiPiTenpoNi, nullptr};

        for (; kasiPiTenpoNi < lipuWawa.kasiLonAnpa.size(); kasiPiTenpoNi++) {
            lipuWawa.kasiLonAnpa.at(kasiPiTenpoNi)->lawa(sonaLawa);

            while (!pokiPali.empty())
                pokiPali.pop();
        }
    }
}