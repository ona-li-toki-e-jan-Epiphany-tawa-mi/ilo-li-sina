#include "lawa.hpp"
#include <iostream>
#include <cassert>
#include "../ante_toki/ante_toki.hpp"

namespace lawa {
	/**
	 * @brief sona tawa lawa e ilo nanpa.
	 */
	struct SonaTawaLawa {
		const std::string& nimiPiLipuWawa;

		std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli;
		size_t& nanpaLinja;
		bool liWilePini = false;
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
		if (sonaTawaLawa.liWilePini)
			return "";

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

				} catch (const std::out_of_range& pokiNanpaLiLonAla) {
					kepeken::tokiEIke({
						sonaTawaLawa.nimiPiLipuWawa, 
						kasiPiKamaJoTanPoki->kamaJoELonKasi(), 
						ante_toki::anteENimi(
							ante_toki::kamaJoENimiTawaJan("ike.lawa.poki_nimi.li_lukin_kama_jo_tan_poki_pi_sona_ala"),
							"%s", kasiPiKamaJoTanPoki->kamaJoENimiPoki())});

					sonaTawaLawa.liWilePini = true;
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

				if (sonaTawaLawa.liWilePini)
					break;


				std::optional<std::string> ijoTanNimi = kasiPiNimiWawa->kamaJoENimiWawa()(
					sonaTawaLawa.nimiPiLipuWawa, &kasiPiNimiWawa->kamaJoELonKasi(), ijoTawaNimiWawa);

				if (!ijoTanNimi.has_value()) {
					sonaTawaLawa.liWilePini = true;
					sonaTawaLawa.nanpaIke = 0;

					break;
				}

				return *ijoTanNimi;
			}

			case pali::NimiKasi::TAWA: {
				const auto kasiTawa = static_cast<const pali::KasiTawa*>(kasi);
				std::list<std::string> ijoTawaTawa;

				for (const auto& ijo : kasiTawa->kamaJoEIjoTawaTawa())
					ijoTawaTawa.push_back(paliEKasi(sonaTawaLawa, ijo.get()));

				if (sonaTawaLawa.liWilePini)
					break;
					

				std::optional<std::tuple<bool, std::string>> ijoTanKasiTawa = kasiTawa->liKenTawa(
					sonaTawaLawa.nimiPiLipuWawa, ijoTawaTawa);

				if (ijoTanKasiTawa.has_value()) {
					const auto [liKen, nimi] = *ijoTanKasiTawa;

					if (liKen)
						sonaTawaLawa.nanpaLinja = kasiTawa->linjaTawaTawa;

					return nimi;

				} else {
					sonaTawaLawa.liWilePini = true;
					sonaTawaLawa.nanpaIke = 1;
				}
					
				break;
			}

			case pali::NimiKasi::NIMI_TAWA:
				break;

			default:
				assert(false && "lawa la li kama jo e kasi pi kasi suli pi sona ala");
		}

		return "";
	}

	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, std::unordered_map<std::string, std::string>& pokiPiPokiNanpaAli, const std::string& nimiPiLipuWawa) {
		size_t nanpaLinja = 0;

		SonaTawaLawa sonaTawaLawa = {nimiPiLipuWawa, pokiPiPokiNanpaAli, nanpaLinja};

		for (; nanpaLinja != lipuWawa.size(); nanpaLinja++) {
			paliEKasi(sonaTawaLawa, lipuWawa.at(nanpaLinja).get());

			if (sonaTawaLawa.liWilePini)
				break;
		}

		return sonaTawaLawa.nanpaIke;
	}

	int lawaEIloNanpa(const std::vector<std::shared_ptr<pali::KasiPiKasiSuli>>& lipuWawa, const std::string& nimiPiLipuWawa) {
		std::unordered_map<std::string, std::string> pokiPiPokiNanpaAli;
		return lawaEIloNanpa(lipuWawa, pokiPiPokiNanpaAli, nimiPiLipuWawa);
	}
}
