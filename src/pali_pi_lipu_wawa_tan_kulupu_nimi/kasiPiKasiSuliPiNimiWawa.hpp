#pragma once

#include <memory>
#include <optional>
#include <tuple>
#include "nimi_wawa.hpp"

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
			ALA
	};


	/**
	 * li mama pi kasi ali.
	 */
	class KasiPiKasiSuli {
		public:
			/**
			 * @param nanpaLinja 		   kasi li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiKasiSuli(const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			/**
			 * @brief li pali e kasi sama kasi ni.
			 */
			virtual KasiPiKasiSuli* paliSama() const noexcept = 0;

			virtual ~KasiPiKasiSuli() = 0;

			/**
			 * @return nimi kasi pi kasi ni.
			 */
			virtual NimiKasi kamaJoENimiKasi() const;
			/**
			 * @return nimi pi nimi kasi tawa toki tawa jan.
			 */
			virtual const std::string& kamaJoENimiPiNimiKasi() const;
			/**
			 * @return lon pi kasi ni lon lipu wawa.
			 */
			const kepeken::LonIjoLonLipuLawa& kamaJoELonKasi() const;

		protected:
			kepeken::LonIjoLonLipuLawa lonKasiLonLipuWawa;
	};

	/**
	 * kasi ni li tawa ni: lipu wawa li pana e ijo lon poki nanpa.
	 */
	class KasiPiPanaLonPoki : public KasiPiKasiSuli {
		public:
			/**
			 * @param nimiPoki 			   ijo li pana lon poki pi nimi ni.
			 * @param ijoTawaPana 		   kasi ni li kama jo e ijo tawa poki.
			 * @param nanpaLinja 		   kasi li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiPanaLonPoki(const std::string& nimiPoki, const std::shared_ptr<KasiPiKasiSuli>& ijoTawaPana, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante) = delete;
			virtual KasiPiPanaLonPoki* paliSama() const noexcept override;

			virtual ~KasiPiPanaLonPoki() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			virtual const std::string& kamaJoENimiPiNimiKasi() const override;
			
			/**
			 * @return nimi pi poki nanpa pi kasi ni.
			 */
			const std::string& kamaJoENimiPoki() const;
			/**
			 * @return kasi tawa kama jo e ijo tawa poki.
			 */
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
			 * @param nimiPoki 			   ijo li kama tan poki pi nimi ni.
			 * @param nanpaLinja 		   kasi li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiKamaJoTanPoki(const std::string& nimiPoki, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiKamaJoTanPoki(const KasiPiKamaJoTanPoki& ante) = delete;
			virtual KasiPiKamaJoTanPoki* paliSama() const noexcept override;

			virtual ~KasiPiKamaJoTanPoki() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			virtual const std::string& kamaJoENimiPiNimiKasi() const override;

			/**
			 * @return nimi pi poki nanpa pi kasi ni.
			 */
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
			 * @param ijoTawaKama 		   lipu lawa li kepeken e kasi ni la ijo ni li pana tawa ona.
			 * @param nanpaLinja 		   kasi li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiKamaJoTanPokiPiAnteAla(const std::string& ijoTawaKama, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiKamaJoTanPokiPiAnteAla(const KasiPiKamaJoTanPokiPiAnteAla& ante) = delete;
			virtual KasiPiKamaJoTanPokiPiAnteAla* paliSama() const noexcept override;

			virtual ~KasiPiKamaJoTanPokiPiAnteAla() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			virtual const std::string& kamaJoENimiPiNimiKasi() const override;

			/** 
			 * @return nimi lon kasi ni.
			 */
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
			 * @param nimiWawa 				  ijo pana tawa nimi wawa tawa pali.
			 * @param kulupuPiIjoTawaNimiWawa kasi pi kulupu ni li kama jo e ijo tawa kepeken pi nimi wawa.
			 * @param nanpaLinja 			  kasi ni li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja 	  kasi ni li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiNimiWawa(nimi_wawa nimiWawa, const std::list<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaNimiWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiNimiWawa(const KasiPiNimiWawa& ante) = delete;
			virtual KasiPiNimiWawa* paliSama() const noexcept override;

			virtual ~KasiPiNimiWawa() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			virtual const std::string& kamaJoENimiPiNimiKasi() const override;

			/**
			 * @return nimi wawa poki lon kasi ni.
			 */
			nimi_wawa kamaJoENimiWawa() const;
			/**
			 * @return poki pi ijo pi kama jo e nimi tawa nimi wawa.
			 */
			const std::list<std::shared_ptr<KasiPiKasiSuli>>& kamaJoEKulupuPiIjoTawaNimiWawa() const;

		protected:
			nimi_wawa nimiWawa;
			std::list<std::shared_ptr<KasiPiKasiSuli>> kulupuPiIjoTawaNimiWawa;
	};

	/**
	 * kasi ni li tawa ni: nimi wawa tawa li ken kama lon ante.
	 */
	class KasiPiNimiTawa : public KasiPiKasiSuli {
		public:
			/**
			 * @param nimiPiNimiTawa 	   nimi pi nimi tawa. nimi wawa tawa li kepeken e nimi ni tawa tawa.
			 * @param nanpaLinja 		   kasi ni li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi ni li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiNimiTawa(const std::string& nimiPiNimiTawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiNimiTawa(const KasiPiNimiTawa& ante) = delete;
			virtual KasiPiNimiTawa* paliSama() const noexcept override;

			virtual ~KasiPiNimiTawa() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			virtual const std::string& kamaJoENimiPiNimiKasi() const override;

			/**
			 * @return nimi pi nimi tawa ni lon lipu.
			 */
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
			 * @attention sina wile pana e nanpa lon this->linjaTawaTawa.
			 * 
			 * @param nanpaLinja 		   kasi ni li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi ni li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiTawa(const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiTawa(const KasiTawa& ante) = delete;
			virtual KasiTawa* paliSama() const noexcept override;

			virtual ~KasiTawa() override;

			virtual NimiKasi kamaJoENimiKasi() const override;
			virtual const std::string& kamaJoENimiPiNimiKasi() const override;

			/**
			 * @return ijo tawa kama jo e nimi tawa kasi ni.
			 */
			const std::list<std::shared_ptr<KasiPiKasiSuli>>& kamaJoEIjoTawaTawa() const;
			/**
			 * @brief li pali e ijo kasi tawa li pilin e ni: li wile tawa ala tawa.
			 * 		tenpo ali la kasi kiwen KasiTawa li pana e nimi True.
			 * 
			 * @param nimiLipu 			nimi pi lipu wawa pi tenpo ni.
			 * @param nimiTawaTawa 		nimi tawa kasi tawa tan ijo tawa tawa. li sama ijo tawa nimi wawa.
			 * 
			 * @retval true 		li ken tawa.
			 * @retval false 		li ken ala tawa.
			 * @return std::string	ala.
			 * 
			 * @retval std::nullopt ike li kama.
			 */
			virtual std::optional<std::tuple<bool, std::string>> liKenTawa(const std::string& nimiLipu, const std::list<std::string>& nimiTawaTawa) const;
			/**
			 * @return nimi tawa kepeken e kasi tawa lon lipu pi toki Ilo Li Sina (sama "tawa" anu "niLaTawa").
			 */
			virtual std::string kamaJoENimiPiKasiTawa() const;

			/**
			 * kasi li tawa linja ni.
			 */
			size_t linjaTawaTawa;

		protected:
			std::list<std::shared_ptr<KasiPiKasiSuli>> ijoTawaTawa;
	};

	/**
	 * @brief kasi li ken tawa tan nimi jan.
	 * 
	 * ni li toki e nimi li toki e nimi lon e nimi pi lon ala.
	 * jan li toki e nimi lon la ni li tawa.
	 * ni ala la ni li tawa ala.
	 */
	class KasiPiTawaKen : public KasiTawa {
		public:
			/**
			 * @attention sina li wile pana e nanpa lon linjaTawaTawa. kasi li tawa linja ni.
			 *
			 * @param ijoTawa 			   kulupu kasi ni li kama jo e nimi lon e nimi pi lon ala e ijo tawa toki tawa jan.
			 * @param nanpaLinja 		   kasi ni li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi ni li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiTawaKen(const std::list<std::shared_ptr<KasiPiKasiSuli>>& ijoTawaTawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiTawaKen(const KasiPiTawaKen& ante) = delete;
			virtual KasiPiTawaKen* paliSama() const noexcept override;

			virtual ~KasiPiTawaKen() override;

			/**
			 * @brief li toki e nimi tawa toki tawa jan. jan li toki e nimi lon li ken tawa. 
			 * 		jan li toki e nimi ala la li ken ala.
			 * 
			 * @param nimiLipu 			 nimi pi lipu wawa pi tenpo ni.
			 * @param nimiTawaTawa[0] 	 nimi lon		 - nimi tawa tawa. 			li wile.
			 * @param nimiTawaTawa[1] 	 nimi pi lon ala - nimi tawa tawa ala. 		li wile.
			 * @param nimiTawaTawa[2...] ijo tawa toki	 - nimi tawa toki tawa jan. li wile ala.
			 * 
			 * @retval true 		jan li toki e nimi lon.
			 * @retval false 		jan li toki e nimi pi lon ala.
			 * @return std::string	nimi tan jan
			 * 
			 * @retval std::nullopt ike li kama.
			 */
			virtual std::optional<std::tuple<bool, std::string>> liKenTawa(const std::string& nimiLipu, const std::list<std::string>& nimiTawaTawa) const override;
			virtual std::string kamaJoENimiPiKasiTawa() const override;
	};

	/**
	 * @brief li kama jo e nimi. ona ale li ala la li tawa.
	 */
	class KasiPiAlaLaTawa : public KasiTawa {
		public:
			/**
			 * @attention sina li wile pana e nanpa lon linjaTawaTawa. kasi li tawa linja ni.
			 *
			 * @param ijoTawa 			   kulupu kasi ni li kama jo e nimi lon e nimi pi lon ala e ijo tawa toki tawa jan.
			 * @param nanpaLinja 		   kasi ni li kama tan nimi lon linja pi nanpa ni. li tawa toki e ike.
			 * @param nanpaSitelenLonLinja kasi ni li kama tan nimi tan sitelen pi nanpa ni lon linja. li tawa toki e ike.
			 */
			KasiPiAlaLaTawa(const std::list<std::shared_ptr<KasiPiKasiSuli>>& ijoTawaTawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja);

			KasiPiAlaLaTawa(const KasiPiAlaLaTawa& ante) = delete;
			virtual KasiPiAlaLaTawa* paliSama() const noexcept override;

			virtual ~KasiPiAlaLaTawa() override;

			/**
			 * @brief nimi pana ale li jo e ala la li tawa.
			 * 
			 * @param nimiLipu 			 nimi pi lipu wawa pi tenpo ni.
			 * @param nimiTawaTawa		 nimi tawa kama sona e ni: ona li jo ala jo e ala. 
			 * 
			 * @retval true 		nimi pana ale li jo e ala.
			 * @retval false 		nimi pana pi ale ala li jo e ala.
			 * @return std::string  ala.
			 */
			virtual std::optional<std::tuple<bool, std::string>> liKenTawa(const std::string& nimiLipu, const std::list<std::string>& nimiTawaTawa) const override;
			virtual std::string kamaJoENimiPiKasiTawa() const override;
	};
}
