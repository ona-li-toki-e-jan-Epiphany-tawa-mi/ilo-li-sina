#include <string>
#include <vector>

/**
 * kasi pi kasi suli tawa pali e lipu wawa tan kulupu nimi.
 */
namespace pali {
	/**
	 * nimi kasi li toki e ni: kasi li pali e seme.
	 */
	enum class NimiKasi {
			PANA_LON_POKI,
			KAMA_JO_TAN_POKI,
			KAMA_JO_TAN_POKI_PI_ANTE_ALA,
			NIMI_WAWA,
			ALA
	};

	/**
	 * li mama pi kasi ali.
	 * kasi ni li wile ala kepeken. o pali ala e ona.
	 */
	class KasiPiKasiSuli {
		public:
			virtual ~KasiPiKasiSuli();

			/**
			 * @retval nimi kasi pi kasi ni.
			 */
			NimiKasi kamaJoENimiKasi() const;

		protected:
			NimiKasi nimiKasi = NimiKasi::ALA;
	};

	/**
	 * kasi ni li tawa ni: lipu wawa li pana e ijo lon poki nanpa.
	 */
	class KasiPiPanaLonPoki : public KasiPiKasiSuli {
		public:
			/**
			 * @param nimiPoki ijo li pana lon poki pi nimi ni.
			 * @param ijoTawaPana kasi ni li kama jo e ijo tawa poki.
			 */
			KasiPiPanaLonPoki(const std::string& nimiPoki, KasiPiKasiSuli* ijoTawaPana);

			KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante);

			KasiPiPanaLonPoki(KasiPiPanaLonPoki&& ante);

			KasiPiPanaLonPoki& operator=(KasiPiPanaLonPoki&& ante);

			~KasiPiPanaLonPoki() override;

			const std::string& kamaJoENimiPoki() const;
			const KasiPiKasiSuli* kamaJoEIjoTawaPana() const;

		protected:
			std::string nimiPoki;
			KasiPiKasiSuli* ijoTawaPana;
	};

	/**
	 * kasi ni li tawa ni: lipu wawa li kama jo e ijo tan poki nanpa.
	 */
	class KasiPiKamaJoTanPoki : public KasiPiKasiSuli {
		public:
			/**
			 * @param nimiPoki ijo li kama tan poki pi nimi ni.
			 */
			KasiPiKamaJoTanPoki(const std::string& nimiPoki);

			const std::string& kamaJoENimiPoki() const;

		protected:
			std::string nimiPoki;
	};

	/**
	 * kasi ni li tawa ni: lipu wawa li kama jo e ijo tan poki nanpa pi ante ala.
	 */
	class KasiPiKamaJoTanPokiPiAnteAla : public KasiPiKasiSuli {
		public:
			/**
			 * @param ijoTawaKama lipu lawa li kepeken e kasi ni la ijo ni li pana tawa ona.
			 */
			KasiPiKamaJoTanPokiPiAnteAla(const std::string& ijoTawaKama);

			const std::string& kamaJoEIjoPoki() const;

		protected:
			std::string ijoTawaKama;
	};

	/**
	 * kasi ni li tawa ni: lipu wawa li kepeken e nimi wawa tawa pali e ijo.
	 */
	class KasiPiNimiWawa : public KasiPiKasiSuli {
		public:
			/**
			 * @param nimiPiNimiWawa ni li nimi pi nimi wawa li toki e ni: ona li pali e seme.
			 * @param kulupuPiIjoTawaNimiWawa kasi pi kulupu ni li kama jo e ijo tawa kepeken pi nimi wawa.
			 */
			KasiPiNimiWawa(const std::string& nimiPiNimiWawa, const std::vector<KasiPiKasiSuli*>& kulupuPiIjoTawaNimiWawa);

			KasiPiNimiWawa(const KasiPiNimiWawa& ante);

			KasiPiNimiWawa(KasiPiNimiWawa&& ante);

			KasiPiNimiWawa& operator=(KasiPiNimiWawa&& ante);

			~KasiPiNimiWawa() override;

			const std::string& kamaJoENimiPiNimiWawa() const;
			const std::vector<KasiPiKasiSuli*>& kamaJoEKulupuPiIjoTawaNimiWawa() const;

		protected:
			std::string nimiPiNimiWawa;
			std::vector<KasiPiKasiSuli*> kulupuPiIjoTawaNimiWawa;
	};
}
