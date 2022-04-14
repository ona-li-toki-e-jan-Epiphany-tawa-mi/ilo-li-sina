#pragma once

#include "../pali_pi_lipu_wawa_tan_kulupu_nimi/pali.hpp"

/**
 * ilo tawa lawa e ilo nanpa kepeken lipu wawa.
 */
namespace lawa {
	/**
	 * @breif li lawa e ilo nanpa kepeken lipu wawa.
	 * 
	 * @param lipuWawa li tawa lawa.
	 * @param nimiPiLipuWawa nimi pi lipu wawa.
	 * 
	 * @return nanpa ike. li ken pali la ni li 0. ante la ni li 1, en, lipu wawa li ike.
	 */
	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA);
}
