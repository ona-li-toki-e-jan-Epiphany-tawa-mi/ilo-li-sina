#include "nimi_wawa.hpp"

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <list>

#include "../../ijo_kepeken/ike.hpp"
#include "../../ante_toki/ante_toki.hpp"



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
 * @brief toki([nimi...]) -> ala
 * 
 * li toki e nimi lon lupa Stdout.
 */
void toki(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    tokiEAli(std::cout, sonaLawa.pokiPali, nanpaIjo);
    sonaLawa.pokiPali.push("");
}

/**
 * @brief tokiELinja([nimi...]) -> ala
 * 
 * lon lupa Stdout la li toki e nimi e ike.
 */
void tokiELinja(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    toki(sonaLawa, nanpaIjo);
    std::cout << '\n';
}

/**
 * @brief tokiEIke([nimi...]) -> ala
 * 
 * li toki e nimi lon lupa Stderr.
 */
void tokiEIke(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    tokiEAli(std::cerr, sonaLawa.pokiPali, nanpaIjo);
    sonaLawa.pokiPali.push("");
}

/**
 * @brief tokiEIkeELinja([nimi...]) -> ala
 * 
 * lon lupa Stderr la li toki e nimi e ike.
 */
void tokiEIkeELinja(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    tokiEIke(sonaLawa, nanpaIjo);
    std::cerr << '\n';
}

/**
 * @brief kamaJoTanJan([nimi...]) -> nimi tan jan
 * 
 * li toki e nimi tawa jan li kama jo e nimi tan ona.
 * 
 * @throws std::runtime_error li kama jo e sitelen pi pini lipu.
 */
void kamaJoTanJan(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) noexcept(false) {
    // nimi li wile lon sewi pi poki pali tawa poki e nimi tawa jan. toki la 1 li lon tawa ni. ni ala la
    //      mi wile pana e poki nimi ala lon ona.
    if (nanpaIjo != 0) {
        toki(sonaLawa, nanpaIjo);

    } else
        sonaLawa.pokiPali.push("");

    if (!std::getline(std::cin, sonaLawa.pokiPali.top())) {
        kepeken::tokiEIke({ sonaLawa.lonLipu
                          , sonaLawa.lonPiKasiPiTenpoNi
                          , "kamaJoTanJan(): " + ante_toki::nimiTawaJan("ike.lawa.pini_lipu")});

        throw std::runtime_error("kamaJoTanJan() la li kama jo e pini lipu!");
    }
}

/**
 * @brief wan([nimi...]) -> nimi wan tan nimi pana
 * 
 * li wan e poki nimi mute.
 */
void wan(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    std::string nimiSin;

    for (; nanpaIjo > 0; nanpaIjo--) {
        nimiSin.append(std::move(sonaLawa.pokiPali.top()));
        sonaLawa.pokiPali.pop();
    }

    sonaLawa.pokiPali.push(std::move(nimiSin));
}

/**
 * @brief awen([tenpo...]) -> ala
 * 
 * li awen lon tenpo pana.
 * 
 * @throws std::runtime_error nanpa li nanpa ala anu nanpa ike.
 */
