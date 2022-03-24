#include "pali.hpp"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include "../ike.hpp"

// TODO linja li jo ala e nimi wawa anu pana lon poki la o toki e ike.
// TODO o kepeken e poki "shared_pointer" tawa poki e kasi.

namespace pali {
	/**
	 * li kepeken tawa poki e nimi wawa tawa e nimi wawa ona.
	 */
	struct IjoTawaTawa {
		public:
			IjoTawaTawa(std::string nimiPiNimiTawaTawa, KasiTawa* nimiWawaTawaTawa)
				: nimiPiNimiTawaTawa(nimiPiNimiTawaTawa), nimiWawaTawaTawa(nimiWawaTawaTawa) {}

			std::string nimiPiNimiTawaTawa;
			KasiTawa* nimiWawaTawaTawa;
	};

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
	 * @return kulupu nimi pi lon ante.
	 * @retval nullptr kulupu nimi pi lon ante li lon ala la.
	 */
	const kipisi::KulupuNimi* kamaJoLonAnte(const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::vector<kipisi::KulupuNimi>::const_iterator& alasaPiKulupuNimi, int lonAnte) {
		auto kulupuNimiLonAnte = alasaPiKulupuNimi + lonAnte;

		if (kulupuNimiLonAnte == kulupuNimi.end())
			return nullptr;

		return &(*kulupuNimiLonAnte);
	}

	/**
	 * @brief li pali e kasi sin pi tawa ken.
	 * 
	 * @param kulupuNimiPiNimiWawa lon pi nimi wawa "niLaTawa" lon poki pi kulupu nimi.
	 * @param pokiPiIjoTawaNimiWawa poki pi ijo tawa nimi wawa.
	 * @param nimiWawaTawaTawa poki tawa nimi wawa ni: ona li kama lon lon ante
	 * @param nanpaLinja kulupu ni li lon linja pi nanpa ni. li tawa toki e ike.
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni. li tawa toki e ike.
	 * 
	 * @return kasi sin pi tawa ken.
	 */
	KasiPiTawaKen* paliEKasiPiTawaKen(const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::vector<KasiPiKasiSuli*>& pokiPiIjoTawaNimiWawa, std::vector<IjoTawaTawa>& nimiWawaTawaTawa, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
		if (pokiPiIjoTawaNimiWawa.size() < 3)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, kulupuNimiPiNimiWawa->kamaJoENanpaSitelen(), "Insufficient arguments for function 'niLaTawa'\n\tExpected: (label, yesMessage, noMessage [, messages...])");

		if (pokiPiIjoTawaNimiWawa.at(0)->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, (kulupuNimiPiNimiWawa+2)->kamaJoENanpaSitelen(), "Invalid label name. Expected token matching [a-zA-Z0-9_]");

		std::string nimiPiKasiTawaTawa = static_cast<KasiPiKamaJoTanPoki*>(pokiPiIjoTawaNimiWawa.at(0))->kamaJoENimiPoki();
		delete pokiPiIjoTawaNimiWawa.at(0);
		KasiPiKasiSuli* kasiLon = pokiPiIjoTawaNimiWawa.at(1);
		KasiPiKasiSuli* kasiPiLonAla = pokiPiIjoTawaNimiWawa.at(2);
		pokiPiIjoTawaNimiWawa.erase(pokiPiIjoTawaNimiWawa.begin(), pokiPiIjoTawaNimiWawa.begin() + 3);

