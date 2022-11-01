#pragma once

#include <memory>
#include "toki.hpp"

/**
 * @brief ilo tawa toki e ike.
 */
namespace kepeken {
	/**
	 * @brief li ante e nimi tawa ilo ni. li tawa toki ike.
	 * @attention sina wile kepeken e ni lon monsi pi kepeken e kamaJoENimiPiILO_LI_SINA().
	 * 
	 * @param nimi nimi pi ilo ni.
	 */
	void anteENimiPiILO_LI_SINA(const std::string& nimi);

	/**
	 * @brief li pana e nimi pi ilo ni.
	 * @attention sina wile kepeken e anteENimiPiILO_LI_SINA lon monsi pi kepeken e ni.
	 * 
	 * @return nimi pi ilo ni.
	 * @throws std::logic_error anteENimiPiILO_LI_SINA() li kepeken lon tenpo ala.
	 */
	const std::string& kamaJoENimiPiILO_LI_SINA() noexcept(false);


	/**
	 * @brief li poki e nanpa linja pi ijo poki e nanpa sitelen ona lon linja lipu wawa.
	 */
	struct LonIjo {
		public:
			size_t nanpaLinja, nanpaSitelenLonLinja;
	};

	/**
	 * @brief poki tawa poki e sona pi kama ike en tan ike.
	 */
	struct IjoPiTokiIke {
		public:
			/**
			 * @param nimiIke sona pi kama ike.
			 */
			IjoPiTokiIke(const std::string& nimiIke);
			/**
			 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
			 * @param nimiIke sona pi kama ike.
			 */
			IjoPiTokiIke(const std::string& nimiPiLipuWawa, const std::string& nimiIke);
			/**
			 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
			 * @param nanpaLinja ike li lon linja pi nanpa ni.
			 * @param nanpaSitelenLonLinja ike li lon sitelen pi nanpa ni lon linja.
			 * @param nimiIke sona pi kama ike.
			 */
			IjoPiTokiIke(const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke);
			/**
			 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
			 * @param lonIjo lon ike lon lipu wawa.
			 * @param nimiIke sona pi kama ike.
			 */
			IjoPiTokiIke(const std::string& nimiPiLipuWawa, const LonIjo& lonIjo, const std::string& nimiIke);
			/**
			 * @param nimiPiLipuWawa nimi pi lipu wawa pi tenpo ni.
			 * @param lonIjo lon ike lon lipu wawa. li ijo Nullptr la li toki ala e lon.
			 * @param nimiIke sona pi kama ike.
			 */
			IjoPiTokiIke(const std::string& nimiPiLipuWawa, const LonIjo *const lonIjo, const std::string& nimiIke);

			/**
			 * @return nimi pi lipu wawa. ike li lon ona.
			 */
			const std::string* kamaJoENimiPiLipuWawa() const;
			/**
			 * @return lon ike lon lipu wawa.
			 */
			const LonIjo* kamaJoELonIjo() const;
			/**
			 * @return nimi sona pi kama ike.
			 */
			const std::string& kamaJoENimiIke() const;

		private:
			const std::unique_ptr<const std::string> nimiPiLipuWawa;
			const std::unique_ptr<const LonIjo> lonIjo;
			const std::string nimiIke;
	};

	/**
	 * @brief li toki e ike tawa jan.
	 * 
	 * @param ike sona pi kama ike en tan ike.
	 */
	void tokiEIke(const IjoPiTokiIke& ike);
}
