#pragma once

#include <unordered_map>
#include <string>
#include <stack>

/**
 * nimi wawa ni li ken kepeken lon lipu wawa pi toki "ilo li sina."
 */
namespace ilo {
    /**
     * @brief nimi wawa kiwen lon C++ tawa kepeken lon lipu pi toki "ilo li sina".
     */
    typedef void(*NimiWawaKiwen)(std::stack<std::string>&, unsigned int);
    /**
     * @brief nimi wawa tawa kiwen lon C++ tawa kepeken lon li pi toki "ilo li sina".
     */
    typedef bool(*NimiWawaTawaKiwen)(std::stack<std::string>&, unsigned int);
    /**
     * @brief nanpa pi ijo wile li ken nanpa ali la nanpa ni li kepeken.
     */
    extern const unsigned int nanpaPiIjoWileAli;

    class TomoPiNimiWawa {
        public:
            unsigned int nanpaLiliPiIjoWile;
            unsigned int nanpaSuliPiIjoWile;

            /**
             * @param nanpaLiliPiIjoWile lawa() la nanpa nanpaIjo li wile sama anu suli tawa nanpa ni. 
             * @param nanpaSuliPiIjoWile lawa() la nanpa nanpaIjo li wile sama anu lili tawa nanpa ni. 
             */
            TomoPiNimiWawa(unsigned int nanpaLiliPiIjoWile, unsigned int nanpaSuliPiIjoWile);
    };

    /**
     * @brief li poki e nimi wawa en sona lili wile ona sama nanpa pi ijo wile.
     */
    class NimiWawa : public TomoPiNimiWawa {
        public:
            NimiWawaKiwen nimiWawaKiwen;

            NimiWawa(NimiWawaKiwen nimiWawaKiwen);

            /**
             * @brief li lawa e ilo nanpa kepeken nimi wawa kiwen lon ni. li moku e ijo pi nanpa nanpaIjo
             *      tan poki pokiPali. 
             * @attention nanpaIjo li wile lon nasin nanpa (nanpaLiliPiIjoWile-nanpaSuliPiIjoWile).
             * 
             * @param pokiPali poki ijo lon tenpo lawa.
             * @param nanpaIjo li moku e ijo pi nanpa ni tan pokiPali.
             */
            void lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo);
    };

    class NimiWawaTawa : public TomoPiNimiWawa {
        public:
            NimiWawaTawaKiwen nimiWawaTawaKiwen;

            NimiWawaTawa(NimiWawaTawaKiwen nimiWawaTawaKiwen);
            NimiWawaTawa(NimiWawaTawaKiwen nimiWawaTawaKiwen, unsigned int nanpaLiliPiIjoWile);
            NimiWawaTawa( NimiWawaTawaKiwen nimiWawaTawaKiwen
                        , unsigned int nanpaLiliPiIjoWile
                        , unsigned int nanpaSuliPiIjoWile);

            /**
             * @brief li lawa e ilo nanpa kepeken nimi wawa tawa kiwen lon ni. li moku e ijo pi nanpa 
             *      nanpaIjo tan poki pokiPali. li ken tawa lon ante lon lipu wawa.
             * @attention nanpaIjo li wile lon nasin nanpa (nanpaLiliPiIjoWile-nanpaSuliPiIjoWile).
             * 
             * @param pokiPali poki ijo lon tenpo lawa.
             * @param nanpaIjo li moku e ijo pi nanpa ni tan pokiPali.
             * @return true la li wile tawa lon ante. false la li wile ala.
             */
            bool lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo);
    };



    /**
     * @brief li kama jo e nimi wawa tawa pana lon kasi pi kasi lipu kepeken nimi pi nimi wawa tan lipu jan.
     */
    extern const std::unordered_map<std::string, NimiWawa> nimiTawaNimiWawa;

    /**
     * @return poki li kama jo e nimi pi nimi wawa kepeken nimi wawa kiwen.
     */
    const std::unordered_map<NimiWawaKiwen, std::string>& nimiWawaKiwenTawaNimi();


    /**
     * @brief li kama jo e nimi wawa tawa tawa pana lon kasi pi kasi lipu kepeken nimi pi nimi wawa tawa 
     *      tan lipu jan.
     */
    extern const std::unordered_map<std::string, NimiWawaTawa> nimiTawaNimiWawaTawa;

    /**
     * @return poki li kama jo e nimi pi nimi wawa tawa kepeken nimi wawa tawa kiwen.
     */
    const std::unordered_map<NimiWawaTawaKiwen, std::string>& nimiWawaTawaKiwenTawaNimi();
}