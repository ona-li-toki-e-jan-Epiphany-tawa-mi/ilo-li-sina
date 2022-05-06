#include "nimi_wawa.hpp"
#include <iostream>
#include <algorithm>
#include "../ijo_kepeken/ijoTawaPokiMAP.hpp"
#include "../ijo_kepeken/ike.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace pali {
	/**
	 * @brief li toki e ijo lon ilo pi pana nimi.
	 *
	 * @param nimiPiILO_LI_SINA nimi pi lipu "ilo li sina".
	 * @param ijoTawaNi 		ijo tawa toki.
	 */
	std::optional<std::string> toki(const std::string& nimiPiILO_LI_SINA, pali::string_lqueue& ijoTawaNi) {
		while (!ijoTawaNi.empty()) {
			std::cout << ijoTawaNi.front();
			ijoTawaNi.pop();
		}

		return "";
	}

	/**
	 * @brief li toki e ijo e linja sin lon ilo pi pana nimi.
	 *
	 * @param nimiPiILO_LI_SINA nimi pi lipu "ilo li sina".
	 * @param ijoTawaNi 		ijo tawa toki.
	 */
	std::optional<std::string> tokiKepekenLinjaSin(const std::string& nimiPiILO_LI_SINA, pali::string_lqueue& ijoTawaNi) {
		toki(nimiPiILO_LI_SINA, ijoTawaNi);
		std::cout << '\n';

		return "";
	}

	/**
	 * @brief li kama jo e nimi tan jan.
	 *
	 * @param nimiPiILO_LI_SINA nimi pi lipu "ilo li sina".
	 * @param ijoTawaNi 		ijo tawa toki.
	 *
	 * @return 				nimi tan jan.
	 * @retval std::nullopt li ken ala kama jo e nimi.
	 */
	std::optional<std::string> kamaJoTanJan(const std::string& nimiPiILO_LI_SINA, pali::string_lqueue& ijoTawaNi) {
		if (!ijoTawaNi.empty())
			tokiKepekenLinjaSin(nimiPiILO_LI_SINA, ijoTawaNi);

		std::string nimiTanJan;
		if (!std::getline(std::cin, nimiTanJan)) {
			kepeken::tokiEIke(
				nimiPiILO_LI_SINA, 
				ante_toki::kamaJoENimiTawaJan("ike.lawa.pini_lipu"));

			return std::nullopt;
		}

		return nimiTanJan;
	}

	/**
	 * @brief li wan e ijo.
	 * 
	 * @param nimiPiILO_LI_SINA nimi pi lipu "ilo li sina".
	 * @param ijoTawaNi 		ijo ni li kama wan.
	 * 
	 * @return ijo wan tan ijo mute.
	 */
	std::optional<std::string> wan(const std::string& nimiPiILO_LI_SINA, pali::string_lqueue& ijoTawaNi) {
		std::string pokiSitelenSin;

		while (!ijoTawaNi.empty()) {
			pokiSitelenSin.append(ijoTawaNi.front());
			ijoTawaNi.pop();
		}

		return pokiSitelenSin;
	}

	std::optional<std::string> kamaJoEPokiNanpaPiLawaOS(const std::string& nimiPiILO_LI_SINA, pali::string_lqueue& ijoTawaNi) {
		const char* pokiNanpaPiLawaOS = nullptr;

		while (!ijoTawaNi.empty()) {
			pokiNanpaPiLawaOS = getenv(ijoTawaNi.front().c_str());

			if (pokiNanpaPiLawaOS != nullptr)
				break;

			ijoTawaNi.pop();
		}

		return pokiNanpaPiLawaOS != nullptr ? pokiNanpaPiLawaOS : "";
	}

	const std::unordered_map<std::string, nimi_wawa> pokiPiNimiWawaAli = {
			{"toki", 		 &toki},
			{"tokiELinja", 	 &tokiKepekenLinjaSin},
			{"kamaJoTanJan", &kamaJoTanJan},
			{"wan", 		 &wan},
			{"pokiPiLawaOS", &kamaJoEPokiNanpaPiLawaOS}
	};
	
	/**
	 * poki li wile la nimi wawa ni li pali e ona.
	 * 
	 * @return poki Map pi nimi pi nimi wawa lon nasin ante. 
	 */
	const std::unordered_map<nimi_wawa, std::string>& kamaJoEPokiPiNimiPiNimiWawa() {
		static std::optional<std::unordered_map<nimi_wawa, std::string>> pokiPiNimiPiNimiWawa = std::nullopt;

		if (!pokiPiNimiPiNimiWawa.has_value())
			pokiPiNimiPiNimiWawa = std::optional(kepeken::paliEPokiMAPLonNasinAnte(pokiPiNimiWawaAli));

		return *pokiPiNimiPiNimiWawa;
	}
}
