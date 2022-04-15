#pragma once

#include <string>

/**
 * ilo tawa ante toki e nimi tawa pana tawa jan.
 */
namespace ante_toki {
    /**
     * toki pi wile jan.
     */
    extern std::string tokiWile;

    /**
     * @brief li kama jo e nimi pi toki jan tan nimi nimi.
     * 
     * li ken ala kama jo e nimi tawa jan la li pana e nimi nimi pana.
     * 
     * @param nimiNimi nimi tawa kama jo e nimi tawa jan (sama "examle.test" anu "ijo_suli.jan_suli.nimi").
     * 
     * @return nimi tawa jan.
     * @retval nimiNimi li ken ala kama jo e nimi tawa jan la li pana.
     */
    const std::string& kamaJoENimiTawaJan(const std::string& nimiNimi);

    /**
     * @brief li ante e nimi weka tawa nimi kama lon poki nimi.
     * 
     * @param nimiTawaAnte li ante e poki nimi ni.
     * @param nimiWeka nimi ni li weka tan nimi tawa ante.
     * @param nimiKama nimi ni li kama lon lon pi nimi weka lon nimi tawa ante.
     * 
     * @return nimi sin pi nimi weka ala pi nimi kama kin.
     * @retval nimiTawaAnte nimi weka li lon ala nimi tawa ante.
     */
    std::string anteENimi(std::string nimiTawaAnte, const std::string& nimiWeka, const std::string& nimiKama);
}