#pragma once

#include <string>

/**
 * lawa OS la ijo ni li ken ante. nimi wawa ni li pana e nasin 1 pi kepeken ona. lawa OS li kama suli 
 *      ala.
 */
namespace kepeken {
    /**
     * @brief li lukin ala (weka e sitelen) e ilo pana. 
     * @return true la li ala e ilo nanpa. false la li ala ala.
     */
    bool alaEIloPana();

    /**
     * @brief li lukin kama jo e nimi jan tan lawa OS.
     * 
     * @return li kama jo e ona la nimi jan. li kama jo ala la li "".
     */
    const std::string& nimiJan();
}