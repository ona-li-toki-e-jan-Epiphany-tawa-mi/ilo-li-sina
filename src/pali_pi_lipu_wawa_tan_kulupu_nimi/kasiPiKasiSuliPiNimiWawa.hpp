#include <string>
#include <vector>
#include <memory>

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
			NIMI_TAWA,
			TAWA,
			TAWA_KEN,
			ALA
	};

	/**
	 * li mama pi kasi ali.
	 * kasi ni li wile ala kepeken. o pali ala e ona.
	 */
	class KasiPiKasiSuli {
		public:
			/**
			 * @brief li pali e kasi sama kasi ni.
			 */
			virtual KasiPiKasiSuli* paliSama() const = 0;

			virtual ~KasiPiKasiSuli() = 0;

			/**
			 * @retval nimi kasi pi kasi ni.
			 */
			virtual NimiKasi kamaJoENimiKasi() const;
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
			KasiPiPanaLonPoki(const std::string& nimiPoki, const std::shared_ptr<KasiPiKasiSuli>& ijoTawaPana);

			KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante) = delete;
			virtual KasiPiPanaLonPoki* paliSama() const override;

			virtual ~KasiPiPanaLonPoki() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			
			const std::string& kamaJoENimiPoki() const;
			std::shared_ptr<const KasiPiKasiSuli> kamaJoEIjoTawaPana() const;

		protected:
			std::string nimiPoki;
			std::shared_ptr<KasiPiKasiSuli> ijoTawaPana;
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

			KasiPiKamaJoTanPoki(const KasiPiKamaJoTanPoki& ante) = delete;
			virtual KasiPiKamaJoTanPoki* paliSama() const override;

			virtual ~KasiPiKamaJoTanPoki() override;

			virtual NimiKasi kamaJoENimiKasi() const override;

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

			KasiPiKamaJoTanPokiPiAnteAla(const KasiPiKamaJoTanPokiPiAnteAla& ante) = delete;
			virtual KasiPiKamaJoTanPokiPiAnteAla* paliSama() const override;

			virtual ~KasiPiKamaJoTanPokiPiAnteAla() override;

			virtual NimiKasi kamaJoENimiKasi() const override;

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
			KasiPiNimiWawa(const std::string& nimiPiNimiWawa, const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaNimiWawa);

			KasiPiNimiWawa(const KasiPiNimiWawa& ante) = delete;
			virtual KasiPiNimiWawa* paliSama() const override;

			virtual ~KasiPiNimiWawa() override;

			virtual NimiKasi kamaJoENimiKasi() const override;

			const std::string& kamaJoENimiPiNimiWawa() const;
			const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kamaJoEKulupuPiIjoTawaNimiWawa() const;

		protected:
			std::string nimiPiNimiWawa;
			std::vector<std::shared_ptr<KasiPiKasiSuli>> kulupuPiIjoTawaNimiWawa;
	};

	/**
	 * kasi ni li tawa ni: nimi wawa tawa li ken kama lon ante.
	 */
	class KasiPiNimiTawa : public KasiPiKasiSuli {
		public:
			/**
			 * @param nimiPiNimiTawa nimi pi nimi tawa. nimi wawa tawa li kepeken e nimi ni tawa tawa.
			 */
			KasiPiNimiTawa(const std::string nimiPiNimiTawa);

			KasiPiNimiTawa(const KasiPiNimiTawa& ante) = delete;
			virtual KasiPiNimiTawa* paliSama() const override;

			virtual ~KasiPiNimiTawa() override;

			virtual NimiKasi kamaJoENimiKasi() const override;

			const std::string& kamaJoENimiPiNimiTawa() const;

		protected:
			std::string nimiPiNimiTawa;
	};

	/**
	 * kasi ni li tawa lon ante.
	 */
	class KasiTawa : public KasiPiKasiSuli {
		public:
			/**
			 * @attention sina li wile pana e nanpa lon this->linjaTawaTawa.
			 */
			KasiTawa();

			KasiTawa(const KasiTawa& ante) = delete;
			virtual KasiTawa* paliSama() const override;

			virtual ~KasiTawa() override;

			virtual NimiKasi kamaJoENimiKasi() const override;

			/**
			 * kasi li tawa linja ni.
			 */
			size_t linjaTawaTawa;
	};

	/**
	 * @breif kasi li ken tawa tan nimi jan.
	 * 
	 * ni li toki e nimi li toki e nimi lon e nimi pi lon ala.
	 * jan li toki e nimi lon la ni li tawa.
	 * ni ala la ni li tawa ala.
	 */
	class KasiPiTawaKen : public KasiTawa {
		public:
			/**
			 * @brief sina li wile pana e nanpa lon linjaTawaTawa. kasi li tawa linja ni.
			 *
			 * @param kasiLon kasi tawa kama jo e nimi lon.
			 * @param kasiPiLonAla kasi tawa kama jo e nimi pi lon ala.
			 * @param kulupuPiIjoTawaToki kulupu kasi ni li kama jo e ijo tawa toki tawa jan.
			 */
			KasiPiTawaKen(const std::shared_ptr<KasiPiKasiSuli>& kasiLon, const std::shared_ptr<KasiPiKasiSuli>& kasiPiLonAla, const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaToki);

			KasiPiTawaKen(const KasiPiTawaKen& ante) = delete;
			virtual KasiPiTawaKen* paliSama() const override;

			virtual ~KasiPiTawaKen() override;

			virtual NimiKasi kamaJoENimiKasi() const override;

			std::shared_ptr<const KasiPiKasiSuli> kamaJoEKasiLon() const;
			std::shared_ptr<const KasiPiKasiSuli> kamaJoEKasiPiLonAla() const;
			const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kamaJoEKulupuPiIjoToki() const;

		protected:
			std::shared_ptr<KasiPiKasiSuli> kasiLon;
			std::shared_ptr<KasiPiKasiSuli> kasiPiLonAla;
			std::vector<std::shared_ptr<KasiPiKasiSuli>> kulupuPiIjoTawaToki;
	};
}
