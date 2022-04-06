#include "lawa.hpp"
#include <iostream>

namespace lawa {
	// TODO o pana e sona tawa lawa lon poki Struct.
	/**
	 * @breif li lawa e ilo nanpa kepeken kasi pi kasi suli pi lipu wawa.
	 *
	 * @param kasi kasi pi kasi suli pi ilo nanpa.
	 * @param pokiPiPokiNanpaAli poki pi poki nanpa ali tawa poki e poki sitelen.
	 * @param nanpaLinja nanpa pi linja pi tenpo ni.
	 * @param nimiPiLipuWawa nimi pi lipu wawa.
	 *
	 * @return poki sitelen kama tan lawa e ilo nanpa.
	 */
	std::string paliEKasi(const pali::KasiPiKasiSuli* kasi, std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli, size_t& nanpaLinja, const std::string& nimiPiLipuWawa) {
		switch (kasi->kamaJoENimiKasi()) {
			case pali::NimiKasi::PANA_LON_POKI: {
				const auto kasiPiPanaLonPoki = static_cast<const pali::KasiPiPanaLonPoki*>(kasi);
				pokiPiPokiNanpaAli[kasiPiPanaLonPoki->kamaJoENimiPoki()] = paliEKasi(
					kasiPiPanaLonPoki->kamaJoEIjoTawaPana().get(), pokiPiPokiNanpaAli, nanpaLinja, nimiPiLipuWawa);

				break;
			}

			case pali::NimiKasi::KAMA_JO_TAN_POKI: {
				const auto kasiPiKamaJoTanPoki = static_cast<const pali::KasiPiKamaJoTanPoki*>(kasi);

				try {
					return pokiPiPokiNanpaAli.at(kasiPiKamaJoTanPoki->kamaJoENimiPoki());

				} catch (const std::out_of_range& liSuliAla) {
					kepeken::tokiEIke(nimiPiLipuWawa, kasiPiKamaJoTanPoki->kamaJoELonKasi(), "Attempted to get value from undeclared variable '" + kasiPiKamaJoTanPoki->kamaJoENimiPoki() + "'");
					exit(1);
				}
			}

			case pali::NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA:
				return static_cast<const pali::KasiPiKamaJoTanPokiPiAnteAla*>(kasi)->kamaJoEIjoPoki();

			case pali::NimiKasi::NIMI_WAWA: {
				const auto kasiPiNimiWawa = static_cast<const pali::KasiPiNimiWawa*>(kasi);
				std::vector<std::string> ijoTawaNimiWawa;

				ijoTawaNimiWawa.reserve(kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa().size());
				for (const std::shared_ptr<pali::KasiPiKasiSuli>& ijo : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
					ijoTawaNimiWawa.push_back(paliEKasi(
						ijo.get(), pokiPiPokiNanpaAli, nanpaLinja, nimiPiLipuWawa));

				return kasiPiNimiWawa->kamaJoENimiWawa()(ijoTawaNimiWawa.size(), ijoTawaNimiWawa.data());
			}

			case pali::NimiKasi::TAWA_KEN: {
				const auto kasiPiPaliKen = static_cast<const pali::KasiPiTawaKen*>(kasi);
				const std::string nimiLon = paliEKasi(kasiPiPaliKen->kamaJoEKasiLon().get(), pokiPiPokiNanpaAli, nanpaLinja, nimiPiLipuWawa);
				const std::string nimiPiLonAla = paliEKasi(kasiPiPaliKen->kamaJoEKasiPiLonAla().get(), pokiPiPokiNanpaAli, nanpaLinja, nimiPiLipuWawa);

				// TODO o pali e ni: nimi tawa toki li lon ala la o toki ala e sitelen nasa " " lon open pi nimi pi lon en lon ala.
				while (true) {
					for (const std::shared_ptr<pali::KasiPiKasiSuli>& ijoTawaToki : kasiPiPaliKen->kamaJoEKulupuPiIjoToki())
						std::cout << paliEKasi(
							ijoTawaToki.get(), pokiPiPokiNanpaAli, nanpaLinja, nimiPiLipuWawa);
					std::cout << " (" << nimiLon << '/' << nimiPiLonAla << ")\n";

					std::string nimiTanJan;
					std::getline(std::cin, nimiTanJan);

					if (nimiTanJan == nimiLon) {
						nanpaLinja = kasiPiPaliKen->linjaTawaTawa - 1;
						break;
					}

					if (nimiTanJan == nimiPiLonAla)
						break;
				}

				break;
			}

			case pali::NimiKasi::TAWA:
				nanpaLinja = static_cast<const pali::KasiTawa*>(kasi)->linjaTawaTawa;
				break;

			case pali::NimiKasi::NIMI_TAWA:
				break;

			default:
				kepeken::tokiEIke(nimiPiLipuWawa, kasi->kamaJoELonKasi(), "Invalid instruction '" + std::to_string(static_cast<int>(kasi->kamaJoENimiKasi())) + "'");
				exit(-1);
		}

		return "";
	}

	void lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, const std::string& nimiPiLipuWawa) {
		std::unordered_map<std::string, std::string> pokiPiPokiNanpaAli;

		for (size_t nanpa = 0; nanpa != lipuWawa.size(); nanpa++)
			paliEKasi(lipuWawa.at(nanpa).get(), pokiPiPokiNanpaAli, nanpa, nimiPiLipuWawa);
	}
}
