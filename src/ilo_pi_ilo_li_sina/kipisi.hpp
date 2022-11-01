#pragma once

#include <list>
#include <string>

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

        Ijo(NimiIjo nimiIjo);

        Ijo(NimiIjo&& nimiIjo, std::string&& ijo);

        Ijo(NimiIjo nimiIjo, const std::string& ijo);
    };



	/**
	 * @brief li kipisi e lipu wawa.
	 *
	 * @param lonLipu lon pi lipu wawa.
	 * @return poki pi ijo pi lipu wawa.
	 */
	std::list<Ijo> kipisi(const std::string& lonLipu);

    /**
	 * @brief li toki e ijo pi lipu wawa tawa jan pi lawa e ilo nanpa.
	 * 
	 * @param ijoLipu ijoLipu tan kipisi().
	 * @param lonLipu lon pi lipu wawa.
	 */
	void tokiELipuKipisi(const std::list<Ijo>& ijoLipu, const std::string& lonLipu);
}