		KasiPiTawaKen* kasiPiPaliKen = new KasiPiTawaKen(kasiLon, kasiPiLonAla, pokiPiIjoTawaNimiWawa);
		nimiWawaTawaTawa.emplace_back(nimiPiKasiTawaTawa, kasiPiPaliKen);
		return kasiPiPaliKen;
	}

	/**
	 * @brief li pali e kasi tawa sin.
	 * 
	 * @param kulupuNimiPiNimiWawa lon pi nimi wawa "niLaTawa" lon poki pi kulupu nimi.
	 * @param pokiPiIjoTawaNimiWawa poki pi ijo tawa nimi wawa.
	 * @param nimiWawaTawaTawa poki tawa nimi wawa ni: ona li kama lon lon ante
	 * @param nanpaLinja kulupu ni li lon linja pi nanpa ni. li tawa toki e ike.
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni. li tawa toki e ike.
	 * 
	 * @return kasi tawa sin.
	 */
	KasiTawa* paliEKasiTawa(const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::vector<KasiPiKasiSuli*>& pokiPiIjoTawaNimiWawa, std::vector<IjoTawaTawa>& nimiWawaTawaTawa, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
		if (pokiPiIjoTawaNimiWawa.size() != 1)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, kulupuNimiPiNimiWawa->kamaJoENanpaSitelen(), "Incorrect number of arguments for function 'tawa'\n\tExpected: tawa(label)");
				
		if (pokiPiIjoTawaNimiWawa.at(0)->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, (kulupuNimiPiNimiWawa+2)->kamaJoENanpaSitelen(), "Invalid label name. Expected token matching [a-zA-Z0-9_]");

		KasiTawa* kasiTawa = new KasiTawa();
		nimiWawaTawaTawa.emplace_back(static_cast<KasiPiPanaLonPoki*>(pokiPiIjoTawaNimiWawa.at(0))->kamaJoENimiPoki(), kasiTawa);
		return kasiTawa;
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
	 * @param nimiWawaTawaTawa poki tawa nimi wawa ni: ona li kama lon lon ante
	 * @param nanpaLinja kulupu ni li lon linja pi nanpa ni. li tawa toki e ike.
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni. li tawa toki e ike.
	 * 
	 * @return kasi sin pi kasi suli.
	 * @retval nullptr ni li ken ala pali e kasi la.
	 */
	KasiPiKasiSuli* paliEKasi(const std::vector<kipisi::KulupuNimi>& kulupuNimi, std::vector<kipisi::KulupuNimi>::const_iterator alasaPiKulupuNimi, std::vector<IjoTawaTawa>& nimiWawaTawaTawa, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
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


				return new KasiPiPanaLonPoki(pokiNanpa->kamaJoENimiPoki(), paliEKasi(kulupuNimi, alasaPiKulupuNimi + 1, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa));
			}

			case kipisi::NimiPiKulupuNimi::POKI_NANPA:
				return new KasiPiKamaJoTanPoki(alasaPiKulupuNimi->kamaJoENimiPoki());

			case kipisi::NimiPiKulupuNimi::POKI_SITELEN: 
				return new KasiPiKamaJoTanPokiPiAnteAla(alasaPiKulupuNimi->kamaJoENimiPoki());

			case kipisi::NimiPiKulupuNimi::NIMI_WAWA: {
				auto kulupuNimiPiNimiWawa = alasaPiKulupuNimi;
				std::vector<KasiPiKasiSuli*> pokiPiIjoTawaNimiWawa;
				unsigned int liLonNimiWawaPiNanpaNi = 0;

				// li kama jo e ijo tawa nimi wawa.
				for (alasaPiKulupuNimi += 2; alasaPiKulupuNimi != kulupuNimi.end(); alasaPiKulupuNimi++)  {
					switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
						case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
						case kipisi::NimiPiKulupuNimi::POKI_NANPA:
						case kipisi::NimiPiKulupuNimi::POKI_SITELEN:
							if (liLonNimiWawaPiNanpaNi == 0)
								pokiPiIjoTawaNimiWawa.push_back(paliEKasi(kulupuNimi, alasaPiKulupuNimi, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa));

							continue;

						case kipisi::NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA:
							if (alasaPiKulupuNimi->kamaJoENimiPoki().at(0) == ')') {
								if (liLonNimiWawaPiNanpaNi == 0) {
									goto piniPiAlasaIjo;

								} else
									liLonNimiWawaPiNanpaNi--;

							} else
								liLonNimiWawaPiNanpaNi++;

							continue;

						case kipisi::NimiPiKulupuNimi::LINJA_SITELEN_SIN:
							continue;

						default:
							ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, alasaPiKulupuNimi->kamaJoENanpaSitelen(), "Unexpected token");
					}
				}
			piniPiAlasaIjo:

				if (alasaPiKulupuNimi == kulupuNimi.end())
					ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, alasaPiKulupuNimi->kamaJoENanpaSitelen(), "Unterminated function definition. Expected ending ')' symbol");

				// li pali e nimi wawa tawa.
				if (kulupuNimiPiNimiWawa->kamaJoENimiPoki() == "niLaTawa") {
					return paliEKasiPiTawaKen(kulupuNimiPiNimiWawa, pokiPiIjoTawaNimiWawa, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa);

				} else if (kulupuNimiPiNimiWawa->kamaJoENimiPoki() == "tawa") 
					return paliEKasiTawa(kulupuNimiPiNimiWawa, pokiPiIjoTawaNimiWawa, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa);

				// li pali e nimi wawa pi tawa ala.
				return new KasiPiNimiWawa(kulupuNimiPiNimiWawa->kamaJoENimiPoki(), pokiPiIjoTawaNimiWawa);
			}

			case kipisi::NimiPiKulupuNimi::NIMI_TAWA_TAWA:
				return new KasiPiNimiTawa(&alasaPiKulupuNimi->kamaJoENimiPoki());
		}

		return nullptr;
	}

	const std::vector<KasiPiKasiSuli*>& paliELipuWawa(std::vector<KasiPiKasiSuli*>& pokiTawaLipuWawa, const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa) {
		bool liPaliTanLinjaSitelen = false;
		size_t nanpaLinja = 1;
		std::vector<IjoTawaTawa> nimiWawaTawaTawa;

		// li pali e lipu wawa.
		for (auto alasaPiKulupuNimi = kulupuNimi.begin(); alasaPiKulupuNimi != kulupuNimi.end(); alasaPiKulupuNimi++) {
			switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
				// nimi wawa pi nanpa 1 en pana pi nanpa 1 lon poki nanpa li kulupu nimi suli suli lon linja sitelen li wile lon open pi kasi suli.
				case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
				case kipisi::NimiPiKulupuNimi::PANA_LON_POKI_NANPA:
					if (!liPaliTanLinjaSitelen) {
						pokiTawaLipuWawa.push_back(paliEKasi(kulupuNimi, alasaPiKulupuNimi, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa));
						liPaliTanLinjaSitelen = true;
					}

					continue;

				case kipisi::NimiPiKulupuNimi::NIMI_TAWA_TAWA:
					pokiTawaLipuWawa.push_back(paliEKasi(kulupuNimi, alasaPiKulupuNimi, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa));
					continue;

				case kipisi::NimiPiKulupuNimi::LINJA_SITELEN_SIN:
					liPaliTanLinjaSitelen = false;
					nanpaLinja++;
			}
		}


		// li wan e nimi tawa e nimi wawa tawa.
		for (size_t nanpa = 0; nanpa < pokiTawaLipuWawa.size(); nanpa++)
			if (pokiTawaLipuWawa.at(nanpa)->kamaJoENimiKasi() == NimiKasi::NIMI_TAWA) {
				auto kasiTawaTawa = static_cast<KasiPiNimiTawa*>(pokiTawaLipuWawa.at(nanpa));

				for (IjoTawaTawa& ijo : nimiWawaTawaTawa)
					if (ijo.nimiPiNimiTawaTawa == *kasiTawaTawa->kamaJoENimiPiNimiTawa())
						ijo.nimiWawaTawaTawa->linjaTawaTawa = nanpa;
			}

		for (IjoTawaTawa& ijo : nimiWawaTawaTawa)
			if (ijo.nimiWawaTawaTawa->linjaTawaTawa == -1)
				ike::tokiEIke(nimiPiLipuWawa, "TODO Undefined label '" + ijo.nimiPiNimiTawaTawa + "'");


		return pokiTawaLipuWawa;
	}



	// TODO ni li wile: ni li kama pona mute. 
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
