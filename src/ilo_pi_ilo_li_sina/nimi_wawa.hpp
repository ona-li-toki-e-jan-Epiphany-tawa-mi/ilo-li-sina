#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <stack>

/**
 * nimi wawa ni li ken kepeken lon lipu wawa pi toki "ilo li sina."
 */
namespace ilo {
    /**
     * @brief nimi wawa kiwen lon C++ tawa kepeken lon lipu pi toki "ilo li sina".
     */
    typedef std::function<void(std::stack<std::string>&, unsigned int)> NimiWawaKiwen;
    /**
     * @brief nanpa pi ijo wile li ken nanpa ali la nanpa ni li kepeken.
     */
    extern const unsigned int nanpaPiIjoWileAli;

    /**
     * @brief li poki e nimi wawa en sona lili wile ona sama nanpa pi ijo wile.
     */
    struct NimiWawa {
        NimiWawaKiwen nimiWawaKiwen;
        // lawa() li wile e ni: nanpa nanpaIjo li wile sama anu suli tawa nanpa ni.
        unsigned int  nanpaLiliPiIjoWile;
        // lawa() li wile e ni: nanpa nanpaIjo li wile sama anu lili tawa nanpa ni.
        unsigned int  nanpaSuliPiIjoWile;

        NimiWawa(NimiWawaKiwen nimiWawaKiwen);
        NimiWawa(NimiWawaKiwen nimiWawaKiwen, unsigned int nanpaLiliPiIjoWile, unsigned int nanpaSuliPiIjoWile);

        /**
         * @brief li lawa e ilo nanpa kepeken nimi wawa kiwen lon ni. li moku e ijo pi nanpa nanpaIjo
         *      tan poki pokiPali. nanpaIjo li wile lon nasin nanpa (nanpaLiliPiIjoWile-nanpaSuliPiIjoWile).
         * 
         * @param pokiPali poki ijo lon tenpo lawa.
         * @param nanpaIjo li moku e ijo pi nanpa ni tan pokiPali.
         */
        void lawa(std::stack<std::string>& pokiPali, unsigned int nanpaIjo);
    };

    /**
     * @brief li kama jo e nimi wawa tawa pana lon kasi pi kasi lipu kepeken nimi pi nimi wawa tan lipu jan.
     */
    extern const std::unordered_map<std::string, NimiWawa> nimiPiNimiWawaTawaNimiWawa;
}