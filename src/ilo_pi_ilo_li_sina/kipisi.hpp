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

    struct Ijo {
        NimiIjo nimiIjo;
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
}