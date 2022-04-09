#pragma once

#include <string>

/**
 * ilo tawa toki e ike.
 */
namespace kepeken {
	/**
	 * li poki e nanpa linja pi ijo poki e nanpa sitelen ona lon linja lipu wawa.
	 */
	struct LonIjoLonLipuLawa {
		public:
			size_t nanpaLinja, nanpaSitelenLonLinja;
	};


	/**
	 * @brief li toki e ike tawa jan pi lawa e ilo nanpa.
	 * 
	 * @param nimiPiILO_LI_SINA nimi pi lipu wawa ni pi "ilo li sina".
	 * @param nimiIke sona pi kama ike.
	 */
	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiIke);

	/**
	 * @breif li toki e ike tawa jan pi lawa e ilo nanpa.
	 *
	 * @param nimiPiILO_LI_SINA nimi pi lipu wawa ni pi "ilo li sina".
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
	 * @param nimiIke sona pi kama ike.
	 */
	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const std::string& nimiIke);

	/**
	 * @breif li toki e ike e lon ona tawa jan pi lawa e ilo nanpa.
	 *
	 * @param nimiPiILO_LI_SINA nimi pi lipu wawa ni pi "ilo li sina".
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
	 * @param nanpaLinja ike li lon linja pi nanpa ni.
	 * @param nanpaSitelenLonLinja ike li lon sitelen pi nanpa ni lon linja.
	 * @param nimiIke sona pi kama ike.
	 */
	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke);

	/**
	 * @brief li toki e ike e lon ona tawa jan pi lawa e ilo nanpa.
	 * 
	 * @param nimiPiILO_LI_SINA nimi pi lipu wawa ni pi "ilo li sina".
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
	 * @param lonIjo lon ike lon lipu wawa.
	 * @param nimiIke sona pi kama ike.
	 */
	void tokiEIke(const std::string& nimiPiILO_LI_SINA, const std::string& nimiPiLipuWawa, const LonIjoLonLipuLawa& lonIjo, const std::string& nimiIke);
}
