#include "kipisi.hpp"
#include <regex>
#include <iostream>
#include "../ijo_kepeken/ike.hpp"
#include "../ijo_kepeken/ijoTawaPokiMAP.hxx"
#include "../ante_toki/ante_toki.hpp"

#define KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen) static_cast<size_t>(std::distance(linjaSitelen.begin(), alasaSitelen)) + 1

namespace kipisi {
	const std::regex SITELEN_PI_LUKIN_ALA("\\s", std::regex_constants::optimize);
	const std::regex SITELEN_PI_POKI_NANPA("[a-zA-Z0-9_]", std::regex_constants::optimize);
	const std::unordered_map<char, char> sitelenNasaTanNimi = {
		{'n', '\n'}, {'t', '\t'}, {'b', '\b'}, {'v', '\v'}, {'"', '"'}, {'\\', '\\'}};

	std::tuple<std::optional<std::vector<KulupuNimi>>, int> kipisiELipuWawa(const std::string& nimiPiLipuWawa) {
		std::tuple<std::optional<std::vector<KulupuNimi>>, int> ijoTawaPana;

		
		std::ifstream lipuWawa(nimiPiLipuWawa);

		if (!lipuWawa.is_open()) {
			kepeken::tokiEIke({ 
				ante_toki::anteENimi(
					ante_toki::kamaJoENimiTawaJan("ike.kipisi.li_ken_ala_open_e_lipu"),
					"%s", nimiPiLipuWawa)});
			ijoTawaPana = {std::nullopt, -1};
			return ijoTawaPana;
		}


		std::vector<KulupuNimi> pokiPiKulupuNimi;
		std::string linjaSitelen;
		size_t nanpaLinja = 1;
		bool liLipuPiPonaAla = false;

		// ona li lon la li weka e sitelen BOM.
		std::getline(lipuWawa, linjaSitelen);
		if (linjaSitelen.compare(0, 3, "\xEF\xBB\xBF") == 0)
			linjaSitelen.erase(0, 3);

		do {
			if (linjaSitelen.size() != 0)
				for (auto alasaSitelen = linjaSitelen.begin(); alasaSitelen < linjaSitelen.end(); alasaSitelen++) {
					switch (*alasaSitelen) {
						// li kama jo e nimi pi pana lon poki nanpa.
						case '=': {
							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::PANA_LON_POKI_NANPA, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));
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
								kepeken::tokiEIke({
									nimiPiLipuWawa, 
									nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen), 
									ante_toki::kamaJoENimiTawaJan("ike.kipisi.nimi_tawa.nimi_li_wile")});
								liLipuPiPonaAla = true;
							}

							if (pokiPiKulupuNimi.size() >= 2 && (pokiPiKulupuNimi.end() - 2)->nimiPiKulupuNimi != NimiPiKulupuNimi::LINJA_SITELEN_SIN) {
								kepeken::tokiEIke({
									nimiPiLipuWawa, 
									nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen - 1), 
									ante_toki::kamaJoENimiTawaJan("ike.kipisi.nimi_tawa.li_ken_lon_open_linja_taso")});
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
							for (; alasaSitelen < linjaSitelen.end(); alasaSitelen++) {
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
										
										} catch (const std::out_of_range& liSitelenAlaTawaSitelenNasa) {	
											kepeken::tokiEIke({
												nimiPiLipuWawa, 
												nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen - 1), 
												ante_toki::anteENimi(
													ante_toki::kamaJoENimiTawaJan("ike.kipisi.poki_nimi.nimi_pi_sitelen_nasa_pi_sona_ala"),
													"%s", std::string(1, *alasaSitelen))});
											liLipuPiPonaAla = true;
										}

										continue;

