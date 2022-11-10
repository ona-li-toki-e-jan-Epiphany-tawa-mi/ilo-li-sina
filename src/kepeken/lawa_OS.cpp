#include "lawa_OS.hpp"

#ifdef WINDOWS
#include <cstdlib>
//#include <windows.h>
#elif UNIX
#include <unistd.h>
#include <term.h>
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
}