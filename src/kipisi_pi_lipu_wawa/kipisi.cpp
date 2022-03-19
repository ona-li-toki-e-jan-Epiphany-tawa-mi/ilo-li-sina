#include "kipisi.hpp"
#include <iostream>
#include <string>
#include <regex>
#include "../ike.hpp"

#define KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen) std::distance(linjaSitelen.begin(), alasaSitelen) + 1

namespace kipisi {
	const std::regex SITELEN_PI_LUKIN_ALA("\\s", std::regex_constants::optimize);
	const std::regex SITELEN_PI_POKI_NANPA("[a-zA-Z_0-9]", std::regex_constants::optimize);

	std::vector<KulupuNimi>& kipisiELipuWawa(std::vector<KulupuNimi>& pokiPiKulupuNimi, const std::string& nimiPiLipuWawa) {
		std::ifstream lipuWawa(nimiPiLipuWawa, std::ifstream::in);

		if (!lipuWawa.is_open()) {
			ike::tokiEIke(nimiPiLipuWawa, "Unable to open file");
			exit(-1);
		}


		std::string linjaSitelen;
		size_t nanpaLinja = 1;

		while (lipuWawa.good() && std::getline(lipuWawa, linjaSitelen)) {
			if (linjaSitelen.size() != 0)
				for (auto alasaSitelen = linjaSitelen.begin(); alasaSitelen != linjaSitelen.end(); alasaSitelen++) {
					switch (*alasaSitelen) {
						// li kama jo e nimi pi pana lon poki nanpa.
						case '=': {
							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::PANA_LON_POKI_NANPA, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));
							break;
						}

						// li kama jo e poki sitelen.
						case '"': {
							std::string pokiSitelen;
							bool liJoEPini = false;
							auto openPoki = alasaSitelen;

							alasaSitelen++;
							for (; alasaSitelen != linjaSitelen.end(); alasaSitelen++) {
								if (*alasaSitelen == '"') {
									alasaSitelen++;
									liJoEPini = true;

									break;
								}

								pokiSitelen.push_back(*alasaSitelen);
							}

							if (!liJoEPini)
								ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPoki), "Unterminated string!");

							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_SITELEN, std::move(pokiSitelen), KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPoki));

							alasaSitelen--;
							break;
						}

						// li kama jo e poki pi ijo tawa nimi wawa e nimi wawa.
						case '(':
						case ')': {
							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA, std::string(1, *alasaSitelen), KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));

							if (*alasaSitelen == '(') {
								bool liPaliENimiWawa = false;

								if (pokiPiKulupuNimi.size() > 1) {
									auto kulupuNimiLonMonsi = pokiPiKulupuNimi.end() - 2;

									if (kulupuNimiLonMonsi->nimiPiKulupuNimi == NimiPiKulupuNimi::POKI_NANPA) {
										kulupuNimiLonMonsi->nimiPiKulupuNimi = NimiPiKulupuNimi::NIMI_WAWA;
										liPaliENimiWawa = true;
									}
								}

								if (!liPaliENimiWawa)
									ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen), "Expected a function name before '('!");
							}

							break;
						}

						default:
							// li kama jo e poki nanpa.
							if (std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA)) {
								std::string nimiPiPokiNanpa(1, *alasaSitelen);

								alasaSitelen++;
								for (; alasaSitelen != linjaSitelen.end(); alasaSitelen++) {
									if (!std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA))
										break;

									nimiPiPokiNanpa.push_back(*alasaSitelen);
								}

								pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_NANPA, std::move(nimiPiPokiNanpa), KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));

								alasaSitelen--;
								break;
							}

							// li weka e sitelen pi lukin ala.
							if (std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_LUKIN_ALA))
								break;
					}
				}

			nanpaLinja++;
			pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::LINJA_SITELEN_SIN, linjaSitelen.size() + 1);
		}


		lipuWawa.close();
		return pokiPiKulupuNimi;
	}
}
