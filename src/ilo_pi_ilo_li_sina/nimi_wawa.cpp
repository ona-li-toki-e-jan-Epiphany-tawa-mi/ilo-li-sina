#include "nimi_wawa.hpp"

#include <cassert>
#include <iostream>



void toki(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) {
        std::cout << pokiPali.top();
        pokiPali.pop();
    }
}

void tokiELinja(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) {
        std::cout << pokiPali.top();
        pokiPali.pop();
    }

    std::cout << '\n';
}

void tokiEIke(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) {
        std::cerr << pokiPali.top();
        pokiPali.pop();
    }
}

void tokiEIkeELinja(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) {
        std::cerr << pokiPali.top();
        pokiPali.pop();
    }

    std::cerr << '\n';
}



namespace ilo {
    const unsigned int nanpaPiIjoWileAli = -1;



    NimiWawa::NimiWawa(NimiWawaKiwen nimiWawaKiwen)
        : NimiWawa::NimiWawa(nimiWawaKiwen, nanpaPiIjoWileAli, nanpaPiIjoWileAli) {}

    NimiWawa::NimiWawa(NimiWawaKiwen nimiWawaKiwen, unsigned int nanpaLiliPiIjoWile, unsigned int nanpaSuliPiIjoWile) {
        this->nimiWawaKiwen = nimiWawaKiwen;

        assert(nanpaSuliPiIjoWile >= nanpaLiliPiIjoWile && "nanpa lon nanpaLiliPiIjoWile li ken ala "
                                                            "suli tawa nanpa lon nanpaSuliPiIjoWile!");

        this->nanpaLiliPiIjoWile = nanpaLiliPiIjoWile;
        this->nanpaSuliPiIjoWile = nanpaSuliPiIjoWile;
    }

    void NimiWawa::lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
        assert( (this->nanpaLiliPiIjoWile != nanpaPiIjoWileAli || this->nanpaSuliPiIjoWile != nanpaPiIjoWileAli) 
             && nanpaIjo >= this->nanpaLiliPiIjoWile && nanpaIjo <= this->nanpaSuliPiIjoWile
             && "nanpa ijo tawa nimi wawa li ken ala lon ante tannanpaLiliPiIjoWile en nanpaSuliPiIjoWile!");

        assert(pokiPali.size() >= nanpaIjo && "poki pali li jo e ijo lili lili tawa lawa e nimi wawa!");

        this->nimiWawaKiwen(pokiPali, nanpaIjo);
    }



    const std::unordered_map<std::string, NimiWawa> nimiPiNimiWawaTawaNimiWawa = {
        {"toki",           NimiWawa(&toki)},
        {"tokiELinja",     NimiWawa(&tokiELinja)},
        {"tokiEIke",       NimiWawa(&tokiEIke)},
        {"tokiEIkeELinja", NimiWawa(&tokiEIkeELinja)}
    };
}