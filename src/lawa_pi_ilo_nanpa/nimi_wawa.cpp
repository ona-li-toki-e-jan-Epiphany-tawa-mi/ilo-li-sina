#include "nimi_wawa.hpp"
#include <iostream>

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
 * li toki e ijo e linja sin lon ilo pi pana nimi.
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
 * li kama jo e nimi tan jan.
 *
 * @param nanpaIjo nanpa ijo.
 * @param ijoTawaNi ijo tawa toki.
 *
 * @retval nimi tan jan.
 */
std::string kamaJoTanJan(size_t nanpaIjo, std::string* ijoTawaNi) {
	tokiKepekenLinjaSin(nanpaIjo, ijoTawaNi);

	std::string nimiTanJan;
	std::getline(std::cin, nimiTanJan);
	return nimiTanJan;
}

namespace lawa {
	const std::unordered_map<std::string, std::string(*)(size_t, std::string[])> pokiPiNimiWawaAli = {
			{"toki", toki},
			{"tokiELinja", tokiKepekenLinjaSin},
			{"kamaJoTanJan", kamaJoTanJan}
	};
}
