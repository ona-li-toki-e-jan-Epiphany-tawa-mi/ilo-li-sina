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
	 * @return poki Map pi sitelen nasa tan nimi lon nasin ante. 
	 */
	const std::unordered_map<char, char>& kamaJoEPokiPiNimiTanSitelenNasa();

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

	/**
	 * @brief li toki e kulupu nimi pi lipu wawa tawa jan lawa e ilo nanpa.
	 * 
	 * @param pokiPiKulupuNimi li jo e lipu wawa lon kulupu nimi.
	 * @param nimiPiLipuWawa nimi pi lipu wawa
	 */
	void tokiELipuWawa(const std::vector<KulupuNimi>& pokiPiKulupuNimi, const std::string& nimiPiLipuWawa);
}
