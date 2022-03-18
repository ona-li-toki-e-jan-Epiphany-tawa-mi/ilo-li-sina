#include "ike.hpp"
#include <iostream>

namespace ike {
	void tokiEIke(const std::string& nimiPiLipuWawa, const std::string& nimiIke) {
		std::cerr << "ilo_li_sina: " << nimiPiLipuWawa << ": Error: " << nimiIke << std::endl;
		exit(1);
	}

	void tokiEIke(const std::string& nimiPiLipuWawa, size_t nanpaLinja, size_t nanpaSitelenLonLinja, const std::string& nimiIke) {
		std::cerr << "ilo_li_sina: " << nimiPiLipuWawa << "(" << nanpaLinja << "," << nanpaSitelenLonLinja << "): Error: " << nimiIke << std::endl;
		exit(1);
	}
}
