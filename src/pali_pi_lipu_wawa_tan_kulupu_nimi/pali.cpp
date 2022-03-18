#include "pali.hpp"
#include <iostream>
#include "../ike.hpp"

// TODO linja li jo ala e nimi wawa anu pana lon poki la o toki e ike.

namespace pali {
	/**
	 * @breif li kama jo e kulupu nimi pi lon ante.
	 *
	 * ni li kama jo e kulupu nimi pi lon ante.
	 * ona li lon ala la ni li toki e ike li pini e ali.
	 *
	 * @param kulupuNimi kulupu nimi pi lipu wawa.
	 * @param alasaPiKulupuNimi ilo alasa pi kulupu nimi.
	 * @param lonAnte ni li nanpa kulupu nimi lon sinpin pi lon pi ilo alasa pi tenpo ni lon monsi kulupi nimi wile.
	 *
	 * @retval kulupu nimi pi lon ante.
	 */
	const kipisi::KulupuNimi* kamaJoLonAnte(const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::vector<kipisi::KulupuNimi>::const_iterator& alasaPiKulupuNimi, int lonAnte) {
		auto kulupuNimiLonAnte = alasaPiKulupuNimi + lonAnte;

		if (kulupuNimiLonAnte == kulupuNimi.end())
			return nullptr;

		return &(*kulupuNimiLonAnte);
	}

	/**
	 * @breif li pali e kasi pi kasi suli tan kulupu nimi lon linja sitelen.
	 *
	 * ni li pali e kasi pi kasi suli tan kulupu nimi.
	 * ni li ken taso kama jo e kulupu pi nimi wawa en pana lon poki nimi.
	 * 	 sin la ona li wile nanpa 1 lon linja sitelen.
	 * ali ni li lon ala la o kepeken ala e ni a!
	 *
	 * @param kulupuNimi kulupu nimi tan lipu wawa.
	 * @param alasaPiKulupuNimi ilo alasa pi kulupu nimi. ni li lon pi kulupu nimi tawa pali.
	 * @param nanpaLinja kulupu ni li lon linja pi nanpa ni. li tawa toki e ike.
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni. li tawa toki e ike.
	 *
	 * @retval kasi pi kasi suli.
	 */
	KasiPiKasiSuli* paliEKasi(const std::vector<kipisi::KulupuNimi>& kulupuNimi, std::vector<kipisi::KulupuNimi>::const_iterator alasaPiKulupuNimi, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
		switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
			case kipisi::NimiPiKulupuNimi::PANA_LON_POKI_NANPA: {
				const kipisi::KulupuNimi* pokiNanpa = kamaJoLonAnte(kulupuNimi, alasaPiKulupuNimi, -1);
				if (pokiNanpa == nullptr) {
					ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, alasaPiKulupuNimi->kamaJoENanpaSitelen(), "Expected variable name before '=' token");
				} else if (pokiNanpa->nimiPiKulupuNimi != kipisi::NimiPiKulupuNimi::POKI_NANPA)
					ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, pokiNanpa->kamaJoENanpaSitelen(), "Expected variable name before '=' token");

