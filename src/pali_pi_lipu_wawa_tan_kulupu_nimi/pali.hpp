#pragma once

#include "../kipisi_pi_lipu_wawa/kulupu_nimi.hpp"
#include "kasiPiKasiSuliPiNimiWawa.hpp"

/**
 * ilo pali tawa pali e lipu wawa tan kulupu nimi tan kipisi.
 */
namespace pali {
	/**
	 * @breif li pali e lipu wawa tan kulupu nimi tan kipisi pi lipu wawa jan.
	 *
	 * @param kulupuNimi poki pi kulupu nimi tan kipisi tawa pali pi lipu wawa.
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni. li tawa toki e ike.
	 * @param nimiPiILO_LI_SINA nimi tawa ilo IloLiSina tan jan.
	 *
	 * @return poki pi lipu wawa.
	 */
	std::vector<std::shared_ptr<KasiPiKasiSuli>> paliELipuWawa(const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA);

	/**
	 * @breif li pana e lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param pokiTawaLipuWawa lipu wawa.
	 * @param nimiPiLipuWawa nimi pi lipu wawa.
	 */
	void tokiEKasiSuli(const std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const std::string& nimiPiLipuWawa);
}
