#include "pali.hpp"
#include <iostream>
#include "../kipisi_pi_lipu_wawa/kipisi.hpp"

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
	 * @return kulupu nimi pi lon ante.
	 */
	std::optional<const kipisi::KulupuNimi*> kamaJoLonAnte(const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::vector<kipisi::KulupuNimi>::const_iterator& alasaPiKulupuNimi, int lonAnte) {
		const auto kulupuNimiLonAnte = alasaPiKulupuNimi + lonAnte;

		if (kulupuNimiLonAnte == kulupuNimi.cend())
			return std::nullopt;

		return &(*kulupuNimiLonAnte);
	}

	/**
	 * li kepeken tawa poki e nimi wawa tawa e nimi wawa ona.
	 */
	struct IjoTawaTawa {
		public:
			IjoTawaTawa(const std::string& nimiPiNimiTawaTawa, KasiTawa *const nimiWawaTawaTawa)
				: nimiPiNimiTawaTawa(nimiPiNimiTawaTawa), nimiWawaTawaTawa(nimiWawaTawaTawa) {}

			const std::string nimiPiNimiTawaTawa;
			KasiTawa *const nimiWawaTawaTawa;
	};

	/**
	 * @brief li kepeken tawa poki e ijo suli tawa pali e lipu wawa.
	 */
	struct SonaTawaPali {
		public:
			// kulupu nimi pi lipu wawa tan kipisi.
			const std::vector<kipisi::KulupuNimi>& kulupuNimi;
			const std::string& nimiPiLipuWawa;
			const std::string& nimiPiILO_LI_SINA;

			// li tawa wan e nimi wawa tawa e nimi tawa.
			std::vector<IjoTawaTawa>& nimiWawaTawaTawa;
			bool liLipuPiPonaAla;
	};

	/**
	 * @brief li pali e kasi sin pi tawa ken.
	 * 
	 * @param sonaTawaPali sona tawa pali e lipu wawa.
	 * @param kulupuNimiPiNimiWawa lon pi nimi wawa "niLaTawa" lon poki pi kulupu nimi.
	 * @param pokiPiIjoTawaNimiWawa poki pi ijo tawa nimi wawa.
	 * 
	 * @return kasi sin pi tawa ken.
	 */
	std::shared_ptr<KasiPiTawaKen> paliEKasiPiTawaKen(SonaTawaPali& sonaTawaPali, const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa) {
		if (pokiPiIjoTawaNimiWawa.size() < 3) {
			kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, kulupuNimiPiNimiWawa->kamaJoELon(), "Insufficient arguments for function 'niLaTawa'\n\tExpected: (label, yesMessage, noMessage [, messages...])");
			
			sonaTawaPali.liLipuPiPonaAla = true;
			return nullptr;
		}

		if (pokiPiIjoTawaNimiWawa.at(0)->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI) {
			kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, (kulupuNimiPiNimiWawa+2)->kamaJoELon(), "Invalid label name\n\tExpected token matching [a-zA-Z0-9_]");
			sonaTawaPali.liLipuPiPonaAla = true;
		}

		const std::string nimiPiKasiTawaTawa = static_cast<KasiPiKamaJoTanPoki*>(pokiPiIjoTawaNimiWawa.at(0).get())->kamaJoENimiPoki();
		const std::shared_ptr<KasiPiKasiSuli> kasiLon = pokiPiIjoTawaNimiWawa.at(1);
		const std::shared_ptr<KasiPiKasiSuli> kasiPiLonAla = pokiPiIjoTawaNimiWawa.at(2);
		pokiPiIjoTawaNimiWawa.erase(pokiPiIjoTawaNimiWawa.begin(), pokiPiIjoTawaNimiWawa.begin() + 3);
		const auto [linja, sitelen] = kulupuNimiPiNimiWawa->kamaJoELon();

		std::shared_ptr<KasiPiTawaKen> kasiPiPaliKen = std::make_shared<KasiPiTawaKen>(
			kasiLon, 
			kasiPiLonAla, 
			pokiPiIjoTawaNimiWawa, 
			linja, sitelen);
		sonaTawaPali.nimiWawaTawaTawa.emplace_back(nimiPiKasiTawaTawa, kasiPiPaliKen.get());
		return kasiPiPaliKen;
	}

	/**
	 * @brief li pali e kasi tawa sin.
	 * 
	 * @param sonaTawaPali sona tawa pali e lipu wawa.
	 * @param kulupuNimiPiNimiWawa lon pi nimi wawa "niLaTawa" lon poki pi kulupu nimi.
	 * @param pokiPiIjoTawaNimiWawa poki pi ijo tawa nimi wawa.
	 * 
	 * @return kasi tawa sin.
	 */
	std::shared_ptr<KasiTawa> paliEKasiTawa(SonaTawaPali& sonaTawaPali, const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa) {
		if (pokiPiIjoTawaNimiWawa.size() != 1) {
			kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, kulupuNimiPiNimiWawa->kamaJoELon(), "Incorrect number of arguments for function 'tawa'\n\tExpected: tawa(label)");
			
			sonaTawaPali.liLipuPiPonaAla = true;
			return nullptr;
		}
				
		if (pokiPiIjoTawaNimiWawa.at(0)->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI) {
			kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, (kulupuNimiPiNimiWawa+2)->kamaJoELon(), "Invalid label name\n\tExpected token matching [a-zA-Z0-9_]");
			sonaTawaPali.liLipuPiPonaAla = true;
		}


		const auto [linja, sitelen] = kulupuNimiPiNimiWawa->kamaJoELon(); 
		auto kasiTawa = std::make_shared<KasiTawa>(linja, sitelen);

		const std::string nimiPiNimiTawa = static_cast<KasiPiPanaLonPoki*>(pokiPiIjoTawaNimiWawa.at(0).get())->kamaJoENimiPoki();
		sonaTawaPali.nimiWawaTawaTawa.emplace_back(nimiPiNimiTawa, kasiTawa.get());

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
	 * @param sonaTawaPali sona tawa pali e lipu wawa.
	 * @param alasaPiKulupuNimi ilo alasa pi kulupu nimi. ni li lon pi kulupu nimi tawa pali.
	 * 
	 * @return kasi sin pi kasi suli.
	 * @retval nullptr ni li ken ala pali e kasi la.
	 */
	std::shared_ptr<KasiPiKasiSuli> paliEKasi(SonaTawaPali& sonaTawaPali, std::vector<kipisi::KulupuNimi>::const_iterator alasaPiKulupuNimi) {
		switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
			case kipisi::NimiPiKulupuNimi::PANA_LON_POKI_NANPA: {
				const std::optional<const kipisi::KulupuNimi *const> pokiNanpa = kamaJoLonAnte(sonaTawaPali.kulupuNimi, alasaPiKulupuNimi, -1);
				if (!pokiNanpa.has_value()) {
					kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, alasaPiKulupuNimi->kamaJoELon(), "Expected variable name before '=' token");
					sonaTawaPali.liLipuPiPonaAla = true;

					return nullptr;
				}
				if ((*pokiNanpa)->nimiPiKulupuNimi != kipisi::NimiPiKulupuNimi::POKI_NANPA) {
					kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, (*pokiNanpa)->kamaJoELon(), "Expected variable name before '=' token");
					sonaTawaPali.liLipuPiPonaAla = true;
				}

				const std::optional<const kipisi::KulupuNimi *const> ijoTawaPoki = kamaJoLonAnte(sonaTawaPali.kulupuNimi, alasaPiKulupuNimi, 1);
				if (!ijoTawaPoki.has_value()) {
					kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, alasaPiKulupuNimi->kamaJoELon(), "Expected secondary expression after '=' token");
					sonaTawaPali.liLipuPiPonaAla = true;

					return nullptr;
				}
				switch ((*ijoTawaPoki)->nimiPiKulupuNimi) {
					case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
					case kipisi::NimiPiKulupuNimi::POKI_NANPA:
					case kipisi::NimiPiKulupuNimi::POKI_SITELEN:
						break;

					default:
						kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, (*ijoTawaPoki)->kamaJoELon(), "Invalid secondary expression after '=' token\n\tMust be or return some kind of value!");
						sonaTawaPali.liLipuPiPonaAla = true;
				}


				const auto [linja, sitelen] = alasaPiKulupuNimi->kamaJoELon();

				return std::make_shared<KasiPiPanaLonPoki>(
					(*pokiNanpa)->kamaJoENimiPoki(), 
					paliEKasi(sonaTawaPali, alasaPiKulupuNimi + 1), 
					linja, sitelen);
			}

			case kipisi::NimiPiKulupuNimi::POKI_NANPA: {
				const auto [linja, sitelen] = alasaPiKulupuNimi->kamaJoELon();
			
				return std::make_shared<KasiPiKamaJoTanPoki>(
					alasaPiKulupuNimi->kamaJoENimiPoki(), 
					linja, sitelen);
			}

			case kipisi::NimiPiKulupuNimi::POKI_SITELEN: {
				const auto [linja, sitelen] = alasaPiKulupuNimi->kamaJoELon();

				return std::make_shared<KasiPiKamaJoTanPokiPiAnteAla>(
					alasaPiKulupuNimi->kamaJoENimiPoki(), 
					linja, sitelen);
			}

			case kipisi::NimiPiKulupuNimi::NIMI_WAWA: {
				const auto kulupuNimiPiNimiWawa = alasaPiKulupuNimi;
				std::vector<std::shared_ptr<KasiPiKasiSuli>> pokiPiIjoTawaNimiWawa;
				unsigned int liLonNimiWawaPiNanpaNi = 0;

				// li kama jo e ijo tawa nimi wawa.
				for (alasaPiKulupuNimi += 2; alasaPiKulupuNimi != sonaTawaPali.kulupuNimi.cend(); alasaPiKulupuNimi++)  {
					switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
						case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
						case kipisi::NimiPiKulupuNimi::POKI_NANPA:
						case kipisi::NimiPiKulupuNimi::POKI_SITELEN:
							if (liLonNimiWawaPiNanpaNi == 0)
								pokiPiIjoTawaNimiWawa.push_back(paliEKasi(
									sonaTawaPali, 
									alasaPiKulupuNimi));

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
							kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, kulupuNimiPiNimiWawa->kamaJoELon(), "Unterminated function call\n\tExpected ending ')' symbol");
							sonaTawaPali.liLipuPiPonaAla = true;

							return nullptr;

						default:
							kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, alasaPiKulupuNimi->kamaJoELon(), "Unexpected token" + kipisi::kamaJoENimiPiNimiKulupu(alasaPiKulupuNimi->nimiPiKulupuNimi));
							sonaTawaPali.liLipuPiPonaAla = true;
					}
				}
			piniPiAlasaIjo:

				// li pali e nimi wawa tawa.
				if (kulupuNimiPiNimiWawa->kamaJoENimiPoki() == "niLaTawa") {
					return paliEKasiPiTawaKen(
						sonaTawaPali,
						kulupuNimiPiNimiWawa, 
						pokiPiIjoTawaNimiWawa);

				} else if (kulupuNimiPiNimiWawa->kamaJoENimiPoki() == "tawa") 
					return paliEKasiTawa(
						sonaTawaPali,
						kulupuNimiPiNimiWawa, 
						pokiPiIjoTawaNimiWawa);


				nimi_wawa nimiWawa;

				try {					
					nimiWawa = pokiPiNimiWawaAli.at(kulupuNimiPiNimiWawa->kamaJoENimiPoki());

				} catch (const std::out_of_range& liSuliAla) {
					kepeken::tokiEIke(sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, kulupuNimiPiNimiWawa->kamaJoELon(), "Unknown function '" + kulupuNimiPiNimiWawa->kamaJoENimiPoki() + "'");
					sonaTawaPali.liLipuPiPonaAla = true;

					return nullptr;
				}
				

				// li pali e nimi wawa pi tawa ala.
				const auto [linja, sitelen] = kulupuNimiPiNimiWawa->kamaJoELon();

				return std::make_shared<KasiPiNimiWawa>(
					nimiWawa, 
					pokiPiIjoTawaNimiWawa, 
					linja, sitelen);
			}

			case kipisi::NimiPiKulupuNimi::NIMI_TAWA_TAWA: {
				const auto [linja, sitelen] = alasaPiKulupuNimi->kamaJoELon();

				return std::make_shared<KasiPiNimiTawa>(
					alasaPiKulupuNimi->kamaJoENimiPoki(), 
					linja, sitelen);
			}

			default:
				throw std::out_of_range("pali la li kama jo e kulupu nimi pi sona ala pi nimi '" + kipisi::kamaJoENimiPiNimiKulupu(alasaPiKulupuNimi->nimiPiKulupuNimi));
		}

		return nullptr;
	}

	const std::vector<std::shared_ptr<KasiPiKasiSuli>>& paliELipuWawa(std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
		bool liPaliTanLinjaSitelen = false;
		std::vector<IjoTawaTawa> nimiWawaTawaTawa;

		SonaTawaPali sonaTawaKipisi = {kulupuNimi, nimiPiLipuWawa, nimiPiILO_LI_SINA, nimiWawaTawaTawa, false};

		// li pali e lipu wawa.
		for (auto alasaPiKulupuNimi = kulupuNimi.cbegin(); alasaPiKulupuNimi != kulupuNimi.cend(); alasaPiKulupuNimi++) {
			switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
				// nimi wawa pi nanpa 1 en pana pi nanpa 1 lon poki nanpa li kulupu nimi suli suli lon linja sitelen li wile lon open pi kasi suli.
				case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
				case kipisi::NimiPiKulupuNimi::PANA_LON_POKI_NANPA:
					if (!liPaliTanLinjaSitelen) {
						pokiTawaLipuWawa.push_back(paliEKasi(
							sonaTawaKipisi,
							alasaPiKulupuNimi));
						liPaliTanLinjaSitelen = true;
					}

					continue;

				case kipisi::NimiPiKulupuNimi::NIMI_TAWA_TAWA:
					pokiTawaLipuWawa.push_back(paliEKasi(
						sonaTawaKipisi,
						alasaPiKulupuNimi));

					continue;

				case kipisi::NimiPiKulupuNimi::LINJA_SITELEN_SIN:
					liPaliTanLinjaSitelen = false;
			}
		}

		if (!sonaTawaKipisi.liLipuPiPonaAla) {
			// li wan e nimi tawa e nimi wawa tawa.
			for (size_t nanpa = 0; nanpa < pokiTawaLipuWawa.size(); nanpa++)
				if (pokiTawaLipuWawa.at(nanpa)->kamaJoENimiKasi() == NimiKasi::NIMI_TAWA) {
					const auto kasiTawaTawa = static_cast<const KasiPiNimiTawa*>(pokiTawaLipuWawa.at(nanpa).get());

					for (IjoTawaTawa& ijo : nimiWawaTawaTawa)
						if (ijo.nimiPiNimiTawaTawa == kasiTawaTawa->kamaJoENimiPiNimiTawa())
							ijo.nimiWawaTawaTawa->linjaTawaTawa = nanpa;
				}

			for (const IjoTawaTawa& ijo : nimiWawaTawaTawa)
				if (ijo.nimiWawaTawaTawa->linjaTawaTawa == -1) {
					kepeken::tokiEIke(nimiPiILO_LI_SINA, nimiPiLipuWawa, ijo.nimiWawaTawaTawa->kamaJoELonKasi(), "Jump to undefined label '" + ijo.nimiPiNimiTawaTawa + "'");
					sonaTawaKipisi.liLipuPiPonaAla = true;
				}
		}


		if (sonaTawaKipisi.liLipuPiPonaAla)
			exit(1);

		return pokiTawaLipuWawa;
	}



	/**
	 * @brief li toki e sitelen pi lukin ala lon open pi toki kasi.
	 * 
	 * @param lonInsaPiNanpaNi nanpa ni li nanpa sitelen tawa toki. kasi li lon insa pi kasi pi nanpa ni.
	 */
	void tokiEOpenPiTokiKasi(const unsigned int lonInsaPiNanpaNi) {
		for (int nanpa = 0; nanpa < lonInsaPiNanpaNi; nanpa++)
			std::cout << "    ";
	}

	/**
	 * @breif li pana e kasi pi kasi suli pi lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasi kasi pi kasi suli tawa pana.
	 * @param lonInsaPiNanpaNi kasi li lon insa pi kasi pi nanpa ni.
	 * @param nanpaPiKasiLonSewi kasi li kasi pi nanpa ni lon poki pi lipu wawa anu lon kasi ni.
	 */
	void tokiEKasiPiKasiSuli(const KasiPiKasiSuli* kasi, const unsigned int lonInsaPiNanpaNi, const size_t nanpaPiKasiLonSewi) {
		tokiEOpenPiTokiKasi(lonInsaPiNanpaNi);

		switch (kasi->kamaJoENimiKasi()) {
			case NimiKasi::PANA_LON_POKI: {
				const auto kasiPiPanaLonPoki = static_cast<const KasiPiPanaLonPoki*>(kasi);
				std::cout << kamaJoENimiPiNimiKasi(kasiPiPanaLonPoki->kamaJoENimiKasi()) << "=\"" << kasiPiPanaLonPoki->kamaJoENimiPoki() << "\":\n";
				tokiEKasiPiKasiSuli(kasiPiPanaLonPoki->kamaJoEIjoTawaPana().get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI: {
				const auto kasiPiKamaJoTanPoki = static_cast<const KasiPiKamaJoTanPoki*>(kasi);
				std::cout << kamaJoENimiPiNimiKasi(kasiPiKamaJoTanPoki->kamaJoENimiKasi()) << "=\"" << kasiPiKamaJoTanPoki->kamaJoENimiPoki() << "\"\n";

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA: {
				const auto kasiPiKamaJoTanPokiPiAnteAla = static_cast<const KasiPiKamaJoTanPokiPiAnteAla*>(kasi);
				std::cout << kamaJoENimiPiNimiKasi(kasiPiKamaJoTanPokiPiAnteAla->kamaJoENimiKasi()) << "=\"";

				const std::unordered_map<char, char>& nimiTanSitelenNasa = kipisi::kamaJoEPokiPiNimiTanSitelenNasa();
				
				for (const char sitelen : kasiPiKamaJoTanPokiPiAnteAla->kamaJoEIjoPoki())
					try {
						const char sitelenPiNasaAla = nimiTanSitelenNasa.at(sitelen);
						std::cout << '\\' << sitelenPiNasaAla;

					} catch (const std::out_of_range& liSuliAla) {
						std::cout << sitelen;
					}

				std::cout << "\"\n";
				break;
			}

			case NimiKasi::NIMI_WAWA: {
				const auto kasiPiNimiWawa = static_cast<const KasiPiNimiWawa*>(kasi);
				
				try {
					std::cout << kamaJoENimiPiNimiKasi(kasiPiNimiWawa->kamaJoENimiKasi()) << "=\"" << kamaJoEPokiPiNimiPiNimiWawa().at(kasiPiNimiWawa->kamaJoENimiWawa()) << '"';
				
				} catch (const std::out_of_range& liSuliAla) {
					throw std::out_of_range("Found either nullptr or pointer to an unknown function");
				}

				if (kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa().size() > 0) {
					std::cout << ":\n";

					for (const std::shared_ptr<KasiPiKasiSuli>& kasiPiIjoTawaNimiWawa : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
						tokiEKasiPiKasiSuli(kasiPiIjoTawaNimiWawa.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);
				
				} else
					std::cout << '\n';


				break;
			}

			case NimiKasi::NIMI_TAWA:
				std::cout << kamaJoENimiPiNimiKasi(kasi->kamaJoENimiKasi()) << "=" << nanpaPiKasiLonSewi << '\n';
				break;

			case NimiKasi::TAWA: {
				const auto kasiTawa = static_cast<const KasiTawa*>(kasi);
				std::cout << kamaJoENimiPiNimiKasi(kasiTawa->kamaJoENimiKasi()) << "=" << kasiTawa->linjaTawaTawa << '\n';

				break;
			}

			case NimiKasi::TAWA_KEN: {
				const auto kasiPiTawaKen = static_cast<const KasiPiTawaKen*>(kasi);
				std::cout << kamaJoENimiPiNimiKasi(kasiPiTawaKen->kamaJoENimiKasi()) << "=" << kasiPiTawaKen->linjaTawaTawa << ":\n";

				tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 1);
				std::cout << "NIMI_LON:\n";
				tokiEKasiPiKasiSuli(kasiPiTawaKen->kamaJoEKasiLon().get(), lonInsaPiNanpaNi + 2, nanpaPiKasiLonSewi);
				tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 1);
				std::cout << "NIMI_PI_LON_ALA:\n";
				tokiEKasiPiKasiSuli(kasiPiTawaKen->kamaJoEKasiPiLonAla().get(), lonInsaPiNanpaNi + 2, nanpaPiKasiLonSewi);
				
				if (kasiPiTawaKen->kamaJoEKulupuPiIjoToki().size() > 0) {
					tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 1);
					std::cout << "IJO_TAWA_TOKI:\n";
					for (const std::shared_ptr<KasiPiKasiSuli>& ijo : kasiPiTawaKen->kamaJoEKulupuPiIjoToki())
						tokiEKasiPiKasiSuli(ijo.get(), lonInsaPiNanpaNi + 2, nanpaPiKasiLonSewi);
				}

				break;
			}

			default:
				std::cout << kamaJoENimiPiNimiKasi(kasi->kamaJoENimiKasi()) << '\n';
		}
	}

	void tokiEKasiSuli(const std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const std::string& nimiPiLipuWawa) {
		std::cout << "/-------------------\n| " << nimiPiLipuWawa << "\n\\-------------------\n";

		for (size_t nanpa = 0; nanpa < pokiTawaLipuWawa.size(); nanpa++) {
			const KasiPiKasiSuli *const kasiPiKasiSuli = pokiTawaLipuWawa.at(nanpa).get();

			std::cout << "linja pi nanpa " << kasiPiKasiSuli->kamaJoELonKasi().nanpaLinja << ":\n";
			tokiEKasiPiKasiSuli(pokiTawaLipuWawa.at(nanpa).get(), 1, nanpa);
		}

		std::cout << "\\-------------------\n";
	}
}
