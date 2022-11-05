#pragma once

#include <list>
#include <string>
#include <unordered_map>

#include "../ijo_kepeken/ike.hpp"

/**
 * ilo kipisi tawa kipisi pi lipu wawa pi toki "ilo li sina".
 */
namespace ilo {
    enum class NimiIjo {
        POKI,
        PANA_LON_POKI,

        POKI_NIMI,

        NIMI_WAWA,
        POKI_PI_IJO_PI_NIMI_WAWA,
        NIMI_TAWA_TAWA,

        LINJA_SIN
    };

    /**
     * @brief li ijo tan lipu wawa. lipu kipisi li kipisi lon ni.
     */
    struct Ijo {
        NimiIjo nimiIjo;
        // ijo li ken poki e nimi sama NimiIjo::POKI en NimiIjo::POKI_NIMI la nimi ni li lon ni.
        std::string ijo;
        kepeken::LonIjo lonIjo;

        Ijo(NimiIjo nimiIjo, size_t linja, size_t sitelenLonLinja);

        Ijo(NimiIjo&& nimiIjo, std::string&& ijo, size_t&& linja, size_t&& sitelenLonLinja);

        Ijo(NimiIjo nimiIjo, const std::string& ijo, size_t linja, size_t sitelenLonLinja);
    };



	/**
	 * @brief li kipisi e lipu wawa.
	 *
	 * @param lonLipu lon pi lipu wawa.
	 * @return poki pi ijo pi lipu wawa.
	 */
	std::list<Ijo> kipisi(const std::string& lonLipu) noexcept(false);



    /**
     * @brief li kama jo e nimi pi nimi ijo tawa toki tawa jan.
     * 
     * @param nimiIjo nimi ijo tawa kama e nimi pi nimi ijo.
     * @return        nimi pi nimi ijo.
     */
    std::string nimiIjoTawaNimiPiNimiIjo(NimiIjo nimiIjo);

    /**
     * @return nimi pi sitelen nasa (jan li sitelen e ni) tan sitelen nasa ni.
     */
    const std::unordered_map<char, char>& sitelenNasaTawaNimi();
}