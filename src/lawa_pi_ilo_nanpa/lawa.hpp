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
	 */
	void lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA);
}
