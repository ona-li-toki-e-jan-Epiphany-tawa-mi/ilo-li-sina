#include "kulupu_nimi.hpp"

namespace kipisi {
	KulupuNimi::KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const std::string& nimiPokiPiKulupuNimi, const size_t nanpaSitelenLonLinja)
		: nimiPiKulupuNimi(nimiPiKulupuNimi), nimiPokiPiKulupuNimi(nimiPokiPiKulupuNimi), nanpaSitelenLonLinja(nanpaSitelenLonLinja) {}

	KulupuNimi::KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const size_t nanpaSitelenLonLinja)
		: nimiPiKulupuNimi(nimiPiKulupuNimi), nimiPokiPiKulupuNimi(""), nanpaSitelenLonLinja(nanpaSitelenLonLinja) {}

	const std::string& KulupuNimi::kamaJoENimiPoki() const {
		return this->nimiPokiPiKulupuNimi;
	}

	size_t KulupuNimi::kamaJoENanpaSitelen() const {
		return this->nanpaSitelenLonLinja;
	}
}

