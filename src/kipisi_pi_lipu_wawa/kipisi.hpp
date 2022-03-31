#pragma once

#include <fstream>
#include <vector>
#include "kulupu_nimi.hpp"

/**
 * ilo kipisi tawa kipisi pi lipu wawa pi toki "ilo li sina".
 */
namespace kipisi {
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