									default:
										pokiSitelen.push_back(*alasaSitelen);
								}
							}
						liPiniPiPokiSitelen:

							if (!liJoEPini) {
								kepeken::tokiEIke({
									nimiPiLipuWawa, 
									nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPoki), 
									ante_toki::kamaJoENimiTawaJan("ike.kipisi.poki_nimi.li_jo_ala_e_pini")});
								liLipuPiPonaAla = true;
							}

							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_SITELEN, pokiSitelen, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPoki));

							alasaSitelen--;
							break;
						}

						// li ken e ni: jan li sitelen e nimi pi wawa ala tawa toki e sona.
						case '#':
							goto liNimiPiWawaAla;

						// li ken e ni: jan li sitelen e ijo lon linja mute.
						case '\\':
							goto linjaSinLiWileAla;

						// li kama jo e poki pi ijo tawa nimi wawa e nimi wawa.
						case '(':
						case ')': {
							pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA, std::string(1, *alasaSitelen), nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen));

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
									kepeken::tokiEIke({
										nimiPiLipuWawa, 
										nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen), 
										ante_toki::kamaJoENimiTawaJan("ike.kipisi.nimi_wawa.nimi_li_wile")});
									liLipuPiPonaAla = true;
								}
							}

							break;
						}

						default:
							// li kama jo e poki nanpa.
							// sitelen li lon ala kulupu ASCII la ona li ken lon nimi pi poki nanpa. '& 0b1000_0000' li alasa e ona.
							if ((*alasaSitelen & 0b10000000) != 0
									|| std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA)) {
								std::string nimiPiPokiNanpa(1, *alasaSitelen);
								const auto openPiPokiNanpa = alasaSitelen;

								alasaSitelen++;
								for (; alasaSitelen < linjaSitelen.end(); alasaSitelen++) {
									if ((*alasaSitelen & 0b10000000) == 0
											&& !std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA))
										break;

									nimiPiPokiNanpa.push_back(*alasaSitelen);
								}

								pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::POKI_NANPA, nimiPiPokiNanpa, nanpaLinja, KAMA_JO_E_NANPA_SITELEN(linjaSitelen, openPiPokiNanpa));

								alasaSitelen--;
								break;
							}

							// li weka e sitelen pi lukin ala.
							if (std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_LUKIN_ALA))
								break;



							// li toki e sitelen ike.
							size_t lonSitelen = KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen);
							size_t suliSitelen = ante_toki::UTF8LaKamaJoESuliSitelen(linjaSitelen, lonSitelen - 1);

							alasaSitelen += suliSitelen;

							kepeken::tokiEIke({
								nimiPiLipuWawa, 
								nanpaLinja, lonSitelen, 
								ante_toki::anteENimi(
									ante_toki::kamaJoENimiTawaJan("ike.kulupu_nimi_pi_wile_ala"),
									"%s", linjaSitelen.substr(lonSitelen - 1, suliSitelen))});
							liLipuPiPonaAla = true;
					}
				}
		liNimiPiWawaAla:

			pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::LINJA_SITELEN_SIN, nanpaLinja, linjaSitelen.size() + 1);
		linjaSinLiWileAla:
			nanpaLinja++;

		} while (lipuWawa.good() && std::getline(lipuWawa, linjaSitelen));

		if (!pokiPiKulupuNimi.empty() && pokiPiKulupuNimi.back().nimiPiKulupuNimi != NimiPiKulupuNimi::LINJA_SITELEN_SIN)
			pokiPiKulupuNimi.emplace_back(NimiPiKulupuNimi::LINJA_SITELEN_SIN, nanpaLinja, linjaSitelen.size() + 1);


		if (liLipuPiPonaAla) {
			ijoTawaPana = {std::nullopt, 1};

		} else
			ijoTawaPana = {std::move(pokiPiKulupuNimi), 0};

		return ijoTawaPana;
	}



	const std::unordered_map<char, char>& kamaJoEPokiPiNimiTanSitelenNasa() {
		static std::optional<std::unordered_map<char, char>> nimiTanSitelenNasa = std::nullopt;

		if (!nimiTanSitelenNasa.has_value())
			nimiTanSitelenNasa = std::optional(kepeken::paliEPokiMAPLonNasinAnte(kipisi::sitelenNasaTanNimi));

		return *nimiTanSitelenNasa;
	}

	void tokiELipuWawa(const std::vector<KulupuNimi>& pokiPiKulupuNimi, const std::string& nimiPiLipuWawa) {
		static const std::string sitelenAlaLonMonsi(8, ' ');
		const std::string sinpin(nimiPiLipuWawa.size() + 2, '-');

		std::cout << '/' << sinpin << "\\\n"
			<< "| " << nimiPiLipuWawa << " |\n" 
			<< '\\' << sinpin << "/\n";
		
		if (!pokiPiKulupuNimi.empty()) {
			size_t nanpaLinja = 1;
			std::cout << ante_toki::anteENimi(
				ante_toki::kamaJoENimiTawaJan("toki.nanpa_linja"),
				"%d", std::to_string(nanpaLinja))
				<< ":\n";

			for (auto alasaPiKulupuNimi = pokiPiKulupuNimi.cbegin(); alasaPiKulupuNimi < pokiPiKulupuNimi.cend(); alasaPiKulupuNimi++) {
				std::cout << sitelenAlaLonMonsi << kamaJoENimiPiNimiKulupu(alasaPiKulupuNimi->nimiPiKulupuNimi) << "=\"";

				for (const char sitelen : alasaPiKulupuNimi->kamaJoENimiPoki())
					try {
						const char sitelenNasa = kamaJoEPokiPiNimiTanSitelenNasa().at(sitelen);
						std::cout << '\\' << sitelenNasa;

					} catch (const std::out_of_range& liSitelenNasaAla) {
						std::cout << sitelen;
					}

				std::cout << "\"\n";


				if (alasaPiKulupuNimi->nimiPiKulupuNimi == NimiPiKulupuNimi::LINJA_SITELEN_SIN && alasaPiKulupuNimi != pokiPiKulupuNimi.cend() - 1)
					std::cout << ante_toki::anteENimi(
						ante_toki::kamaJoENimiTawaJan("toki.nanpa_linja"),
						"%d", std::to_string(++nanpaLinja))
						<< ":\n";
			}

		} else
			std::cout << '\n' << ante_toki::kamaJoENimiTawaJan("toki.li_jo_e_ala") << "\n\n";

		std::cout << "\\" << sinpin << "/\n";
	}
}