void awen(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) noexcept(false) {
    // li weka e ijo tan lupa tawa ni: sitelen ali lon ona li kama lon ilo CLI pi pana sitelen.
    std::cout.flush();
    std::cerr.flush();


    int tenpoLape = 0;
    bool nanpaIke = false;
    
    for (; nanpaIjo > 0; nanpaIjo--) {
        const std::string& ijo = sonaLawa.pokiPali.top();

        try {
            // nimi li jo e ala la li pona. ni la mi wile ala toki e ike.
            if (!ijo.empty())
                tenpoLape += std::stoi(ijo);

        } catch (const std::invalid_argument& liNanpaAla) {
            kepeken::tokiEIke({ sonaLawa.lonLipu
                              , sonaLawa.lonPiKasiPiTenpoNi
                              , "awen(): " + ante_toki::anteENimi(
                                        ante_toki::nimiTawaJan("ike.lawa.awen.nanpa_ala")
                                      , "%s", ijo)});
            
            throw std::runtime_error("awen() la li kama jo e nimi '" + ijo + "' pi nanpa ala!");                            

        } catch (const std::out_of_range& liNanpaIke) {
            kepeken::tokiEIke({ sonaLawa.lonLipu
                              , sonaLawa.lonPiKasiPiTenpoNi
                              , "awen(): " + ante_toki::anteENimi(
                                        ante_toki::nimiTawaJan("ike.lawa.awen.nanpa_ike")
                                      , "%s", ijo)});

            throw std::runtime_error("awen() la li kama jo e nanpa ike '" + ijo + "' pi suli suli anu "
                                     "lili lili!");
        }

        sonaLawa.pokiPali.pop();
    }


    std::this_thread::sleep_for(std::chrono::milliseconds(tenpoLape));
    sonaLawa.pokiPali.push("");
}

/**
 * @brief pokiPiLawaOS([nimiKen...]) -> nimi lon poki nanpa | ala
 * 
 * li kama jo e poki pi lawa OS tan lawa OS sama "LANG" anu "USER" anu "LOGNAME".
 */
void pokiPiLawaOS(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    const char* pokiNanpaPiLawaOS = nullptr;

    // li kama jo e poki pi lawa OS pi nanpa 1 pi jo e ijo.
    for (; nanpaIjo > 0; nanpaIjo--) {
        pokiNanpaPiLawaOS = getenv(sonaLawa.pokiPali.top().c_str());

        if (pokiNanpaPiLawaOS != nullptr && strcmp(pokiNanpaPiLawaOS, "") != 0)
            break;

        sonaLawa.pokiPali.pop();
    }

    pakalaEAwen(sonaLawa.pokiPali, nanpaIjo);
    sonaLawa.pokiPali.push(pokiNanpaPiLawaOS != nullptr ? pokiNanpaPiLawaOS : "");
}



/**
 * @brief tawa(nimiTawa) -> ala
 * 
 * li tawa lon ante.
 */
bool tawa(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    sonaLawa.pokiPali.push("");
    return true;
}

/**
 * @brief niLaTawa(nimiTawa nimiLon nimiPiLonAla [nimiTawaToki...]) -> nimi tan jan 
 * 
 * jan li toki e nimi lon la li tawa lon ante. ona li toki e nimi pi lon ala la li tawa ala. ona li toki 
 *      e ante la li toki sin e toki seme tawa ona. nimi lon anu nimi pi lon ante li ken ala. ni la ona 
 *      li sama nimi ali pi nimi ante ala pi lon anu lon ala.
 * 
 * @throws std::runtime_error nimi lon en nimi pi lon ala li sama.
 * @throws std::runtime_error li kama jo e sitelen pi pini lipu.
 */
bool niLaTawa(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) noexcept(false) {		
    std::string nimiLon = std::move(sonaLawa.pokiPali.top());
    sonaLawa.pokiPali.pop();
    std::string nimiPiLonAla = std::move(sonaLawa.pokiPali.top());
    sonaLawa.pokiPali.pop();
    nanpaIjo -= 2;
    
    if (nimiLon == nimiPiLonAla) {
        kepeken::tokiEIke({ sonaLawa.lonLipu
                          , sonaLawa.lonPiKasiPiTenpoNi
                          , "niLaTawa(): " + ante_toki::anteENimi( ante_toki::nimiTawaJan(
                                    "ike.lawa.tawa_ken.nimi_pi_lon_en_lon_ala_li_ken_ala_sama")
                                                                 , "%s", nimiLon)});

        throw std::runtime_error("niLaTawa() la nimi lon en nimi pi lon ala li ken ala sama!");
    }

    std::list<std::string> nimiTawaJan;
    for (; nanpaIjo > 0; nanpaIjo--) {
        nimiTawaJan.push_back(std::move(sonaLawa.pokiPali.top()));
        sonaLawa.pokiPali.pop();
    }


    sonaLawa.pokiPali.push("");
    std::string& nimiJan = sonaLawa.pokiPali.top();

    // jan li toki e ike la li wile toki sin e ijo.
    while (true) {
        for (const auto& nimi : nimiTawaJan)
            std::cout << nimi;
        
        if (!std::getline(std::cin, nimiJan)) {
            kepeken::tokiEIke({ sonaLawa.lonLipu
                              , sonaLawa.lonPiKasiPiTenpoNi
                              , "niLaTawa(): " + ante_toki::nimiTawaJan("ike.lawa.pini_lipu")});

            throw std::runtime_error("niLaTawa() la li kama jo e pini lipu!");
        }


        if (nimiLon.empty() && nimiJan != nimiPiLonAla) {
            return true;

        } else if (nimiPiLonAla.empty() && nimiJan != nimiLon) {
            return false;

        } else if (sonaLawa.pokiPali.top() == nimiLon) {
            return true;
        
        } else if (sonaLawa.pokiPali.top() == nimiPiLonAla)
            return false;
    }
}

