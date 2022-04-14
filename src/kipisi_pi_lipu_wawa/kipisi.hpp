#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <optional>
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
	 * @breif li kipisi e lipu wawa li pali e kulupu nimi tan kipisi.
	 *
	 * @param nimiPiLipuWawa nimi pi lipu wawa tawa kipisi.
	 * @param nimiPiILO_LI_SINA nimi tawa ilo IloLiSina tan jan.
	 *
	 * @return std::optional<std::vector<KulupuNimi>> poki pi kulupu nimi pi lipu wawa.
	 * @return int nanpa ike. li ken kipisi la ni li 0. ante la ni li 1, en, lipu wawa li ike.
	 */
	std::tuple<std::optional<std::vector<KulupuNimi>>, int> kipisiELipuWawa(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA);

	/**
	 * @brief li toki e kulupu nimi pi lipu wawa tawa jan lawa e ilo nanpa.
	 * 
	 * @param pokiPiKulupuNimi li jo e lipu wawa lon kulupu nimi.
	 * @param nimiPiLipuWawa nimi pi lipu wawa
	 */
	void tokiELipuWawa(const std::vector<KulupuNimi>& pokiPiKulupuNimi, const std::string& nimiPiLipuWawa);
}
