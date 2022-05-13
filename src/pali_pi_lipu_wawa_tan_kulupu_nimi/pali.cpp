#include "pali.hpp"
#include <iostream>
#include <functional>
#include <cassert>
#include "../kipisi_pi_lipu_wawa/kipisi.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace pali {
	/**
	 * @breif li kama jo e kulupu nimi pi lon ante.
	 *
	 * ni li kama jo e kulupu nimi pi lon ante.
	 * ona li lon ala la ni li toki e ike li pini e ali.
	 *
	 * @param kulupuNimi 		kulupu nimi pi lipu wawa.
	 * @param alasaPiKulupuNimi ilo alasa pi kulupu nimi.
	 * @param lonAnte 			ni li nanpa kulupu nimi lon sinpin pi lon pi ilo alasa pi tenpo ni lon monsi kulupi nimi wile.
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
			std::list<IjoTawaTawa>& nimiWawaTawaTawa;
			bool liLipuPiPonaAla;
	};
	


	/**
	 * @brief li pali e kasi tawa sin.
	 * 
	 * @param sonaTawaPali 			sona tawa pali e lipu wawa.
	 * @param kulupuNimiPiNimiWawa 	lon pi nimi wawa "niLaTawa" lon poki pi kulupu nimi.
	 * @param pokiPiIjoTawaNimiWawa poki pi ijo tawa nimi wawa.
	 * 
	 * @return kasi tawa sin.
	 */
	std::shared_ptr<KasiTawa> paliEKasiTawa(SonaTawaPali& sonaTawaPali, const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::list<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa) {
		if (pokiPiIjoTawaNimiWawa.size() != 1) {
			kepeken::tokiEIke(
				sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
				&kulupuNimiPiNimiWawa->kamaJoELon(), 
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.tawa.nanpa_ijo_ike"));
			
			sonaTawaPali.liLipuPiPonaAla = true;
			return nullptr;
		}


		// TODO o pana e ijo ni lon ma wan tawa kasi tawa ali.
		if (pokiPiIjoTawaNimiWawa.front()->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI) {
			kepeken::tokiEIke(
				sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
				&(kulupuNimiPiNimiWawa+2)->kamaJoELon(), 
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.tawa.sitelen_ike"));
			sonaTawaPali.liLipuPiPonaAla = true;
		}

		const std::string nimiPiNimiTawa = static_cast<KasiPiPanaLonPoki*>(pokiPiIjoTawaNimiWawa.front().get())->kamaJoENimiPoki();
		const auto [linja, sitelen] = kulupuNimiPiNimiWawa->kamaJoELon(); 


		auto kasiTawa = std::make_shared<KasiTawa>(linja, sitelen);
		sonaTawaPali.nimiWawaTawaTawa.emplace_back(nimiPiNimiTawa, kasiTawa.get());//TODO
		return kasiTawa;
	}

	/**
	 * @brief li pali e kasi sin pi tawa ken.
	 * 
	 * @param sonaTawaPali		    sona tawa pali e lipu wawa.
	 * @param kulupuNimiPiNimiWawa  lon pi nimi wawa "niLaTawa" lon poki pi kulupu nimi.
	 * @param pokiPiIjoTawaNimiWawa poki pi ijo tawa nimi wawa.
	 * 
	 * @return kasi sin pi tawa ken.
	 */
	std::shared_ptr<KasiPiTawaKen> paliEKasiPiTawaKen(SonaTawaPali& sonaTawaPali, const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::list<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa) {
		if (pokiPiIjoTawaNimiWawa.size() < 3) {
			kepeken::tokiEIke(
				sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
				&kulupuNimiPiNimiWawa->kamaJoELon(), 
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.niLaTawa.nanpa_ijo_lili"));
			
			sonaTawaPali.liLipuPiPonaAla = true;
			return nullptr;
		}

		// TODO o pana e ijo ni lon ma wan tawa kasi tawa ali.
		if (pokiPiIjoTawaNimiWawa.front()->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI) {
			kepeken::tokiEIke(
				sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
				&(kulupuNimiPiNimiWawa+2)->kamaJoELon(), 
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.tawa.sitelen_ike"));
			sonaTawaPali.liLipuPiPonaAla = true;
		}


		const std::string nimiPiKasiTawaTawa = static_cast<KasiPiKamaJoTanPoki*>(pokiPiIjoTawaNimiWawa.front().get())->kamaJoENimiPoki();
		pokiPiIjoTawaNimiWawa.pop_front();
		const auto [linja, sitelen] = kulupuNimiPiNimiWawa->kamaJoELon();


		std::shared_ptr<KasiPiTawaKen> kasiPiPaliKen = std::make_shared<KasiPiTawaKen>(
			pokiPiIjoTawaNimiWawa, 
			linja, sitelen);
		sonaTawaPali.nimiWawaTawaTawa.emplace_back(nimiPiKasiTawaTawa, kasiPiPaliKen.get());//TODO
		return kasiPiPaliKen;
	}

	//TODO
	std::shared_ptr<KasiPiAlaLaTawa> paliEKasiPiAlaLaTawa(SonaTawaPali& sonaTawaPali, const std::vector<kipisi::KulupuNimi>::const_iterator& kulupuNimiPiNimiWawa, std::list<std::shared_ptr<KasiPiKasiSuli>>& pokiPiIjoTawaNimiWawa) {
		if (pokiPiIjoTawaNimiWawa.size() < 2) {
			kepeken::tokiEIke(
				sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
				&kulupuNimiPiNimiWawa->kamaJoELon(), 
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.alaLaTawa.nanpa_ijo_lili"));
			
			sonaTawaPali.liLipuPiPonaAla = true;
			return nullptr;
		}


		// TODO o pana e ijo ni lon ma wan tawa kasi tawa ali.
		if (pokiPiIjoTawaNimiWawa.front()->kamaJoENimiKasi() != NimiKasi::KAMA_JO_TAN_POKI) {
			kepeken::tokiEIke(
				sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
				&(kulupuNimiPiNimiWawa+2)->kamaJoELon(), 
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.tawa.sitelen_ike"));
			sonaTawaPali.liLipuPiPonaAla = true;
		}

		const std::string nimiPiKasiTawaTawa = static_cast<KasiPiKamaJoTanPoki*>(pokiPiIjoTawaNimiWawa.front().get())->kamaJoENimiPoki();
		pokiPiIjoTawaNimiWawa.pop_front();
		const auto [linja, sitelen] = kulupuNimiPiNimiWawa->kamaJoELon();


		std::shared_ptr<KasiPiAlaLaTawa> kasiPiAlaLaTawa = std::make_shared<KasiPiAlaLaTawa>(
			pokiPiIjoTawaNimiWawa, 
			linja, sitelen);
		sonaTawaPali.nimiWawaTawaTawa.emplace_back(nimiPiKasiTawaTawa, kasiPiAlaLaTawa.get());//TODO
		return kasiPiAlaLaTawa;
	}

	/**
	 * @brief li kama jo e nimi pi nimi wawa pi pali e kasi tawa li pana e nimi wawa pali pi nimi pana.
	 */
	std::unordered_map<std::string, std::function<std::shared_ptr<KasiTawa>(SonaTawaPali&, const std::vector<kipisi::KulupuNimi>::const_iterator&, std::list<std::shared_ptr<KasiPiKasiSuli>>&)>> 
		iloPiPaliTawa = {
			{"tawa", 	  &paliEKasiTawa},
			{"niLaTawa",  &paliEKasiPiTawaKen},
			{"alaLaTawa", &paliEKasiPiAlaLaTawa}
	};



	/**
	 * @brief li pali e kasi pi kasi suli tan kulupu nimi lon linja sitelen.
	 *
	 * ni li pali e kasi pi kasi suli tan kulupu nimi.
	 * ni li ken taso kama jo e kulupu pi nimi wawa en pana lon poki nimi.
	 * 	 sin la ona li wile nanpa 1 lon linja sitelen.
	 * ali ni li lon ala la o kepeken ala e ni a!
	 *
	 * @param sonaTawaPali 		sona tawa pali e lipu wawa.
	 * @param alasaPiKulupuNimi ilo alasa pi kulupu nimi. ni li lon pi kulupu nimi tawa pali.
	 * 
	 * @return 		   kasi sin pi kasi suli.
	 * @retval nullptr ni li ken ala pali e kasi la.
	 */
	std::shared_ptr<KasiPiKasiSuli> paliEKasi(SonaTawaPali& sonaTawaPali, std::vector<kipisi::KulupuNimi>::const_iterator alasaPiKulupuNimi) {
		// TODO o pana e ijo suli lon ni lon nimi wawa sin.
		switch (alasaPiKulupuNimi->nimiPiKulupuNimi) {
			case kipisi::NimiPiKulupuNimi::PANA_LON_POKI_NANPA: {
				const std::optional<const kipisi::KulupuNimi *const> pokiNanpa = kamaJoLonAnte(sonaTawaPali.kulupuNimi, alasaPiKulupuNimi, -1);
				if (!pokiNanpa.has_value()) {
					kepeken::tokiEIke(
						sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
						&alasaPiKulupuNimi->kamaJoELon(), 
						ante_toki::kamaJoENimiTawaJan("ike.pali.poki_nanpa.nimi_poki_li_wile"));
					sonaTawaPali.liLipuPiPonaAla = true;

					return nullptr;
				}
				if ((*pokiNanpa)->nimiPiKulupuNimi != kipisi::NimiPiKulupuNimi::POKI_NANPA) {
					kepeken::tokiEIke(
						sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
						&(*pokiNanpa)->kamaJoELon(), 
						ante_toki::kamaJoENimiTawaJan("ike.pali.poki_nanpa.nimi_poki_li_wile"));
					sonaTawaPali.liLipuPiPonaAla = true;
				}

				const std::optional<const kipisi::KulupuNimi *const> ijoTawaPoki = kamaJoLonAnte(sonaTawaPali.kulupuNimi, alasaPiKulupuNimi, 1);
				if (!ijoTawaPoki.has_value()) {
					kepeken::tokiEIke(
						sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
						&alasaPiKulupuNimi->kamaJoELon(), 
						ante_toki::kamaJoENimiTawaJan("ike.pali.poki_nanpa.ijo_tawa_poki_li_wile"));
					sonaTawaPali.liLipuPiPonaAla = true;

					return nullptr;
				}
				switch ((*ijoTawaPoki)->nimiPiKulupuNimi) {
					case kipisi::NimiPiKulupuNimi::NIMI_WAWA:
					case kipisi::NimiPiKulupuNimi::POKI_NANPA:
					case kipisi::NimiPiKulupuNimi::POKI_SITELEN:
						break;

					default:
						kepeken::tokiEIke(
							sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
							&(*ijoTawaPoki)->kamaJoELon(), 
							ante_toki::kamaJoENimiTawaJan("ike.pali.poki_nanpa.ijo_ike_tawa_poki"));
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
				std::list<std::shared_ptr<KasiPiKasiSuli>> pokiPiIjoTawaNimiWawa;
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
							kepeken::tokiEIke(
								sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
								&kulupuNimiPiNimiWawa->kamaJoELon(), 
								ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.li_jo_ala_e_pini"));
							sonaTawaPali.liLipuPiPonaAla = true;

							return nullptr;

						default:
							kepeken::tokiEIke(
								sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
								&alasaPiKulupuNimi->kamaJoELon(), 
								ante_toki::anteENimi(
									ante_toki::kamaJoENimiTawaJan("ike.kulupu_nimi_pi_wile_ala"), 
									"%s", kipisi::kamaJoENimiPiNimiKulupu(alasaPiKulupuNimi->nimiPiKulupuNimi)));
							sonaTawaPali.liLipuPiPonaAla = true;
					}
				}
			piniPiAlasaIjo:


				// li pali e nimi wawa tawa.
				try {
					auto iloPali = iloPiPaliTawa.at(kulupuNimiPiNimiWawa->kamaJoENimiPoki())(
						sonaTawaPali,
						kulupuNimiPiNimiWawa,
						pokiPiIjoTawaNimiWawa);

					return iloPali;

				} catch (const std::out_of_range& liNimiWawaTawaAla) {}


				nimi_wawa nimiWawa;

				try {					
					nimiWawa = pokiPiNimiWawaAli.at(kulupuNimiPiNimiWawa->kamaJoENimiPoki());

				} catch (const std::out_of_range& nimiWawaLiLonAla) {
					kepeken::tokiEIke(
						sonaTawaPali.nimiPiILO_LI_SINA, sonaTawaPali.nimiPiLipuWawa, 
						&kulupuNimiPiNimiWawa->kamaJoELon(), 
						ante_toki::anteENimi(
							ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.nimi_pi_sona_ala"), 
							"%s", kulupuNimiPiNimiWawa->kamaJoENimiPoki()));
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
				assert(false && "pali la li kama jo e kulupu nimi pi sona ala");
		}

		return nullptr;
	}

	std::tuple<std::optional<std::vector<std::shared_ptr<KasiPiKasiSuli>>>, int> paliELipuWawa(const std::vector<kipisi::KulupuNimi>& kulupuNimi, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
		std::vector<std::shared_ptr<KasiPiKasiSuli>> pokiTawaLipuWawa;
		bool liPaliTanLinjaSitelen = false;
		std::list<IjoTawaTawa> nimiWawaTawaTawa;

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

					for (auto alasaIjo = nimiWawaTawaTawa.begin(); alasaIjo != nimiWawaTawaTawa.end();)
						if (alasaIjo->nimiPiNimiTawaTawa == kasiTawaTawa->kamaJoENimiPiNimiTawa()) {
							alasaIjo->nimiWawaTawaTawa->linjaTawaTawa = nanpa;
							alasaIjo = nimiWawaTawaTawa.erase(alasaIjo);
						
						} else 
							alasaIjo++;
				}

			for (const IjoTawaTawa& ijo : nimiWawaTawaTawa) {
				kepeken::tokiEIke(
					nimiPiILO_LI_SINA, nimiPiLipuWawa, 
					&ijo.nimiWawaTawaTawa->kamaJoELonKasi(), 
					ante_toki::anteENimi(
						ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.tawa.nimi_tawa_pi_sona_ala"),
						"%s", ijo.nimiPiNimiTawaTawa));
				sonaTawaKipisi.liLipuPiPonaAla = true;
			}
		}


		std::tuple<std::optional<std::vector<std::shared_ptr<KasiPiKasiSuli>>>, int> ijoTawaPana;

		if (sonaTawaKipisi.liLipuPiPonaAla) {
			ijoTawaPana = {std::nullopt, 1};

		} else 
			ijoTawaPana = {std::move(pokiTawaLipuWawa), 0};

		return ijoTawaPana;
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
	 * @brief li pana e kasi pi kasi suli pi lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param pokiTawaLipuWawa 	 lipu wawa tawa toki.
	 * @param kasi 				 kasi pi kasi suli tawa pana.
	 * @param lonInsaPiNanpaNi	 kasi li lon insa pi kasi pi nanpa ni.
	 * @param nanpaPiKasiLonSewi kasi li kasi pi nanpa ni lon poki pi lipu wawa anu lon kasi ni.
	 */
	void tokiEKasiPiKasiSuli(const std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const KasiPiKasiSuli* kasi, const unsigned int lonInsaPiNanpaNi, const size_t nanpaPiKasiLonSewi) {
		tokiEOpenPiTokiKasi(lonInsaPiNanpaNi);

		switch (kasi->kamaJoENimiKasi()) {
			case NimiKasi::PANA_LON_POKI: {
				const auto kasiPiPanaLonPoki = static_cast<const KasiPiPanaLonPoki*>(kasi);
				std::cout << kasiPiPanaLonPoki->kamaJoENimiPiNimiKasi() << "=\"" << kasiPiPanaLonPoki->kamaJoENimiPoki() << "\":\n";
				tokiEKasiPiKasiSuli(pokiTawaLipuWawa, kasiPiPanaLonPoki->kamaJoEIjoTawaPana().get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI: {
				const auto kasiPiKamaJoTanPoki = static_cast<const KasiPiKamaJoTanPoki*>(kasi);
				std::cout << kasiPiKamaJoTanPoki->kamaJoENimiPiNimiKasi() << "=\"" << kasiPiKamaJoTanPoki->kamaJoENimiPoki() << "\"\n";

				break;
			}

			case NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA: {
				const auto kasiPiKamaJoTanPokiPiAnteAla = static_cast<const KasiPiKamaJoTanPokiPiAnteAla*>(kasi);
				std::cout << kasiPiKamaJoTanPokiPiAnteAla->kamaJoENimiPiNimiKasi() << "=\"";

				const std::unordered_map<char, char>& nimiTanSitelenNasa = kipisi::kamaJoEPokiPiNimiTanSitelenNasa();
				
				for (const char sitelen : kasiPiKamaJoTanPokiPiAnteAla->kamaJoEIjoPoki())
					try {
						const char sitelenPiNasaAla = nimiTanSitelenNasa.at(sitelen);
						std::cout << '\\' << sitelenPiNasaAla;

					} catch (const std::out_of_range& liSitelenNasaAla) {
						std::cout << sitelen;
					}

				std::cout << "\"\n";
				break;
			}

			case NimiKasi::NIMI_WAWA: {
				const auto kasiPiNimiWawa = static_cast<const KasiPiNimiWawa*>(kasi);
				
				try {
					std::cout << kasiPiNimiWawa->kamaJoENimiPiNimiKasi() << "=\"" << kamaJoEPokiPiNimiPiNimiWawa().at(kasiPiNimiWawa->kamaJoENimiWawa()) << '"';
				
				} catch (const std::out_of_range& nimiWawaLiLonAla) {
					assert(false && "pali la li kama jo e lon nullptr anu lon tawa nimi wawa pi sona ala");
				}

				if (kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa().size() > 0) {
					std::cout << ":\n";

					for (const std::shared_ptr<KasiPiKasiSuli>& kasiPiIjoTawaNimiWawa : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
						tokiEKasiPiKasiSuli(pokiTawaLipuWawa, kasiPiIjoTawaNimiWawa.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);
				
				} else
					std::cout << '\n';


				break;
			}

			case NimiKasi::NIMI_TAWA: {
				const auto kasiPiNimiTawa = static_cast<const KasiPiNimiTawa*>(kasi);
				std::cout << kasi->kamaJoENimiPiNimiKasi() << "=\"" << kasiPiNimiTawa->kamaJoENimiPiNimiTawa() << "\"\n";
			
				break;
			}

			case NimiKasi::TAWA: {
				const auto kasiTawa = static_cast<const KasiTawa*>(kasi);
				assert(dynamic_cast<const KasiPiNimiTawa*>(pokiTawaLipuWawa.at(kasiTawa->linjaTawaTawa).get()) != nullptr && "kasi li wile nimi tawa. taso, ona li ala ni");
				const auto kasiPiNimiTawa = static_cast<const KasiPiNimiTawa*>(pokiTawaLipuWawa.at(kasiTawa->linjaTawaTawa).get());

				std::cout << kasiTawa->kamaJoENimiPiNimiKasi() << "=\"" << kasiTawa->kamaJoENimiPiKasiTawa() 
					<< "\", \"" << kasiPiNimiTawa->kamaJoENimiPiNimiTawa() << "\" - "
					<< ante_toki::anteENimi(ante_toki::kamaJoENimiTawaJan("toki.nanpa_linja"),
						"%d",
						std::to_string(kasiPiNimiTawa->kamaJoELonKasi().nanpaLinja));
					

				if (kasiTawa->kamaJoEIjoTawaTawa().size() > 0) {
					std::cout << ":\n";

					for (const auto& ijo : kasiTawa->kamaJoEIjoTawaTawa())
						tokiEKasiPiKasiSuli(pokiTawaLipuWawa, ijo.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);
				
				} else
					std::cout << "\n";

				break;
			}

			default:
				std::cout << kasi->kamaJoENimiPiNimiKasi() << '\n';
		}
	}

	void tokiEKasiSuli(const std::vector<std::shared_ptr<KasiPiKasiSuli>>& pokiTawaLipuWawa, const std::string& nimiPiLipuWawa) {
		std::cout << "/-------------------\n| " << nimiPiLipuWawa << "\n\\-------------------\n";

		for (size_t nanpa = 0; nanpa < pokiTawaLipuWawa.size(); nanpa++) {
			const KasiPiKasiSuli *const kasiPiKasiSuli = pokiTawaLipuWawa.at(nanpa).get();

			std::cout << ante_toki::anteENimi(
				ante_toki::kamaJoENimiTawaJan("toki.nanpa_linja"), 
				"%d", std::to_string(kasiPiKasiSuli->kamaJoELonKasi().nanpaLinja)) 
				<< ":\n";
			tokiEKasiPiKasiSuli(pokiTawaLipuWawa, pokiTawaLipuWawa.at(nanpa).get(), 1, nanpa);
		}

		std::cout << "\\-------------------\n";
	}
}