				const kipisi::KulupuNimi* ijoTawaPoki = kamaJoLonAnte(kulupuNimi, alasaPiKulupuNimi, 1);
				if (pokiNanpa == nullptr) ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, alasaPiKulupuNimi->kamaJoENanpaSitelen(), "Expected secondary expression after '=' token");
				switch (ijoTawaPoki->nimiPiKulupuNimi) {
					case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
					case kipisi::NimiPiKulupuNimi::POKI_NANPA:
					case kipisi::NimiPiKulupuNimi::POKI_SITELEN:
						break;

					default:
						ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, ijoTawaPoki->kamaJoENanpaSitelen(), "Invalid secondary expression after '=' token. Must be or return some kind of value!");
				}

				return new KasiPiPanaLonPoki(pokiNanpa->kamaJoENimiPoki(), paliEKasi(kulupuNimi, alasaPiKulupuNimi + 1, nanpaLinja, nimiPiLipuWawa));
			}

			case kipisi::NimiPiKulupuNimi::POKI_NANPA: {
				return new KasiPiKamaJoTanPoki(alasaPiKulupuNimi->kamaJoENimiPoki());
			}

			case kipisi::NimiPiKulupuNimi::POKI_SITELEN: {
				return new KasiPiKamaJoTanPokiPiAnteAla(alasaPiKulupuNimi->kamaJoENimiPoki());
			}

			case kipisi::NimiPiKulupuNimi::NIMI_WAWA: {
				auto kulupuNimiPiNimiWawa = alasaPiKulupuNimi;
				std::vector<KasiPiKasiSuli*> pokiPiIjoTawaNimiWawa;
				unsigned int liLonNimiWawaPiNanpaNi = 0;

				for (alasaPiKulupuNimi += 2; alasaPiKulupuNimi != kulupuNimi.end(); alasaPiKulupuNimi++)  {
					const kipisi::KulupuNimi* ijoTawaPoki = kamaJoLonAnte(kulupuNimi, alasaPiKulupuNimi, 1);
					switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
						case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
						case kipisi::NimiPiKulupuNimi::POKI_NANPA:
						case kipisi::NimiPiKulupuNimi::POKI_SITELEN:
							if (liLonNimiWawaPiNanpaNi == 0)
								pokiPiIjoTawaNimiWawa.push_back(paliEKasi(kulupuNimi, alasaPiKulupuNimi, nanpaLinja, nimiPiLipuWawa));

							break;

						case kipisi::NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA:
							if (alasaPiKulupuNimi->kamaJoENimiPoki().at(0) == ')') {
								if (liLonNimiWawaPiNanpaNi == 0) {
									goto piniPiAlasaIjo;

								} else
									liLonNimiWawaPiNanpaNi--;

							} else
								liLonNimiWawaPiNanpaNi++;

							break;

						case kipisi::NimiPiKulupuNimi::LINJA_SITELEN_SIN:
							ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, alasaPiKulupuNimi->kamaJoENanpaSitelen(), "Unterminated function definition. Expected ending ')' symbol");

						default:
							ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, alasaPiKulupuNimi->kamaJoENanpaSitelen(), "Unexpected token");
					}
				}
			piniPiAlasaIjo:

				return new KasiPiNimiWawa(kulupuNimiPiNimiWawa->kamaJoENimiPoki(), pokiPiIjoTawaNimiWawa);
			}
		}

		return nullptr;
	}

	const std::vector<KasiPiKasiSuli*>& paliELipuWawa(std::vector<KasiPiKasiSuli*>& pokiTawaLipuWawa, const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa) {
		bool liPaliTanLinjaSitelen = false;
		size_t nanpaLinja = 1;

		for (auto alasaPiKulupuNimi = kulupuNimi.begin(); alasaPiKulupuNimi != kulupuNimi.end(); alasaPiKulupuNimi++) {
			switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
				// nimi wawa pi nanpa 1 en pana pi nanpa 1 lon poki nanpa li kulupu nimi suli suli lon linja sitelen li wile lon open pi kasi suli.
				case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
				case kipisi::NimiPiKulupuNimi::PANA_LON_POKI_NANPA:
					if (!liPaliTanLinjaSitelen) {
						pokiTawaLipuWawa.push_back(paliEKasi(kulupuNimi, alasaPiKulupuNimi, nanpaLinja, nimiPiLipuWawa));
						liPaliTanLinjaSitelen = true;
					}

					break;

				case kipisi::NimiPiKulupuNimi::LINJA_SITELEN_SIN:
					liPaliTanLinjaSitelen = false;
					nanpaLinja++;
			}
		}

		return pokiTawaLipuWawa;
	}



	/**
	 * @breif li pana e kasi pi kasi suli pi lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasi kasi pi kasi suli tawa pana.
	 * @param lonInsaPiNanpaNi kasi li lon insa pi kasi pi nanpa ni.
	 */
	void tokiEKasiPiKasiSuli(const KasiPiKasiSuli* kasi, int lonInsaPiNanpaNi) {
		for (int nanpa = 0; nanpa < lonInsaPiNanpaNi; nanpa++)
					std::cout << "  ";

		switch (kasi->kamaJoENimiKasi()) {
			case NimiKasi::PANA_LON_POKI: {
				const KasiPiPanaLonPoki* kasiPiPanaLonPoki = static_cast<const KasiPiPanaLonPoki*>(kasi);
				std::cout << "ASSIGN='" << kasiPiPanaLonPoki->kamaJoENimiPoki() << "':" << std::endl;
				tokiEKasiPiKasiSuli(kasiPiPanaLonPoki->kamaJoEIjoTawaPana(), lonInsaPiNanpaNi + 2);

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI: {
				const KasiPiKamaJoTanPoki* kasiPiKamaJoTanPoki = static_cast<const KasiPiKamaJoTanPoki*>(kasi);
				std::cout << "VARIABLE_GET='" << kasiPiKamaJoTanPoki->kamaJoENimiPoki() << "'" << std::endl;

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA: {
				const KasiPiKamaJoTanPokiPiAnteAla* kasiPiKamaJoTanPokiPiAnteAla = static_cast<const KasiPiKamaJoTanPokiPiAnteAla*>(kasi);
				std::cout << "CONST_GET='" << kasiPiKamaJoTanPokiPiAnteAla->kamaJoEIjoPoki() << "'" << std::endl;

				break;
			}

			case NimiKasi::NIMI_WAWA: {
				const KasiPiNimiWawa* kasiPiNimiWawa = static_cast<const KasiPiNimiWawa*>(kasi);
				std::cout << "FUNCTION='" << kasiPiNimiWawa->kamaJoENimiPiNimiWawa() << "':" << std::endl;
				for (KasiPiKasiSuli* kasiPiIjoTawaNimiWawa : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
					tokiEKasiPiKasiSuli(kasiPiIjoTawaNimiWawa, lonInsaPiNanpaNi + 2);

				break;
			}

			default:
				std::cout << "INVALID" << std::endl;
		}
	}

	void tokiEKasiSuli(const std::vector<KasiPiKasiSuli*>& pokiTawaLipuWawa) {
		for (KasiPiKasiSuli* kasi : pokiTawaLipuWawa) {
			tokiEKasiPiKasiSuli(kasi, 0);
		}
	}
}
