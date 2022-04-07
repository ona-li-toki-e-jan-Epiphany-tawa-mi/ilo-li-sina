#include "nimi_wawa.hpp"
#include <iostream>
#include <algorithm>
#include <optional>
#include "../ijo_kepeken/ijoTawaPokiMAP.hpp"

/**
 * @breif li toki e ijo lon ilo pi pana nimi.
 *
 * @param nanpaIjo nanpa ijo.
 * @param ijoTawaNi ijo tawa toki.
 */
std::string toki(const size_t nanpaIjo, const std::string *const ijoTawaNi) {
	for (size_t nanpa = 0; nanpa < nanpaIjo; nanpa++)
		std::cout << ijoTawaNi[nanpa];

	return "";
}

/**
 * @breif li toki e ijo e linja sin lon ilo pi pana nimi.
 *
 * @param nanpaIjo nanpa ijo.
 * @param ijoTawaNi ijo tawa toki.
 */
std::string tokiKepekenLinjaSin(const size_t nanpaIjo, const std::string *const ijoTawaNi) {
	toki(nanpaIjo, ijoTawaNi);
	std::cout << '\n';

	return "";
}

/**
 * @breif li kama jo e nimi tan jan.
 *
 * @param nanpaIjo nanpa ijo.
 * @param ijoTawaNi ijo tawa toki.
 *
 * @return nimi tan jan.
 */
std::string kamaJoTanJan(const size_t nanpaIjo, const std::string *const ijoTawaNi) {
	if (nanpaIjo != 0)
		tokiKepekenLinjaSin(nanpaIjo, ijoTawaNi);

	std::string nimiTanJan;
	std::getline(std::cin, nimiTanJan);
	return nimiTanJan;
}

/**
 * @brief li wan e ijo.
 * 
 * @param nanpaIjo nanpa ijo.
 * @param ijoTawaNi ijo ni li kama wan.
 * 
 * @return std::string ijo wan tan ijo mute.
 */
std::string wan(const size_t nanpaIjo, const std::string *const ijoTawaNi) {
	std::string pokiSitelenSin;

	for (size_t nanpa = 0; nanpa < nanpaIjo; nanpa++)
		pokiSitelenSin += ijoTawaNi[nanpa];

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
