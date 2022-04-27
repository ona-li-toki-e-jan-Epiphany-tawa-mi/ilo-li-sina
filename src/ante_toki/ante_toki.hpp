#pragma once

#include <string>

/**
 * ilo tawa ante toki e nimi tawa pana tawa jan.
 */
namespace ante_toki {
    /**
     * @brief li lukin kama jo e toki wile jan li open kepeken e ona tawa ante toki.
     * 
     * nanpa 1 la li lukin e poki nanpa LANG pi lawa OS. (true)
     * nanpa 2 la toki pona li lon la li kepeken e toki pona. (false)
     * nanpa 3 la li kepeken e toki pi nanpa 1 lon poki pi toki ali. (false)
     * nanpa 4 la toki ala la ala li kama. (false)
     *
     * @return li kama ala kama jo e toki wile.
     */
    bool alasaETokiWile();

    /**
     * @brief li kama jo e nimi pi toki jan tan nimi nimi.
     * 
     * li ken ala kama jo e nimi tawa jan la li pana e nimi nimi pana.
     * 
     * @param nimiNimi nimi tawa kama jo e nimi tawa jan (sama "examle.test" anu "ijo_suli.jan_suli.nimi").
     * 
     * @return          nimi tawa jan.
     * @retval nimiNimi li ken ala kama jo e nimi tawa jan la li pana.
     */
    const std::string& kamaJoENimiTawaJan(const std::string& nimiNimi);

    /**
     * @brief li ante e nimi weka tawa nimi kama lon poki nimi.
     * 
     * @param nimiTawaAnte li ante e poki nimi ni.
     * @param nimiWeka     nimi ni li weka tan nimi tawa ante.
     * @param nimiKama     nimi ni li kama lon lon pi nimi weka lon nimi tawa ante.
     * 
     * @return              nimi sin pi nimi weka ala pi nimi kama kin.
     * @retval nimiTawaAnte nimi weka li lon ala nimi tawa ante.
     */
    std::string anteENimi(std::string nimiTawaAnte, const std::string& nimiWeka, const std::string& nimiKama);
}