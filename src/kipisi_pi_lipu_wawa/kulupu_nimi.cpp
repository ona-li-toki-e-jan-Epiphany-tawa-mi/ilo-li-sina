#include "kulupu_nimi.hpp"

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
}

