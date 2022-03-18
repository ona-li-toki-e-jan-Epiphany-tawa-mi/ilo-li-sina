#include "kulupu_nimi.hpp"

namespace kipisi {
	const std::string& KulupuNimi::kamaJoENimiPoki() const {
		return this->nimiPokiPiKulupuNimi;
	}

	size_t KulupuNimi::kamaJoENanpaSitelen() const {
		return this->nanpaSitelenLonLinja;
	}
}

