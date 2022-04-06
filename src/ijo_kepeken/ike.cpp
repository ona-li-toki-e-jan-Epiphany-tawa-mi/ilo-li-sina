#include "ike.hpp"
#include <iostream>

namespace kepeken {
	void tokiEIke(const std::string& nimiPiLipuWawa, const std::string& nimiIke) {
		std::cerr << "ilo_li_sina: " << nimiPiLipuWawa << ": Error: " << nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke) {
		std::cerr << "ilo_li_sina: " << nimiPiLipuWawa << "(" << nanpaLinja << "," << nanpaSitelenLonLinja << "): Error: " << nimiIke << '\n';
	}

	void tokiEIke(const std::string& nimiPiLipuWawa, const LonIjoLonLipuLawa& lonIjo, const std::string& nimiIke) {
		const auto [linja, sitelen] = lonIjo;
		tokiEIke(nimiPiLipuWawa, linja, sitelen, nimiIke);
	}
}
