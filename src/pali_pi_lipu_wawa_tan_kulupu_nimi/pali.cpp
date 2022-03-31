#include "pali.hpp"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include "../ike.hpp"

namespace pali {
	/**
	 * li kepeken tawa poki e nimi wawa tawa e nimi wawa ona.
	 */
	struct IjoTawaTawa {
		public:
			IjoTawaTawa(std::string nimiPiNimiTawaTawa, const std::shared_ptr<KasiTawa>& nimiWawaTawaTawa)
				: nimiPiNimiTawaTawa(nimiPiNimiTawaTawa), nimiWawaTawaTawa(nimiWawaTawaTawa.get()) {}

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
	std::shared_ptr<KasiPiTawaKen> paliEKasiPiTawaKen(const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa, std::vector<IjoTawaTawa>& nimiWawaTawaTawa, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
		if (pokiPiIjoTawaNimiWawa.size() < 3)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, kulupuNimiPiNimiWawa->kamaJoENanpaSitelen(), "Insufficient arguments for function 'niLaTawa'\n\tExpected: (label, yesMessage, noMessage [, messages...])");

		if (pokiPiIjoTawaNimiWawa.at(0)->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, (kulupuNimiPiNimiWawa+2)->kamaJoENanpaSitelen(), "Invalid label name. Expected token matching [a-zA-Z0-9_]");

		std::string nimiPiKasiTawaTawa = static_cast<KasiPiKamaJoTanPoki*>(pokiPiIjoTawaNimiWawa.at(0).get())->kamaJoENimiPoki();
		std::shared_ptr<KasiPiKasiSuli> kasiLon = pokiPiIjoTawaNimiWawa.at(1);
		std::shared_ptr<KasiPiKasiSuli> kasiPiLonAla = pokiPiIjoTawaNimiWawa.at(2);
		pokiPiIjoTawaNimiWawa.erase(pokiPiIjoTawaNimiWawa.begin(), pokiPiIjoTawaNimiWawa.begin() + 3);

		std::shared_ptr<KasiPiTawaKen> kasiPiPaliKen = std::make_shared<KasiPiTawaKen>(kasiLon, kasiPiLonAla, pokiPiIjoTawaNimiWawa);
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
	std::shared_ptr<KasiTawa> paliEKasiTawa(const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa, std::vector<IjoTawaTawa>& nimiWawaTawaTawa, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
		if (pokiPiIjoTawaNimiWawa.size() != 1)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, kulupuNimiPiNimiWawa->kamaJoENanpaSitelen(), "Incorrect number of arguments for function 'tawa'\n\tExpected: tawa(label)");
				
		if (pokiPiIjoTawaNimiWawa.at(0)->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI)
			ike::tokiEIke(nimiPiLipuWawa, nanpaLinja, (kulupuNimiPiNimiWawa+2)->kamaJoENanpaSitelen(), "Invalid label name. Expected token matching [a-zA-Z0-9_]");

		auto kasiTawa = std::make_shared<KasiTawa>();
		nimiWawaTawaTawa.emplace_back(static_cast<KasiPiPanaLonPoki*>(pokiPiIjoTawaNimiWawa.at(0).get())->kamaJoENimiPoki(), kasiTawa);
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
	std::shared_ptr<KasiPiKasiSuli> paliEKasi(const std::vector<kipisi::KulupuNimi>& kulupuNimi, std::vector<kipisi::KulupuNimi>::const_iterator alasaPiKulupuNimi, std::vector<IjoTawaTawa>& nimiWawaTawaTawa, size_t nanpaLinja, const std::string& nimiPiLipuWawa) {
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

				return std::make_shared<KasiPiPanaLonPoki>(pokiNanpa->kamaJoENimiPoki(), paliEKasi(kulupuNimi, alasaPiKulupuNimi + 1, nimiWawaTawaTawa, nanpaLinja, nimiPiLipuWawa));
			}

			case kipisi::NimiPiKulupuNimi::POKI_NANPA:
				return std::make_shared<KasiPiKamaJoTanPoki>(alasaPiKulupuNimi->kamaJoENimiPoki());

			case kipisi::NimiPiKulupuNimi::POKI_SITELEN: 
				return std::make_shared<KasiPiKamaJoTanPokiPiAnteAla>(alasaPiKulupuNimi->kamaJoENimiPoki());

			case kipisi::NimiPiKulupuNimi::NIMI_WAWA: {
				auto kulupuNimiPiNimiWawa = alasaPiKulupuNimi;
				std::vector<std::shared_ptr<KasiPiKasiSuli>> pokiPiIjoTawaNimiWawa;
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
				return std::make_shared<KasiPiNimiWawa>(kulupuNimiPiNimiWawa->kamaJoENimiPoki(), pokiPiIjoTawaNimiWawa);
			}

			case kipisi::NimiPiKulupuNimi::NIMI_TAWA_TAWA:
				return std::make_shared<KasiPiNimiTawa>(alasaPiKulupuNimi->kamaJoENimiPoki());
		}

