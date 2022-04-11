#pragma once

#include <string>
#include "../ijo_kepeken/ike.hpp"

/**
 * kulupu nimi. ilo kipisi li kipisi e lipu wawa la ona li pali e kulupu pi ni mute.
 */
namespace kipisi {
	/**
	 * nimi pi kulupu nimi li toki e ni: kulupu nimi li pali e seme.
	 */
	enum class NimiPiKulupuNimi {
		POKI_NANPA,
		PANA_LON_POKI_NANPA,
		POKI_SITELEN,
		NIMI_WAWA,
		POKI_PI_IJO_TAWA_NIMI_WAWA,
		LINJA_SITELEN_SIN,
		NIMI_TAWA_TAWA,
		ALA
	};

	/**
	 * @brief li kama jo e nimi pi nimi pi kulupu nimi tawa pana tawa jan.
	 * 
	 * @param nimiPiKulupuNimi nimi pi kulupu nimi. 
	 *
	 * @return nimi pi nimi pi kulupu nimi.
	 * @throws std::out_of_range nimi pi kulupu nimi li jo ala e nimi pi nimi pi kulupu nimi.
	 */
	std::string kamaJoENimiPiNimiKulupu(NimiPiKulupuNimi nimiPiKulupuNimi) noexcept(false);


	/**
	 * kulupu nimi li tawa ni: ilo kipisi li ken pali e lipu wawa pi ijo mute ala.
	 */
	struct KulupuNimi {
		public:
			/**
			 * @param nimiPiKulupuNimi nimi pi kulupu nimi ni.
			 * @param nimiPokiPiKulupuNimi nimi ni li poki lon kulupu nimi ni. nimi poki ali li jo e nimi kulupu.
			 * @param nanpaSitelenLonLinja kulupu nimi li open lon sitelen pi nanpa ni lon linja
			 */
			KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const std::string& nimiPokiPiKulupuNimi, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			/**
			 * @breif nimi poki pi kulupu nimi li kama jo e poki pi sitelen ala ("") kepeken ni.
			 *
			 * @param nimiPiKulupuNimi nimi pi kulupu nimi ni.
			 * @param nanpaSitelenLonLinja kulupu nimi li open lon sitelen pi nanpa ni lon linja
			 */
			KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			/**
			 * @return nimi poki lon kulupu nimi ni.
			 */
			const std::string& kamaJoENimiPoki() const;

			/**
			 * @return lon pi kulupu nimi
			 */
			const kepeken::LonIjoLonLipuLawa& kamaJoELon() const;


			NimiPiKulupuNimi nimiPiKulupuNimi;

		private:
			const std::string nimiPokiPiKulupuNimi;
			const kepeken::LonIjoLonLipuLawa lon;
	};
}
