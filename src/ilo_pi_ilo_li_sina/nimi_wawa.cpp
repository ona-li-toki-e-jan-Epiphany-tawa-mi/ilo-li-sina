#include "nimi_wawa.hpp"

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>

#include "../ijo_kepeken/ike.hpp"
#include "../ante_toki/ante_toki.hpp"



/**
 * @brief li toki e nimi pi nimi wawa lon pokiPali lon lupa pana.
 * @param lupaTawaToki li toki e nimi lon lupa ni.
 */
void tokiEAli(std::ostream& lupaTawaToki, std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) {
        lupaTawaToki << pokiPali.top();
        pokiPali.pop();
    }
}

/**
 * @brief nimi wawa li pakala ala e ijo ali ona la ni li wile kepeken tawa pakala e ijo awen.
 */
void pakalaEAwen(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) pokiPali.pop();
}



/**
 * @brief li toki e nimi lon lupa Stdout.
 */
void toki(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    tokiEAli(std::cout, pokiPali, nanpaIjo);
}

/**
 * @brief lon lupa Stdout la li toki e nimi e ike.
 */
void tokiELinja(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    toki(pokiPali, nanpaIjo);
    std::cout << '\n';
}

/**
 * @brief li toki e nimi lon lupa Stderr.
 */
void tokiEIke(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    tokiEAli(std::cerr, pokiPali, nanpaIjo);
}

/**
 * @brief lon lupa Stderr la li toki e nimi e ike.
 */
void tokiEIkeELinja(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    tokiEIke(pokiPali, nanpaIjo);
    std::cerr << '\n';
}

/**
 * @brief li toki e nimi tawa jan li kama jo e nimi tan ona.
 */
void kamaJoTanJan(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    if (nanpaIjo != 0)
        tokiELinja(pokiPali, nanpaIjo);

    pokiPali.push("");
    if (!std::getline(std::cin, pokiPali.top())) {
        kepeken::tokiEIke({ "nimiPiLipuWawa" //TODO
                          , (unsigned int)-1, (unsigned int)-1   // TODO "lonKasi"
                          , "kamaJoTanJan(): " + ante_toki::nimiTawaJan("ike.lawa.pini_lipu")});
        //TODO o "throw" e ike.
    }
}

/**
 * @brief li wan e poki nimi mute.
 */
void wan(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    std::string nimiSin;

    for (; nanpaIjo > 0; nanpaIjo--) {
        nimiSin.append(pokiPali.top());
        pokiPali.pop();
    }

    pokiPali.push("");
    pokiPali.top().swap(nimiSin);
}

/**
 * @brief li awen lon tenpo pana.
 */
void awen(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    // li weka e ijo tan lupa tawa ni: sitelen ali lon ona li kama lon ilo CLI pi pana sitelen.
    std::cout.flush();
    std::cerr.flush();


    int tenpoLape = 0;
    bool nanpaIke = false;
    
    for (; nanpaIjo > 0; nanpaIjo--) {
        const std::string& ijo = pokiPali.top();

        try {
            // nimi li jo e ala la li pona. ni la mi wile ala toki e ike.
            if (!ijo.empty())
                tenpoLape += std::stoi(ijo);

        } catch (const std::invalid_argument& liNanpaAla) {
            kepeken::tokiEIke({ "nimiPiLipuWawa" // TODO
                              , 10, 10 //TODO lonKasi
                              , "awen(): " + ante_toki::anteENimi(
                                        ante_toki::nimiTawaJan("ike.lawa.awen.nanpa_ala")
                                      , "%s", ijo)});
            
            nanpaIke = true;
            break;                                      

        } catch (const std::out_of_range& liNanpaIke) {
            kepeken::tokiEIke({ "nimiPiLipuWawa" //TODO
                              , 10, 10 //TODO "lonKasi"
                              , "awen(): " + ante_toki::anteENimi(
                                        ante_toki::nimiTawaJan("ike.lawa.awen.nanpa_ike")
                                      , "%s", ijo)});

            nanpaIke = true;
            break;
        }

        pokiPali.pop();
    }


    pakalaEAwen(pokiPali, nanpaIjo);

    if (!nanpaIke)
        std::this_thread::sleep_for(std::chrono::milliseconds(tenpoLape));
}

/**
 * @brief li kama jo e poki nanpa pi lawa OS tan lawa OS sama "LANG" anu "USER" anu "LOGNAME".
 */
void kamaJoEPokiNanpaPiLawaOS(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    const char* pokiNanpaPiLawaOS = nullptr;

    for (; nanpaIjo > 0; nanpaIjo--) {
        pokiNanpaPiLawaOS = getenv(pokiPali.top().c_str());

        if (pokiNanpaPiLawaOS != nullptr && strcmp(pokiNanpaPiLawaOS, "") != 0)
            break;

        pokiPali.pop();
    }

    pakalaEAwen(pokiPali, nanpaIjo);
    pokiPali.push(pokiNanpaPiLawaOS != nullptr ? pokiNanpaPiLawaOS : "");
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
        {"tokiEIkeELinja", NimiWawa(&tokiEIkeELinja)},

        {"kamaJoTanJan", NimiWawa(&kamaJoTanJan)},
        {"wan", NimiWawa(&wan)},

        {"awen", NimiWawa(&awen)},

        {"kamaJoEPokiNanpaPiLawaOS", NimiWawa(&kamaJoEPokiNanpaPiLawaOS)}
    };
}