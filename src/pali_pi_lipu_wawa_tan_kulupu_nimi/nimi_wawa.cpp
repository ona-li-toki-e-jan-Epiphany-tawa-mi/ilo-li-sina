#include "nimi_wawa.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstring>
#include "../ijo_kepeken/ijoTawaPokiMAP.hpp"
#include "../ijo_kepeken/ike.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace pali {
	/**
	 * @brief li toki e ijo lon lupa pana.
	 * 
	 * @param lupaTawaToki  li toki e ijo lon lupa ni (lupa sama Stdout).
	 * @param ijoTawaToki 	ijo ni li toki.
	 */
	void tokiEIjo(std::ostream& lupaTawaToki, pali::string_lqueue& ijoTawaToki) {
		while (!ijoTawaToki.empty()) {
			lupaTawaToki << ijoTawaToki.front();
			ijoTawaToki.pop();
		}
	}

	/**
	 * @brief li toki e ijo lon ilo pi pana nimi lon lupa Stdin.
	 *
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		ijo tawa toki.
	 */
	std::optional<std::string> toki(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		tokiEIjo(std::cout, ijoTawaNi);
		return "";
	}

	/**
	 * @brief li toki e ijo e linja sin lon ilo pi pana nimi lon lupa Stdin.
	 *
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		ijo tawa toki.
	 */
	std::optional<std::string> tokiKepekenLinjaSin(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		tokiEIjo(std::cout, ijoTawaNi);
		std::cout << '\n';

		return "";
	}

	/**
	 * @brief li toki e ijo lon ilo pi pana nimi lon lupa Stderr.
	 *
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		ijo tawa toki.
	 */
	std::optional<std::string> tokiEIke(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		tokiEIjo(std::cerr, ijoTawaNi);
		return "";
	}

	/**
	 * @brief li toki e ijo e linja sin lon ilo pi pana nimi lon lupa Stderr.
	 *
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		ijo tawa toki.
	 */
	std::optional<std::string> tokiEIkeKepekenLinjaSin(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		tokiEIjo(std::cerr, ijoTawaNi);
		std::cerr << '\n';

		return "";
	}

	/**
	 * @brief li kama jo e nimi tan jan.
	 *
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		ijo tawa toki.
	 *
	 * @return 				nimi tan jan.
	 * @retval std::nullopt li ken ala kama jo e nimi.
	 */
	std::optional<std::string> kamaJoTanJan(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		if (!ijoTawaNi.empty())
			tokiKepekenLinjaSin(nimiPiLipuWawa, lonKasi, ijoTawaNi);

		std::string nimiTanJan;
		if (!std::getline(std::cin, nimiTanJan)) {
			kepeken::tokiEIke({
				nimiPiLipuWawa,
				lonKasi,
				"kamaJoTanJan(): " + ante_toki::kamaJoENimiTawaJan("ike.lawa.pini_lipu")});

			return std::nullopt;
		}

		return nimiTanJan;
	}

	/**
	 * @brief li wan e ijo.
	 * 
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		ijo ni li kama wan.
	 * 
	 * @return ijo wan tan ijo mute.
	 */
	std::optional<std::string> wan(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		std::string pokiSitelenSin;

		while (!ijoTawaNi.empty()) {
			pokiSitelenSin.append(ijoTawaNi.front());
			ijoTawaNi.pop();
		}

		return pokiSitelenSin;
	}

	/**
	 * @brief lon tenpo pana la li awen li pali e ala.
	 *
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi 		tenpo tawa awen. nimi ni li wile sama nanpa. nanpa ni li wan.
	 *
	 * @retval std::nullopt nimi pi 1 anu mute li sama ala nanpa.
	 */
	std::optional<std::string> awen(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		// li weka e ijo tan lupa tawa ni: sitelen ali lon ona li kama lon ilo CLI pi pana sitelen.
		std::cout.flush();
		std::cerr.flush();
		
		while (!ijoTawaNi.empty()) {
			const std::string& ijo = ijoTawaNi.front();

			try {
				// nimi li jo e ala la li pona. ni la mi wile ala toki e ike.
				if (!ijo.empty())
					std::this_thread::sleep_for(std::chrono::milliseconds(
						std::stoi(ijo)));

			} catch (const std::invalid_argument& nanpaAla) {
				kepeken::tokiEIke({
					nimiPiLipuWawa,
					lonKasi,
					"awen(): " + ante_toki::anteENimi(
						ante_toki::kamaJoENimiTawaJan("ike.lawa.awen.nanpa_ala"),
						"%s", ijo)});

				return std::nullopt;

			} catch (const std::out_of_range& nanpaIke) {
				kepeken::tokiEIke({
					nimiPiLipuWawa,
					lonKasi,
					"awen(): " + ante_toki::anteENimi(
						ante_toki::kamaJoENimiTawaJan("ike.lawa.awen.nanpa_ike"),
						"%s", ijo)});
				
				return std::nullopt;
			}

			ijoTawaNi.pop();
		}

		return "";
	}

	std::optional<std::string> kamaJoEPokiNanpaPiLawaOS(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi) {
		const char* pokiNanpaPiLawaOS = nullptr;

		while (!ijoTawaNi.empty()) {
			pokiNanpaPiLawaOS = getenv(ijoTawaNi.front().c_str());

			if (pokiNanpaPiLawaOS != nullptr && strcmp(pokiNanpaPiLawaOS, "") != 0)
				break;

			ijoTawaNi.pop();
		}

		return pokiNanpaPiLawaOS != nullptr ? pokiNanpaPiLawaOS : "";
	}

	const std::unordered_map<std::string, nimi_wawa> pokiPiNimiWawaAli = {
			{"toki", 		   &toki},
			{"tokiELinja", 	   &tokiKepekenLinjaSin},
			{"tokiEIke",	   &tokiEIke},
			{"tokiEIkeELinja", &tokiEIkeKepekenLinjaSin},

			{"kamaJoTanJan",   &kamaJoTanJan},


			{"wan", 		   &wan},


			{"awen",		   &awen},
			{"pokiPiLawaOS",   &kamaJoEPokiNanpaPiLawaOS}
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