		return nullptr;
	}

	const std::vector<std::shared_ptr<KasiPiKasiSuli>>& paliELipuWawa(std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa) {
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
				auto kasiTawaTawa = static_cast<KasiPiNimiTawa*>(pokiTawaLipuWawa.at(nanpa).get());

				for (IjoTawaTawa& ijo : nimiWawaTawaTawa)
					if (ijo.nimiPiNimiTawaTawa == kasiTawaTawa->kamaJoENimiPiNimiTawa())
						ijo.nimiWawaTawaTawa->linjaTawaTawa = nanpa;
			}

		for (IjoTawaTawa& ijo : nimiWawaTawaTawa)
			if (ijo.nimiWawaTawaTawa->linjaTawaTawa == -1)
				ike::tokiEIke(nimiPiLipuWawa, "TODO Undefined label '" + ijo.nimiPiNimiTawaTawa + "'");

		return pokiTawaLipuWawa;
	}



	/**
	 * @brief li toki e sitelen pi lukin ala lon open pi toki kasi.
	 * 
	 * @param lonInsaPiNanpaNi nanpa ni li nanpa sitelen tawa toki. kasi li lon insa pi kasi pi nanpa ni.
	 */
	void tokiEOpenPiTokiKasi(unsigned int lonInsaPiNanpaNi) {
		for (int nanpa = 0; nanpa < lonInsaPiNanpaNi; nanpa++)
			std::cout << "  ";
	}

	/**
	 * @breif li pana e kasi pi kasi suli pi lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasi kasi pi kasi suli tawa pana.
	 * @param lonInsaPiNanpaNi kasi li lon insa pi kasi pi nanpa ni.
	 * @param nanpaPiKasiLonSewi kasi li kasi pi nanpa ni lon poki pi lipu wawa anu lon kasi ni.
	 */
	void tokiEKasiPiKasiSuli(const KasiPiKasiSuli* kasi, unsigned int lonInsaPiNanpaNi, size_t nanpaPiKasiLonSewi) {
		tokiEOpenPiTokiKasi(lonInsaPiNanpaNi);

		switch (kasi->kamaJoENimiKasi()) {
			case NimiKasi::PANA_LON_POKI: {
				auto kasiPiPanaLonPoki = static_cast<const KasiPiPanaLonPoki*>(kasi);
				std::cout << "PANA_LON_POKI='" << kasiPiPanaLonPoki->kamaJoENimiPoki() << "':\n";
				tokiEKasiPiKasiSuli(kasiPiPanaLonPoki->kamaJoEIjoTawaPana().get(), lonInsaPiNanpaNi + 2, nanpaPiKasiLonSewi);

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI: {
				auto kasiPiKamaJoTanPoki = static_cast<const KasiPiKamaJoTanPoki*>(kasi);
				std::cout << "KAMA_JO_TAN_POKI='" << kasiPiKamaJoTanPoki->kamaJoENimiPoki() << "'\n";

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA: {
				auto kasiPiKamaJoTanPokiPiAnteAla = static_cast<const KasiPiKamaJoTanPokiPiAnteAla*>(kasi);
				std::cout << "KAMA_JO_TAN_POKI_PI_ANTE_ALA='" << kasiPiKamaJoTanPokiPiAnteAla->kamaJoEIjoPoki() << "'\n";

				break;
			}

			case NimiKasi::NIMI_WAWA: {
				auto kasiPiNimiWawa = static_cast<const KasiPiNimiWawa*>(kasi);
				std::cout << "NIMI_WAWA='" << kasiPiNimiWawa->kamaJoENimiPiNimiWawa() << '\'';

				if (kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa().size() > 0) {
					std::cout << ":\n";

					for (const std::shared_ptr<KasiPiKasiSuli>& kasiPiIjoTawaNimiWawa : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
						tokiEKasiPiKasiSuli(kasiPiIjoTawaNimiWawa.get(), lonInsaPiNanpaNi + 2, nanpaPiKasiLonSewi);
				
				} else
					std::cout << '\n';

				break;
			}

			case NimiKasi::NIMI_TAWA:
				std::cout << "NIMI_TAWA=" << nanpaPiKasiLonSewi << '\n';
				break;

			case NimiKasi::TAWA: {
				auto kasiTawa = static_cast<const KasiTawa*>(kasi);
				std::cout << "TAWA=" << kasiTawa->linjaTawaTawa << '\n';

				break;
			}

			case NimiKasi::TAWA_KEN: {
				auto kasiPiTawaKen = static_cast<const KasiPiTawaKen*>(kasi);
				std::cout << "TAWA_KEN=" << kasiPiTawaKen->linjaTawaTawa << ":\n";

				tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 2);
				std::cout << "NIMI_LON:\n";
				tokiEKasiPiKasiSuli(kasiPiTawaKen->kamaJoEKasiLon().get(), lonInsaPiNanpaNi + 4, nanpaPiKasiLonSewi);
				tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 2);
				std::cout << "NIMI_PI_LON_ALA:\n";
				tokiEKasiPiKasiSuli(kasiPiTawaKen->kamaJoEKasiPiLonAla().get(), lonInsaPiNanpaNi + 4, nanpaPiKasiLonSewi);
				
				if (kasiPiTawaKen->kamaJoEKulupuPiIjoToki().size() > 0) {
					tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 2);
					std::cout << "IJO_TAWA_TOKI:\n";
					for (const std::shared_ptr<KasiPiKasiSuli>& ijo : kasiPiTawaKen->kamaJoEKulupuPiIjoToki())
						tokiEKasiPiKasiSuli(ijo.get(), lonInsaPiNanpaNi + 4, nanpaPiKasiLonSewi);
				}

				break;
			}

			default:
				std::cout << "ALA\n";
		}
	}

	// TODO o pali e ni: sitelen nasa li toki kepeken sitelen pi nasa ala.
	void tokiEKasiSuli(const std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa) {
		for (size_t nanpa; nanpa < pokiTawaLipuWawa.size(); nanpa++)
			tokiEKasiPiKasiSuli(pokiTawaLipuWawa.at(nanpa).get(), 0, nanpa);
	}
}
