#include "lawa.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "nimi_wawa.hpp"
#include "../ike.hpp"

namespace lawa {
	/**
	 * @breif li lawa e ilo nanpa kepeken kasi pi kasi suli pi lipu wawa.
	 *
	 * @param kasi kasi pi kasi suli pi ilo nanpa.
	 * @param pokiPiPokiNanpaAli poki pi poki nanpa ali tawa poki e poki sitelen.
	 *
	 * @retval poki sitelen kama tan lawa e ilo nanpa.
	 */
	std::string paliEKasi(const pali::KasiPiKasiSuli* kasi, std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli) {
		switch (kasi->kamaJoENimiKasi()) {
			case pali::NimiKasi::PANA_LON_POKI: {
				auto kasiPiPanaLonPoki = static_cast<const pali::KasiPiPanaLonPoki*>(kasi);
				pokiPiPokiNanpaAli[kasiPiPanaLonPoki->kamaJoENimiPoki()] = paliEKasi(kasiPiPanaLonPoki->kamaJoEIjoTawaPana(), pokiPiPokiNanpaAli);

				return "";
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
					ijoTawaNimiWawa.push_back(paliEKasi(ijo, pokiPiPokiNanpaAli));

				try {
					return pokiPiNimiWawaAli.at(kasiPiNimiWawa->kamaJoENimiPiNimiWawa())(ijoTawaNimiWawa.size(), ijoTawaNimiWawa.data());

				} catch (std::out_of_range& liSuliAla) {
					ike::tokiEIke("TODO", "Unknown function '" + kasiPiNimiWawa->kamaJoENimiPiNimiWawa() + "'");
				}

				break;
			}

			default:
				ike::tokiEIke("TODO", "Invalid instruction '" + std::to_string(static_cast<int>(kasi->kamaJoENimiKasi())) + "'");
		}

		return "";
	}

	void lawaEIloNanpa(const std::vector<pali::KasiPiKasiSuli*>& lipuWawa) {
		std::unordered_map<std::string, std::string> pokiPiPokiNanpaAli;

		for (auto alasaKasi = lipuWawa.begin(); alasaKasi != lipuWawa.end(); alasaKasi++) {
			paliEKasi(*alasaKasi, pokiPiPokiNanpaAli);
		}
	}
}