/**
 * @brief alaLaTawa(nimiTawa nimi [nimi...]) -> ala
 * 
 * ijo ali pana li ala la li tawa.
 */
bool alaLaTawa(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) {
        if (!sonaLawa.pokiPali.top().empty()) {
            pakalaEAwen(sonaLawa.pokiPali, nanpaIjo);

            sonaLawa.pokiPali.push("");
            return false;
        }

        sonaLawa.pokiPali.pop();
    }

    sonaLawa.pokiPali.push("");
    return true;
}

/**
 * @brief nanpaLaTawa([nanpaKen...]) -> ala
 * 
 * nimi ali pana li nanpa la li tawa.
 */
bool nanpaLaTawa(ilo::SonaLawa& sonaLawa, unsigned int nanpaIjo) {
    for (; nanpaIjo > 0; nanpaIjo--) 
        try {
            std::stoi(sonaLawa.pokiPali.top());
            sonaLawa.pokiPali.pop();
        
        } catch (const std::logic_error liNanpaAlaAnuPonaAla) {
            pakalaEAwen(sonaLawa.pokiPali, nanpaIjo);
            sonaLawa.pokiPali.push("");

            return false;
        }

    sonaLawa.pokiPali.push("");
    return true;
}



namespace ilo {
    const unsigned int nanpaPiIjoWileAli = -1;



    TomoPiNimiWawa::TomoPiNimiWawa(unsigned int nanpaLiliPiIjoWile, unsigned int nanpaSuliPiIjoWile)
            : nanpaLiliPiIjoWile(nanpaLiliPiIjoWile), nanpaSuliPiIjoWile(nanpaSuliPiIjoWile) {
        assert(nanpaSuliPiIjoWile >= nanpaLiliPiIjoWile && "nanpa lon nanpaLiliPiIjoWile li ken ala "
                                                           "suli tawa nanpa lon nanpaSuliPiIjoWile!");
    }

    TomoPiNimiWawa::~TomoPiNimiWawa() {}


    /**
     * @brief li kama sona e ni: nanpa ijo en ijo ante li ike tawa lawa kepeken nimi wawa. ni la li 
     *      "throw" e ike.
     * @param tomoPiNimiWawa nimi wawa tawa kama sona. 
     */
    void ikeLaIke( SonaLawa& sonaLawa
                 , unsigned int nanpaIjo
                 , const TomoPiNimiWawa& tomoPiNimiWawa) {
        assert( (tomoPiNimiWawa.nanpaLiliPiIjoWile == nanpaPiIjoWileAli || nanpaIjo >= tomoPiNimiWawa.nanpaLiliPiIjoWile)
             && (tomoPiNimiWawa.nanpaSuliPiIjoWile == nanpaPiIjoWileAli || nanpaIjo <= tomoPiNimiWawa.nanpaSuliPiIjoWile)
             && "nanpa ijo tawa nimi wawa li ken ala lon ante tannanpaLiliPiIjoWile en nanpaSuliPiIjoWile!");

        assert(sonaLawa.pokiPali.size() >= nanpaIjo && "poki pali li jo e ijo lili lili tawa lawa e nimi wawa!");
    }


