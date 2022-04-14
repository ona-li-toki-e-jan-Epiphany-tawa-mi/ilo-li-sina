#include <unordered_map>

namespace kepeken {
    /**
     * @brief li pali e poki Map sin tan poki ante lon nasin ante.
     * @attention nimi ken lon tenpo 1 taso. ijo mute sama li lon poki la 1 taso li awen.
     * 
     * @tparam nimiIjo nimi ijo lon poki. li kama ijo pi poki sin.
     * @tparam ijo ijo pi poki Map. li kama nimi ijo pi poki sin.
     * @param pokiMAP poki tawa pali e ante.
     * 
     * @return std::unordered_map<ijo, nimiIjo> poki lon nasin ante.
     */
    template<typename nimiIjo, typename ijo>
    std::unordered_map<ijo, nimiIjo> paliEPokiMAPLonNasinAnte(const std::unordered_map<nimiIjo, ijo>& pokiMAP) {
        std::unordered_map<ijo, nimiIjo> pokiMAPSin;

        for (const auto& [nimiIjoPoki, ijoPoki] : pokiMAP)
            pokiMAPSin[ijoPoki] = nimiIjoPoki;

        return pokiMAPSin;
    }
}