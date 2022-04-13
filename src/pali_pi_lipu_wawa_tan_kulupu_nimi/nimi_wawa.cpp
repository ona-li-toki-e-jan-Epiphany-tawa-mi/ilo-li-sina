#include "nimi_wawa.hpp"
#include <iostream>
#include <algorithm>
#include <optional>
#include "../ijo_kepeken/ijoTawaPokiMAP.hpp"

/**
 * @brief li toki e ijo lon ilo pi pana nimi.
 *
 * @param ijoTawaNi ijo tawa toki.
 */
std::string toki(pali::string_lqueue& ijoTawaNi) {
	while (!ijoTawaNi.empty()) {
		std::cout << ijoTawaNi.front();
		ijoTawaNi.pop();
	}

	return "";
}

/**
 * @brief li toki e ijo e linja sin lon ilo pi pana nimi.
 *
 * @param ijoTawaNi ijo tawa toki.
 */
std::string tokiKepekenLinjaSin(pali::string_lqueue& ijoTawaNi) {
	toki(ijoTawaNi);
	std::cout << '\n';

	return "";
}

/**
 * @brief li kama jo e nimi tan jan.
 *
 * @param ijoTawaNi ijo tawa toki.
 *
 * @return nimi tan jan.
 */
std::string kamaJoTanJan(pali::string_lqueue& ijoTawaNi) {
	if (!ijoTawaNi.empty())
		tokiKepekenLinjaSin(ijoTawaNi);

	std::string nimiTanJan;
	std::getline(std::cin, nimiTanJan);
	return nimiTanJan;
}

/**
 * @brief li wan e ijo.
 * 
 * @param ijoTawaNi ijo ni li kama wan.
 * 
 * @return ijo wan tan ijo mute.
 */
std::string wan(pali::string_lqueue& ijoTawaNi) {
	std::string pokiSitelenSin;

	while (!ijoTawaNi.empty()) {
		pokiSitelenSin.append(ijoTawaNi.front());
		ijoTawaNi.pop();
	}

	return pokiSitelenSin;
}

namespace pali {
	const std::unordered_map<std::string, nimi_wawa> pokiPiNimiWawaAli = {
			{"toki", toki},
			{"tokiELinja", tokiKepekenLinjaSin},
			{"kamaJoTanJan", kamaJoTanJan},
			{"wan", wan}
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
