#include "lawa.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "nimi_wawa.hpp"
#include "../ike.hpp"

// TODO o pona e toki ike.

namespace lawa {
	/**
	 * @breif li lawa e ilo nanpa kepeken kasi pi kasi suli pi lipu wawa.
	 *
	 * @param kasi kasi pi kasi suli pi ilo nanpa.
	 * @param pokiPiPokiNanpaAli poki pi poki nanpa ali tawa poki e poki sitelen.
	 * @param nanpaLinja nanpa pi linja pi tenpo ni.
	 *
	 * @retval poki sitelen kama tan lawa e ilo nanpa.
	 */
	std::string paliEKasi(const pali::KasiPiKasiSuli* kasi, std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli, size_t& nanpaLinja) {
		switch (kasi->kamaJoENimiKasi()) {
			case pali::NimiKasi::PANA_LON_POKI: {
				auto kasiPiPanaLonPoki = static_cast<const pali::KasiPiPanaLonPoki*>(kasi);
				pokiPiPokiNanpaAli[kasiPiPanaLonPoki->kamaJoENimiPoki()] = paliEKasi(kasiPiPanaLonPoki->kamaJoEIjoTawaPana(), pokiPiPokiNanpaAli, nanpaLinja);

				break;
			}

			case pali::NimiKasi::KAMA_JO_TAN_POKI:
				return pokiPiPokiNanpaAli.at(static_cast<const pali::KasiPiKamaJoTanPoki*>(kasi)->kamaJoENimiPoki());

			case pali::NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA:
				return static_cast<const pali::KasiPiKamaJoTanPokiPiAnteAla*>(kasi)->kamaJoEIjoPoki();

			case pali::NimiKasi::NIMI_WAWA: {
				auto kasiPiNimiWawa = static_cast<const pali::KasiPiNimiWawa*>(kasi);
				std::vector<std::string> ijoTawaNimiWawa;

				ijoTawaNimiWawa.reserve(kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa().size());
				for (const pali::KasiPiKasiSuli* ijo : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
					ijoTawaNimiWawa.push_back(paliEKasi(ijo, pokiPiPokiNanpaAli, nanpaLinja));

				try {
					return pokiPiNimiWawaAli.at(kasiPiNimiWawa->kamaJoENimiPiNimiWawa())(ijoTawaNimiWawa.size(), ijoTawaNimiWawa.data());

				} catch (std::out_of_range& liSuliAla) {
					ike::tokiEIke("TODO", "Unknown function '" + kasiPiNimiWawa->kamaJoENimiPiNimiWawa() + "'");
				}

				break;
			}

			case pali::NimiKasi::TAWA_KEN: {
				auto kasiPiPaliKen = static_cast<const pali::KasiPiTawaKen*>(kasi);
				std::string nimiLon = paliEKasi(kasiPiPaliKen->kamaJoEKasiLon(), pokiPiPokiNanpaAli, nanpaLinja);
				std::string nimiPiLonAla = paliEKasi(kasiPiPaliKen->kamaJoEKasiPiLonAla(), pokiPiPokiNanpaAli, nanpaLinja);

				while (true) {
					for (pali::KasiPiKasiSuli* ijoTawaToki : kasiPiPaliKen->kamaJoEKulupuPiIjoToki())
						std::cout << paliEKasi(ijoTawaToki, pokiPiPokiNanpaAli, nanpaLinja);
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
				ike::tokiEIke("TODO", "Invalid instruction '" + std::to_string(static_cast<int>(kasi->kamaJoENimiKasi())) + "'");
		}

		return "";
	}

	void lawaEIloNanpa(const std::vector<pali::KasiPiKasiSuli*>& lipuWawa) {
		std::unordered_map<std::string, std::string> pokiPiPokiNanpaAli;

		for (size_t nanpa = 0; nanpa != lipuWawa.size(); nanpa++)
			paliEKasi(lipuWawa.at(nanpa), pokiPiPokiNanpaAli, nanpa);
	}
}
