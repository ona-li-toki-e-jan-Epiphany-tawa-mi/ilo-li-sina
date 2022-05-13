#include "ike.hpp"
#include <iostream>
#include "../ante_toki/ante_toki.hpp"

namespace kepeken {
	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiIke) {
		std::cerr << nimiPiILO_LI_SINA << ": " << ante_toki::kamaJoENimiTawaJan("ike.nimi") << ": " 
			<< nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const std::string& nimiIke) {
		std::cerr << nimiPiILO_LI_SINA << ": " << nimiPiLipuWawa << ": " 
			<< ante_toki::kamaJoENimiTawaJan("ike.nimi") << ": " << nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke) {
		std::cerr << nimiPiILO_LI_SINA << ": " << nimiPiLipuWawa << "(" << nanpaLinja << "," 
			<< nanpaSitelenLonLinja << "): "  << ante_toki::kamaJoENimiTawaJan("ike.nimi") << ": " 
			<< nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const LonIjoLonLipuLawa *const lonIjo, const std::string& nimiIke) {
		if (lonIjo != nullptr) {
			const auto [linja, sitelen] = *lonIjo;
			tokiEIke(nimiPiILO_LI_SINA, nimiPiLipuWawa, linja, sitelen, nimiIke);

		} else
			tokiEIke(nimiPiILO_LI_SINA, nimiPiLipuWawa, nimiIke);
	}
}
