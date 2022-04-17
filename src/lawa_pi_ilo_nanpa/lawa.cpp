#include "lawa.hpp"
#include <iostream>
#include "../ante_toki/ante_toki.hpp"

namespace lawa {
	/**
	 * @brief sona tawa lawa e ilo nanpa.
	 */
	struct SonaTawaLawa {
		const std::string& nimiPiILO_LI_SINA;
		const std::string& nimiPiLipuWawa;

		std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli;
		size_t& nanpaLinja;
		int nanpaIke = 0;
	};

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
	std::string paliEKasi(SonaTawaLawa& sonaTawaLawa, const pali::KasiPiKasiSuli* kasi) {
		switch (kasi->kamaJoENimiKasi()) {
			case pali::NimiKasi::PANA_LON_POKI: {
				const auto kasiPiPanaLonPoki = static_cast<const pali::KasiPiPanaLonPoki*>(kasi);
				sonaTawaLawa.pokiPiPokiNanpaAli[kasiPiPanaLonPoki->kamaJoENimiPoki()] = paliEKasi(
					sonaTawaLawa, kasiPiPanaLonPoki->kamaJoEIjoTawaPana().get());

				break;
			}

			case pali::NimiKasi::KAMA_JO_TAN_POKI: {
				const auto kasiPiKamaJoTanPoki = static_cast<const pali::KasiPiKamaJoTanPoki*>(kasi);

				try {
					return sonaTawaLawa.pokiPiPokiNanpaAli.at(kasiPiKamaJoTanPoki->kamaJoENimiPoki());

				} catch (const std::out_of_range& liSuliAla) {
					kepeken::tokiEIke(
						sonaTawaLawa.nimiPiILO_LI_SINA, sonaTawaLawa.nimiPiLipuWawa, 
						kasiPiKamaJoTanPoki->kamaJoELonKasi(), 
						ante_toki::anteENimi(
							ante_toki::kamaJoENimiTawaJan("ike.lawa.poki_nimi.li_lukin_kama_jo_tan_poki_pi_sona_ala"),
							"%s", kasiPiKamaJoTanPoki->kamaJoENimiPoki()));
					sonaTawaLawa.nanpaIke = 1;

					break;
				}
			}

			case pali::NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA:
				return static_cast<const pali::KasiPiKamaJoTanPokiPiAnteAla*>(kasi)->kamaJoEIjoPoki();

			case pali::NimiKasi::NIMI_WAWA: {
				const auto kasiPiNimiWawa = static_cast<const pali::KasiPiNimiWawa*>(kasi);
				pali::string_lqueue ijoTawaNimiWawa;

				for (const std::shared_ptr<pali::KasiPiKasiSuli>& ijo : kasiPiNimiWawa->kamaJoEKulupuPiIjoTawaNimiWawa())
					ijoTawaNimiWawa.push(paliEKasi(
						sonaTawaLawa, ijo.get()));

				return kasiPiNimiWawa->kamaJoENimiWawa()(ijoTawaNimiWawa);
			}

			case pali::NimiKasi::TAWA_KEN: {
				const auto kasiPiPaliKen = static_cast<const pali::KasiPiTawaKen*>(kasi);
				const std::string nimiLon = paliEKasi(sonaTawaLawa, kasiPiPaliKen->kamaJoEKasiLon().get());
				const std::string nimiPiLonAla = paliEKasi(sonaTawaLawa, kasiPiPaliKen->kamaJoEKasiPiLonAla().get());

				// FIXME lipu ni li kama jo e nimi tan poki Stdin la ni li pini ala. o pona e ni.
				while (true) {
					const std::list<std::shared_ptr<pali::KasiPiKasiSuli>>& kulupuPiIjoTawaToki = kasiPiPaliKen->kamaJoEKulupuPiIjoToki();
					
					if (!kulupuPiIjoTawaToki.empty()) {
						for (const std::shared_ptr<pali::KasiPiKasiSuli>& ijoTawaToki : kulupuPiIjoTawaToki)
							std::cout << paliEKasi(sonaTawaLawa, ijoTawaToki.get());
						std::cout << ' ';
					}
					std::cout << "(" << nimiLon << '/' << nimiPiLonAla << ")\n";

					std::string nimiTanJan;
					std::getline(std::cin, nimiTanJan);

					if (nimiTanJan == nimiLon) {
						sonaTawaLawa.nanpaLinja = kasiPiPaliKen->linjaTawaTawa;
						break;
					}

					if (nimiTanJan == nimiPiLonAla)
						break;
				}

				break;
			}

			case pali::NimiKasi::TAWA:
				sonaTawaLawa.nanpaLinja = static_cast<const pali::KasiTawa*>(kasi)->linjaTawaTawa;
				break;

			case pali::NimiKasi::NIMI_TAWA:
				break;

			default:
				throw std::out_of_range("lawa la li kama jo e kasi pi kasi suli pi sona ala pi nimi " + pali::kamaJoENimiPiNimiKasi(kasi->kamaJoENimiKasi()));
		}

		return "";
	}

	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
		size_t nanpaLinja = 0;

		SonaTawaLawa sonaTawaLawa = {nimiPiILO_LI_SINA, nimiPiLipuWawa, pokiPiPokiNanpaAli, nanpaLinja};

		for (; nanpaLinja != lipuWawa.size(); nanpaLinja++) {
			paliEKasi(sonaTawaLawa, lipuWawa.at(nanpaLinja).get());

			if (sonaTawaLawa.nanpaIke != 0)
				break;
		}

		return sonaTawaLawa.nanpaIke;
	}

	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
		std::unordered_map<std::string, std::string> pokiPiPokiNanpaAli;
		return lawaEIloNanpa(lipuWawa, pokiPiPokiNanpaAli, nimiPiLipuWawa, nimiPiILO_LI_SINA);
	}
}
