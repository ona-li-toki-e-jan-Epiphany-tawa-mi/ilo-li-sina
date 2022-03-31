#pragma once

#include <vector>
#include <memory>
#include "../pali_pi_lipu_wawa_tan_kulupu_nimi/pali.hpp"

/**
 * ilo tawa lawa e ilo nanpa kepeken lipu wawa.
 */
namespace lawa {
	/**
	 * @breif li lawa e ilo nanpa kepeken lipu wawa.
	 * @param lipuWawa li tawa lawa.
	 */
	void lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa);
}