    NimiWawa::NimiWawa(NimiWawaKiwen nimiWawaKiwen)
            : TomoPiNimiWawa(nanpaPiIjoWileAli, nanpaPiIjoWileAli) {
        this->nimiWawaKiwen = nimiWawaKiwen;
    }

    void NimiWawa::lawa(SonaLawa& sonaLawa, unsigned int nanpaIjo) const noexcept(false) {
        ikeLaIke(sonaLawa, nanpaIjo, *this);
        this->nimiWawaKiwen(sonaLawa, nanpaIjo);
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

    bool NimiWawaTawa::lawa(SonaLawa& sonaLawa, unsigned int nanpaIjo) const noexcept(false) {
        ikeLaIke(sonaLawa, nanpaIjo, *this);
        return this->nimiWawaTawaKiwen(sonaLawa, nanpaIjo);
    }



    const std::unordered_map<std::string, NimiWawa> nimiTawaNimiWawa = {
        {"toki",           NimiWawa(&toki)},
        {"tokiELinja",     NimiWawa(&tokiELinja)},
        {"tokiEIke",       NimiWawa(&tokiEIke)},
        {"tokiEIkeELinja", NimiWawa(&tokiEIkeELinja)},

        {"kamaJoTanJan",   NimiWawa(&kamaJoTanJan)},
        {"wan",            NimiWawa(&wan)},

        {"awen",           NimiWawa(&awen)},

        {"pokiPiLawaOS",   NimiWawa(&pokiPiLawaOS)}
    };

    const std::unordered_map<std::string, NimiWawaTawa> nimiTawaNimiWawaTawa = {
        {"tawa",        NimiWawaTawa(&tawa,        0, 0)},
        {"niLaTawa",    NimiWawaTawa(&niLaTawa,    3)},
        {"alaLaTawa",   NimiWawaTawa(&alaLaTawa,   1)},
        {"nanpaLaTawa", NimiWawaTawa(&nanpaLaTawa, 1)}
    };

    const std::string& tomoPiNimiWawaTawaNimi(const TomoPiNimiWawa* tomoPiNimiWawa) noexcept(false) {
        static std::optional<std::unordered_map<NimiWawaKiwen, std::string>> nimiWawaKiwenTawaNimi 
                = std::nullopt;
        static std::optional<std::unordered_map<NimiWawaTawaKiwen, std::string>> nimiWawaTawaKiwenTawaNimi 
                = std::nullopt;


        auto nimiWawa = dynamic_cast<const NimiWawa*>(tomoPiNimiWawa);

        if (nimiWawa != nullptr) {
            if (!nimiWawaKiwenTawaNimi.has_value()) {
                nimiWawaKiwenTawaNimi = std::unordered_map<NimiWawaKiwen, std::string>();

                for (const auto& [nimi, nimiWawa] : nimiTawaNimiWawa)
                    nimiWawaKiwenTawaNimi->operator[](nimiWawa.nimiWawaKiwen) = nimi;
            }

            return nimiWawaKiwenTawaNimi->at(nimiWawa->nimiWawaKiwen);
        }


        if (!nimiWawaTawaKiwenTawaNimi.has_value()) {
            nimiWawaTawaKiwenTawaNimi = std::unordered_map<NimiWawaTawaKiwen, std::string>();

            for (const auto& [nimi, nimiWawa] : nimiTawaNimiWawaTawa)
                nimiWawaTawaKiwenTawaNimi->operator[](nimiWawa.nimiWawaTawaKiwen) = nimi;
        }

        return nimiWawaTawaKiwenTawaNimi->at(static_cast<const NimiWawaTawa*>(tomoPiNimiWawa)
                ->nimiWawaTawaKiwen);
    }
}