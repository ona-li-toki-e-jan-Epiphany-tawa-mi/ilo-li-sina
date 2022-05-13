#include "kulupu_nimi.hpp"
#include <cassert>
#include "../ante_toki/ante_toki.hpp"

namespace kipisi {
	std::string kamaJoENimiPiNimiKulupu(NimiPiKulupuNimi nimiPiKulupuNimi) {
		switch (nimiPiKulupuNimi) {
			case NimiPiKulupuNimi::POKI_NANPA:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.poki_nanpa");
			case NimiPiKulupuNimi::PANA_LON_POKI_NANPA:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.pana_lon_poki_nanpa");
			case NimiPiKulupuNimi::POKI_SITELEN:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.poki_sitelen");
			case NimiPiKulupuNimi::NIMI_WAWA:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.nimi_wawa");
			case NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.poki_pi_ijo_tawa_nimi_wawa");
			case NimiPiKulupuNimi::LINJA_SITELEN_SIN:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.linja_sitelen_sin");
			case NimiPiKulupuNimi::NIMI_TAWA_TAWA:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.nimi_tawa_tawa");
			case NimiPiKulupuNimi::ALA:
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.ala");

			default:
				assert(false && "li kama jo e nimi pi kulupu nimi pi sona ala");
				return ante_toki::kamaJoENimiTawaJan("toki.kulupu_nimi.ala");
		}
	}


	KulupuNimi::KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const std::string& nimiPokiPiKulupuNimi, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: nimiPiKulupuNimi(nimiPiKulupuNimi), nimiPokiPiKulupuNimi(nimiPokiPiKulupuNimi), lon({nanpaLinja, nanpaSitelenLonLinja}) {}

	KulupuNimi::KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: nimiPiKulupuNimi(nimiPiKulupuNimi), nimiPokiPiKulupuNimi(""), lon({nanpaLinja, nanpaSitelenLonLinja}) {}

	const std::string& KulupuNimi::kamaJoENimiPoki() const {
		return this->nimiPokiPiKulupuNimi;
	}

	const kepeken::LonIjoLonLipuLawa& KulupuNimi::kamaJoELon() const {
		return this->lon;
	}
}

