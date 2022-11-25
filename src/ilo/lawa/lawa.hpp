#pragma once

#include "../pali/pali.hpp"

/**
 * @brief ilo tawa lawa e ilo nanpa kepeken lipu wawa pi toki "ilo li sina".
 */
namespace ilo {
    /**
     * @brief li pana e poki open lon poki ali lon tenpo open pi lipu wawa.
     * 
     * @param pokiAli poki en nimi lon ona lon tenpo open pi lipu wawa.
     * @param lonLipu lon pi lipu wawa.
     */
    void panaEPokiOpenLonPokiAli( std::unordered_map<std::string, std::string>& pokiAli
                                , const std::string& lonLipu);

    /**
     * @brief li lawa e ilo nanpa kepeken lipu wawa pana. li pali e poki ali pi poki ala. li kepeken ala
     *      e {@see ilo::panaEPokiOpenLonPokiAli};
     * 
     * @param lipuWawa kasi pi lipu wawa.
     * @param lonLipu  lon pi lipu wawa.
     * @throws std::runtime_error lawa la ike li kama.
     */
    void lawaELipu(const KasiOpen& lipuWawa, const std::string& lonLipu) noexcept(false);

    /**
     * @brief li lawa e ilo nanpa kepeken lipu wawa pana.
     * @attention o kepeken e {@see ilo::panaEPokiOpenLonPokiAli} tawa pana e poki open lon ona.
     * 
     * @param lipuWawa kasi pi lipu wawa.
     * @param pokiAli  poki en nimi lon ona lon tenpo open pi lipu wawa.
     * @param lonLipu  lon pi lipu wawa.
     * @throws std::runtime_error lawa la ike li kama.
     */
    void lawaELipu(const KasiOpen& lipuWawa
             , std::unordered_map<std::string, std::string>& pokiAli
             , const std::string& lonLipu) noexcept(false);
}