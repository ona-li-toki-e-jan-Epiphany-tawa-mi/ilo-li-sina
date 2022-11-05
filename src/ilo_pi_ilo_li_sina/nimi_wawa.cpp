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

    pokiPali.push("");
}

/**
 * @brief lon lupa Stdout la li toki e nimi e ike.
 */
void tokiELinja(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    toki(pokiPali, nanpaIjo);
    std::cout << '\n';

    pokiPali.push("");
}

/**
 * @brief li toki e nimi lon lupa Stderr.
 */
void tokiEIke(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    tokiEAli(std::cerr, pokiPali, nanpaIjo);

    pokiPali.push("");
}

/**
 * @brief lon lupa Stderr la li toki e nimi e ike.
 */
void tokiEIkeELinja(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    tokiEIke(pokiPali, nanpaIjo);
    std::cerr << '\n';

    pokiPali.push("");
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

    pokiPali.push(std::move(nimiSin));
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

    pokiPali.push("");
}



bool tawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    pokiPali.push("");
    return true;
}

bool niLaTawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    assert(false && "o pona e ni!"); //TODO
}

bool alaLaTawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) 
        if (!pokiPali.top().empty()) {
            pakalaEAwen(pokiPali, nanpaIjo);
            return false;
        }

    return true;
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



    TomoPiNimiWawa::TomoPiNimiWawa(unsigned int nanpaLiliPiIjoWile, unsigned int nanpaSuliPiIjoWile)
            : nanpaLiliPiIjoWile(nanpaLiliPiIjoWile), nanpaSuliPiIjoWile(nanpaSuliPiIjoWile) {
        assert(nanpaSuliPiIjoWile >= nanpaLiliPiIjoWile && "nanpa lon nanpaLiliPiIjoWile li ken ala "
                                                           "suli tawa nanpa lon nanpaSuliPiIjoWile!");
    }


    NimiWawa::NimiWawa(NimiWawaKiwen nimiWawaKiwen)
            : TomoPiNimiWawa(nanpaPiIjoWileAli, nanpaPiIjoWileAli) {
        this->nimiWawaKiwen = nimiWawaKiwen;
    }

    void NimiWawa::lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
        assert( (this->nanpaLiliPiIjoWile != nanpaPiIjoWileAli && nanpaIjo < this->nanpaLiliPiIjoWile)
             || (this->nanpaSuliPiIjoWile != nanpaPiIjoWileAli && nanpaIjo > this->nanpaSuliPiIjoWile)
             && "nanpa ijo tawa nimi wawa li ken ala lon ante tannanpaLiliPiIjoWile en nanpaSuliPiIjoWile!");

        assert(pokiPali.size() > nanpaIjo && "poki pali li jo e ijo lili lili tawa lawa e nimi wawa!");

        this->nimiWawaKiwen(pokiPali, nanpaIjo);
    }


    NimiWawaTawa::NimiWawaTawa(NimiWawaTawaKiwen nimiWawaTawaKiwen)
            : TomoPiNimiWawa(nanpaPiIjoWileAli, nanpaPiIjoWileAli) {
        this->nimiWawaTawaKiwen = nimiWawaTawaKiwen;
    }

    NimiWawaTawa::NimiWawaTawa(NimiWawaTawaKiwen nimiWawaTawaKiwen, unsigned int nanpaLiliPiIjoWile)
        : TomoPiNimiWawa(nanpaLiliPiIjoWile, nanpaPiIjoWileAli) {
        this->nimiWawaTawaKiwen = nimiWawaTawaKiwen;
    }

    NimiWawaTawa::NimiWawaTawa( NimiWawaTawaKiwen nimiWawaTawaKiwen
                              , unsigned int nanpaLiliPiIjoWile
                              , unsigned int nanpaSuliPiIjoWile)
            : TomoPiNimiWawa(nanpaLiliPiIjoWile, nanpaSuliPiIjoWile) {
        this->nimiWawaTawaKiwen = nimiWawaTawaKiwen;
    }

    bool NimiWawaTawa::lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo) {
        assert( (this->nanpaLiliPiIjoWile != nanpaPiIjoWileAli && nanpaIjo < this->nanpaLiliPiIjoWile)
             || (this->nanpaSuliPiIjoWile != nanpaPiIjoWileAli && nanpaIjo > this->nanpaSuliPiIjoWile)
             && "nanpa ijo tawa nimi wawa li ken ala lon ante tannanpaLiliPiIjoWile en nanpaSuliPiIjoWile!");

        assert(pokiPali.size() > nanpaIjo && "poki pali li jo e ijo lili lili tawa lawa e nimi wawa!");

        return this->nimiWawaTawaKiwen(pokiPali, nanpaIjo);
    }



    const std::unordered_map<std::string, NimiWawa> nimiTawaNimiWawa = {
        {"toki",                     NimiWawa(&toki)},
        {"tokiELinja",               NimiWawa(&tokiELinja)},
        {"tokiEIke",                 NimiWawa(&tokiEIke)},
        {"tokiEIkeELinja",           NimiWawa(&tokiEIkeELinja)},

        {"kamaJoTanJan",             NimiWawa(&kamaJoTanJan)},
        {"wan",                      NimiWawa(&wan)},

        {"awen",                     NimiWawa(&awen)},

        {"kamaJoEPokiNanpaPiLawaOS", NimiWawa(&kamaJoEPokiNanpaPiLawaOS)}
    };

    const std::unordered_map<NimiWawaKiwen, std::string>& nimiWawaKiwenTawaNimi() {
        static std::optional<std::unordered_map<NimiWawaKiwen, std::string>> nimiWawaKiwenTawaNimi 
                = std::nullopt;

        if (!nimiWawaKiwenTawaNimi.has_value()) {
            nimiWawaKiwenTawaNimi = std::unordered_map<NimiWawaKiwen, std::string>();

            for (const auto& [nimi, nimiWawa] : nimiTawaNimiWawa)
                nimiWawaKiwenTawaNimi->operator[](nimiWawa.nimiWawaKiwen) = nimi;
        }

        return *nimiWawaKiwenTawaNimi;
    }


    const std::unordered_map<std::string, NimiWawaTawa> nimiTawaNimiWawaTawa = {
        {"tawa",      NimiWawaTawa(&tawa,     0, 0)},
        {"niLaTawa",  NimiWawaTawa(&niLaTawa, 3)},
        {"alaLaTawa", NimiWawaTawa(&alaLaTawa)}
    };

    const std::unordered_map<NimiWawaTawaKiwen, std::string>& nimiWawaTawaKiwenTawaNimi() {
        static std::optional<std::unordered_map<NimiWawaTawaKiwen, std::string>> nimiWawaTawaKiwenTawaNimi 
                = std::nullopt;

        if (!nimiWawaTawaKiwenTawaNimi.has_value()) {
            nimiWawaTawaKiwenTawaNimi = std::unordered_map<NimiWawaTawaKiwen, std::string>();

            for (const auto& [nimi, nimiWawa] : nimiTawaNimiWawaTawa)
                nimiWawaTawaKiwenTawaNimi->operator[](nimiWawa.nimiWawaTawaKiwen) = nimi;
        }

        return *nimiWawaTawaKiwenTawaNimi;
    }
}