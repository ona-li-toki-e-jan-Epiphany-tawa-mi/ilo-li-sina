#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <stack>

namespace ilo {
    typedef std::function<void(std::stack<std::string>&, unsigned int)> NimiWawaKiwen;
    extern const unsigned int nanpaPiIjoWileAli;

    struct NimiWawa {
        NimiWawaKiwen nimiWawaKiwen;
        unsigned int  nanpaLiliPiIjoWile;
        unsigned int  nanpaSuliPiIjoWile;

        NimiWawa(NimiWawaKiwen nimiWawaKiwen);
        NimiWawa(NimiWawaKiwen nimiWawaKiwen, unsigned int nanpaLiliPiIjoWile, unsigned int nanpaSuliPiIjoWile);

        void lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo);
    };

    extern const std::unordered_map<std::string, NimiWawa> nimiPiNimiWawaTawaNimiWawa;
}