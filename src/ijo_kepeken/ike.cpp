#include "ike.hpp"
#include <iostream>

namespace kepeken {
	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiIke) {
		std::cerr << nimiPiILO_LI_SINA << ": Error: " << nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const std::string& nimiIke) {
		std::cerr << nimiPiILO_LI_SINA << ": " << nimiPiLipuWawa << ": Error: " << nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke) {
		std::cerr << nimiPiILO_LI_SINA << ": " << nimiPiLipuWawa << "(" << nanpaLinja << "," << nanpaSitelenLonLinja << "): Error: " << nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const LonIjoLonLipuLawa& lonIjo, const std::string& nimiIke) {
		const auto [linja, sitelen] = lonIjo;
		tokiEIke(nimiPiILO_LI_SINA, nimiPiLipuWawa, linja, sitelen, nimiIke);
	}
}
