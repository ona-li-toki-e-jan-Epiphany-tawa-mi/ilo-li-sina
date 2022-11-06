#include "lawa.hpp"

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
        for (auto& ijo : this->ijoPiNimiWawa)
            ijo->lawa(sonaLawa);

        this->nimiWawa->lawa(sonaLawa, this->ijoPiNimiWawa.size());
    }

    void KasiPiNimiWawaTawa::lawa(SonaLawa& sonaLawa) const {
        for (auto& ijo : this->ijoPiNimiWawa)
            ijo->lawa(sonaLawa);

        if (this->nimiWawaTawa->lawa(sonaLawa, this->ijoPiNimiWawa.size()))
            sonaLawa.kasiPiTenpoNi = this->lonTawaTawa - 1;
    }

    void KasiPiPanaLonPoki::lawa(SonaLawa& sonaLawa) const {
        this->ijoPana->lawa(sonaLawa);

        sonaLawa.pokiAli[this->nimiPoki] = sonaLawa.pokiPali.top();
        sonaLawa.pokiPali.pop();
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