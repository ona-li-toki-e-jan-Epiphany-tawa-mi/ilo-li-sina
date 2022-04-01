#pragma once

#include <string>

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
	 * kulupu nimi li tawa ni: ilo kipisi li ken pali e lipu wawa pi ijo mute ala.
	 */
	struct KulupuNimi {
		public:
			/**
			 * @param nimiPiKulupuNimi nimi pi kulupu nimi ni.
			 * @param nimiPokiPiKulupuNimi nimi ni li poki lon kulupu nimi ni. nimi poki ali li jo e nimi kulupu.
			 * @param nanpaSitelenLonLinja kulupu nimi li open lon sitelen pi nanpa ni lon linja
			 */
			KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const std::string& nimiPokiPiKulupuNimi, const size_t nanpaSitelenLonLinja);

			/**
			 * @breif nimi poki pi kulupu nimi li kama jo e poki pi sitelen ala ("") kepeken ni.
			 *
			 * @param nimiPiKulupuNimi nimi pi kulupu nimi ni.
			 * @param nanpaSitelenLonLinja kulupu nimi li open lon sitelen pi nanpa ni lon linja
			 */
			KulupuNimi(const NimiPiKulupuNimi nimiPiKulupuNimi, const size_t nanpaSitelenLonLinja);

			/**
			 * @return nimi poki lon kulupu nimi ni.
			 */
			const std::string& kamaJoENimiPoki() const;

			/**
			 * @return kulupu nimi ni li open lon sitelen pi nanpa ni lon linja sitelen.
			 */
			size_t kamaJoENanpaSitelen() const;


			NimiPiKulupuNimi nimiPiKulupuNimi;

		private:
			const std::string nimiPokiPiKulupuNimi;
			const size_t nanpaSitelenLonLinja;
	};
}
