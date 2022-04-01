#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include "kulupu_nimi.hpp"

/**
 * ilo kipisi tawa kipisi pi lipu wawa pi toki "ilo li sina".
 */
namespace kipisi {
	/**
	 * @brief poki tawa ante tan sitelen pi nasa ala (sama \n en \t) tawa sitelen nasa (sama 0x10 en 0x9).
	 */
	extern const std::unordered_map<char, char> sitelenNasaTanNimi;

	/**
	 * @breif li kipisi e lipu wawa li pali e kulupu nimi tan kipisi li pana e ona lon
	 * 	poki.
	 *
	 * @param pokiPiKulupuNimi li pana e kulupu nimi lon ni.
	 * @param nimiPiLipuWawa nimi pi lipu wawa tawa kipisi.
	 *
	 * @return pokiPiKulupuNimi.
	 */
	std::vector<KulupuNimi>& kipisiELipuWawa(std::vector<KulupuNimi>& pokiPiKulupuNimi, const std::string& nimiPiLipuWawa);
}
