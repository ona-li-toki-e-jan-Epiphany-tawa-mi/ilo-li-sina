#include "kipisi.hpp"
#include <regex>
#include "../ijo_kepeken/ike.hpp"

#define KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen) std::distance(linjaSitelen.begin(), alasaSitelen) + 1

namespace kipisi {
	const std::regex SITELEN_PI_LUKIN_ALA("\\s", std::regex_constants::optimize);
	const std::regex SITELEN_PI_POKI_NANPA("[a-zA-Z_0-9]", std::regex_constants::optimize);
	const std::unordered_map<char, char> sitelenNasaTanNimi = {
		{'n', '\n'}, {'t', '\t'}, {'b', '\b'}, {'v', '\v'}, {'"', '"'}, {'\\', '\\'}};

	std::vector<KulupuNimi>& kipisiELipuWawa(std::vector<KulupuNimi>& pokiPiKulupuNimi, const std::string& nimiPiLipuWawa) {
		std::ifstream lipuWawa(nimiPiLipuWawa, std::ifstream::in);

		if (!lipuWawa.is_open()) {
			kepeken::tokiEIke(nimiPiLipuWawa, "Unable to open file");
			exit(-1);
		}


		std::string linjaSitelen;
		size_t nanpaLinja = 1;
		bool liLipuPiPonaAla = false;

		while (lipuWawa.good() && std::getline(lipuWawa, linjaSitelen)) {
			if (linjaSitelen.size() != 0)
				for (auto alasaSitelen = linjaSitelen.begin(); alasaSitelen != linjaSitelen.end(); alasaSitelen++) {
					switch (*alasaSitelen) {
						// li kama jo e nimi pi pana lon poki nanpa.
						case '=': {
							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::PANA_LON_POKI_NANPA, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));
							break;
						}

						// li kama jo e nimi pi nimi tawa tawa.
						case ':': {
							bool liPaliELonTawaTawa = false;
							if (pokiPiKulupuNimi.size() >= 1) {
								auto kulupuNimiLonMonsi = pokiPiKulupuNimi.end() - 1;

								if (kulupuNimiLonMonsi->nimiPiKulupuNimi == NimiPiKulupuNimi::POKI_NANPA) {
									kulupuNimiLonMonsi->nimiPiKulupuNimi = NimiPiKulupuNimi::NIMI_TAWA_TAWA;
									liPaliELonTawaTawa = true;
								}
							}

							if (!liPaliELonTawaTawa) {
								kepeken::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen), "Expected a label name before ':'!");
								liLipuPiPonaAla = true;
							}

							if (pokiPiKulupuNimi.size() >= 2 && (pokiPiKulupuNimi.end() - 2)->nimiPiKulupuNimi != NimiPiKulupuNimi::LINJA_SITELEN_SIN) {
								kepeken::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen - 1), "A label can only occur at the start of a line!");
								liLipuPiPonaAla = true;
							}

							break;
						}

						// li kama jo e poki sitelen.
						case '"': {
							std::string pokiSitelen;
							bool liJoEPini = false;
							const auto openPoki = alasaSitelen;

							alasaSitelen++;
							for (; alasaSitelen != linjaSitelen.end(); alasaSitelen++) {
								switch (*alasaSitelen) {
									// pini pi poki sitelen.
									case '"':
										alasaSitelen++;
										liJoEPini = true;
										goto liPiniPiPokiSitelen;

									// nimi pi sitelen nasa (sama \n anu \v).
									case '\\':
										alasaSitelen++;
										if (alasaSitelen == linjaSitelen.end())
											goto liPiniPiPokiSitelen;

										try {
											pokiSitelen.push_back(sitelenNasaTanNimi.at(*alasaSitelen));
										
										} catch (const std::out_of_range& liSuliAla) {	
											kepeken::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen - 1), std::string("Unknown escape sequence: \\") + *alasaSitelen);
											liLipuPiPonaAla = true;
										}

										continue;

									default:
										pokiSitelen.push_back(*alasaSitelen);
								}
							}
						liPiniPiPokiSitelen:

							if (!liJoEPini) {
								kepeken::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPoki), "Unterminated string");
								liLipuPiPonaAla = true;
							}

							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_SITELEN, pokiSitelen, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPoki));

							alasaSitelen--;
							break;
						}

						// li ken e ni: jan li sitelen e nimi pi wawa ala tawa toki e sona.
						case '#':
							goto liNimiPiWawaAla;

						// li kama jo e poki pi ijo tawa nimi wawa e nimi wawa.
						case '(':
						case ')': {
							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA, std::string(1, *alasaSitelen), KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));

							if (*alasaSitelen == '(') {
								bool liPaliENimiWawa = false;

								if (pokiPiKulupuNimi.size() > 1) {
									const auto kulupuNimiLonMonsi = pokiPiKulupuNimi.end() - 2;

									if (kulupuNimiLonMonsi->nimiPiKulupuNimi == NimiPiKulupuNimi::POKI_NANPA) {
										kulupuNimiLonMonsi->nimiPiKulupuNimi = NimiPiKulupuNimi::NIMI_WAWA;
										liPaliENimiWawa = true;
									}
								}

								if (!liPaliENimiWawa) {
									kepeken::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen), "Expected a function name before '('!");
									liLipuPiPonaAla = true;
								}
							}

							break;
						}

						default:
							// li kama jo e poki nanpa.
							if (std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA)) {
								std::string nimiPiPokiNanpa(1, *alasaSitelen);
								const auto openPiPokiNanpa = alasaSitelen;

								alasaSitelen++;
								for (; alasaSitelen != linjaSitelen.end(); alasaSitelen++) {
									if (!std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA))
										break;

									nimiPiPokiNanpa.push_back(*alasaSitelen);
								}

								pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_NANPA, nimiPiPokiNanpa, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPiPokiNanpa));

								alasaSitelen--;
								break;
							}

							// li weka e sitelen pi lukin ala.
							if (std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_LUKIN_ALA))
								break;

							kepeken::tokiEIke(nimiPiLipuWawa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen), std::string("Unknown symbol: ") + *alasaSitelen);
							liLipuPiPonaAla = true;
					}
				}
			liNimiPiWawaAla:

			nanpaLinja++;
			pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::LINJA_SITELEN_SIN, linjaSitelen.size() + 1);
		}


		if (liLipuPiPonaAla)
			exit(1);

		return pokiPiKulupuNimi;
	}
}
