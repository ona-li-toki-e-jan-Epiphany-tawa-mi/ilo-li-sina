#include "nimi_wawa.hpp"
#include <iostream>
#include <algorithm>
#include <utility>

/**
 * @breif li toki e ijo lon ilo pi pana nimi.
 *
 * @param nanpaIjo nanpa ijo.
 * @param ijoTawaNi ijo tawa toki.
 */
std::string toki(size_t nanpaIjo, std::string* ijoTawaNi) {
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
std::string tokiKepekenLinjaSin(size_t nanpaIjo, std::string* ijoTawaNi) {
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
std::string kamaJoTanJan(size_t nanpaIjo, std::string* ijoTawaNi) {
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
std::string wan(size_t nanpaIjo, std::string* ijoTawaNi) {
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

	std::optional<const std::string> kamaJoENimiTanNimiWawa(nimi_wawa nimiWawa) {
		auto alasaNimi = std::find_if(pokiPiNimiWawaAli.cbegin(), pokiPiNimiWawaAli.cend(), [nimiWawa](const std::pair<std::string, nimi_wawa>& nimiWawaEnNimi) {
			return nimiWawa == nimiWawaEnNimi.second;
		});

		if (alasaNimi == pokiPiNimiWawaAli.end())
			return {};

		return (*alasaNimi).first;
	}
}
