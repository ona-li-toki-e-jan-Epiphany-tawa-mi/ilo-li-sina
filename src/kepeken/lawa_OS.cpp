#include "lawa_OS.hpp"

#include <array>
#include <cstring>
#include <optional>

#ifdef WINDOWS
#include <cstdlib>
//#include <windows.h>
#elif UNIX
#include <unistd.h>
#include <term.h>
#include <pwd.h>
#endif

namespace kepeken {
    bool alaEIloPana() {
#ifdef WINDOWS
        if (!system(nullptr))
            return false;
            
        int nanpaIke = system("cls");//TODO o pona e ni kepeken ilo API pi lawa Windows.
        return nanpaIke == 0;

#elif UNIX
        // ilo Terminfo li open ala la li open e ona.
        if (cur_term == nullptr) {
            int nanpaIke;
            setupterm(nullptr, STDOUT_FILENO, &nanpaIke);

            if (nanpaIke <= 0)
                return false;
        }

        // li kama jo e nimi wawa "clear" li lawa e ona.
        return putp(tigetstr("clear")) == 0;  
#endif

        return false;
    }



    const std::string& nimiJan() {
        static std::optional<std::string> nimiJan = std::nullopt;
        if (nimiJan.has_value())
            return *nimiJan;


    // li lukin kama jo e nimi tan lawa OS.
#ifdef WINDOWS
    //TODO o pona e ni kepeken ilo API pi lawa Windows.

#elif UNIX
        passwd* tomoPiSonaJan = getpwuid(geteuid());

        if (tomoPiSonaJan != nullptr) 
            return *(nimiJan = tomoPiSonaJan->pw_name);
#endif


        // li lukin kama jo e ona tan poki Enviroment Variables pi lawa OS.
        static const std::array<std::string, 3> pokiOSPiNimiJan = {"USER", "USERNAME", "LOGNAME"};

        for (auto& poki : pokiOSPiNimiJan) {
            const char* nimiJanKen = getenv(poki.c_str());

            if (nimiJanKen != nullptr && strcmp(nimiJanKen, "") != 0) 
                return *(nimiJan = nimiJanKen);
        }


        // nasin ante li pali ala la mi wile pana e ala.
        return *(nimiJan = "");
    }
}