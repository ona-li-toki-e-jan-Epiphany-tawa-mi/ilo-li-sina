#include "kulupu_nimi.hpp"
#include <stdexcept>

namespace kipisi {
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

	std::string KulupuNimi::kamaJoENimiPiNimiKulupu() const {
		switch (this->nimiPiKulupuNimi) {
			case NimiPiKulupuNimi::POKI_NANPA:
				return "POKI_NANPA";
			case NimiPiKulupuNimi::PANA_LON_POKI_NANPA:
				return "PANA_LON_POKI_NANPA";
			case NimiPiKulupuNimi::POKI_SITELEN:
				return "POKI_SITELEN";
			case NimiPiKulupuNimi::NIMI_WAWA:
				return "NIMI_WAWA";
			case NimiPiKulupuNimi::POKI_PI_IJO_TAWA_NIMI_WAWA:
				return "POKI_PI_IJO_TAWA_NIMI_WAWA";
			case NimiPiKulupuNimi::LINJA_SITELEN_SIN:
				return "LINJA_SITELEN_SIN";
			case NimiPiKulupuNimi::NIMI_TAWA_TAWA:
				return "NIMI_TAWA_TAWA";
			case NimiPiKulupuNimi::ALA:
				return "ALA";

			default:
				throw std::out_of_range("Encountered unknown token type with a numeric value of " + static_cast<int>(this->nimiPiKulupuNimi));
		}
	}
}

