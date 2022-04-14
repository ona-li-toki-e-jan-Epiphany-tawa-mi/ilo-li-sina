#pragma once

#include "../pali_pi_lipu_wawa_tan_kulupu_nimi/pali.hpp"

/**
 * ilo tawa lawa e ilo nanpa kepeken lipu wawa.
 */
namespace lawa {
	/**
	 * @brief li lawa e ilo nanpa kepeken lipu wawa.
	 * 
	 * li pali e poki pi poki nanpa ali pi jo e ala.
	 * 
	 * @param lipuWawa li tawa lawa.
	 * @param nimiPiLipuWawa nimi pi lipu wawa.
	 * @param nimiPiILO_LI_SINA nimi tawa ilo IloLiSina tan jan.
	 * 
	 * @return nanpa ike. li ken pali la ni li 0. ante la ni li 1, en, lipu wawa li ike.
	 */
	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA);

	/**
	 * @brief li lawa e ilo nanpa kepeken lipu wawa.
	 * 
	 * @param lipuWawa li tawa lawa.
	 * @param pokiPiPokiNanpaAli poki tawa poki nanpa ali tawa kepeken lon lipu wawa.
	 * @param nimiPiLipuWawa nimi pi lipu wawa.
	 * @param nimiPiILO_LI_SINA nimi tawa ilo IloLiSina tan jan.
	 * 
	 * @return nanpa ike. li ken pali la ni li 0. ante la ni li 1, en, lipu wawa li ike.
	 */
	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA);
}
