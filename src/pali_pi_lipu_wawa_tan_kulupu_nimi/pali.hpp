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
	 * @param pokiTawaLipuWawa poki tawa poki e ijo pi lipu wawa pini.
	 * @param kulupuNimi poki pi kulupu nimi tan kipisi tawa pali pi lipu wawa.
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni. li tawa toki e ike.
	 *
	 * @return pokiTawaLipuWawa;
	 */
	const std::vector<std::shared_ptr<KasiPiKasiSuli>>& paliELipuWawa(std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa);

	/**
	 * @breif li pana e lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param pokiTawaLipuWawa lipu wawa.
	 */
	void tokiEKasiSuli(const std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa);
}
