#pragma once

#include <string>

/**
 * ilo tawa toki e ike.
 */
namespace ike {
	/**
	 * @breif li toki e ike tawa jan pi lawa e ilo nanpa.
	 *
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
	 * @param nimiIke sona pi kama ike.
	 */
	void tokiEIke(const std::string& nimiPiLipuWawa, const std::string& nimiIke);

	/**
	 * @breif li toki e ike e lon ona tawa jan pi lawa e ilo nanpa.
	 *
	 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
	 * @param nanpaLinja ike li lon linja pi nanpa ni.
	 * @param nanpaSitelenLonLinja ike li lon sitelen pi nanpa ni lon linja.
	 * @param nimiIke sona pi kama ike.
	 */
	void tokiEIke(const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke);
}
