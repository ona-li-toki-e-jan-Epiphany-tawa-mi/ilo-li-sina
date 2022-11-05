#pragma once

#include <memory>

#include "kipisi.hpp"
#include "nimi_wawa.hpp"
#include "../ijo_kepeken/ike.hpp"

/**
 * ilo pali tawa pali e lipu wawa tan ijo lipu tan kipisi.
 */
namespace ilo {
	/**
	 * @brief li poki e lipu wawa lon kasi tawa lawa e ilo nanpa kepeken tenpo lili.
	 */
    class KasiLipu {
		public:
			/**
			 * @brief lon kasi lon lipu wawa.
			 */
			kepeken::LonIjo lonKasi = {static_cast<size_t>(-1), static_cast<size_t>(-1)};

			/**
			 * @return KasiLipu* kasi sin sama kasi ni.
			 * @attention o kepeken e ni e ilo Copy Constructor ala (taso, sina ken en wile kepeken e
			 * 		ona tawa pali e nimi wawa ni.)
			 */
			virtual KasiLipu* paliSama() const = 0;

			/**
			 * @return nimi kasi tawa toki tawa jan kepeken ante_toki::nimiTawaJan().
			 */
			virtual std::string nimiPiNimiKasi() const = 0;
	};

	/**
	 * @brief li kasi pi nanpa 1 lon kasi pi lipu wawa.
	 */
	class KasiOpen : public KasiLipu {
		public:
			/**
			 * @brief kasi lon ni li open pi linja ali lon lipu wawa.
			 */
			std::list<std::shared_ptr<KasiLipu>> kasiLonAnpa;

			KasiOpen();
			KasiOpen& operator=(const KasiOpen&) = delete;
			virtual KasiOpen* paliSama() const override;
			KasiOpen(KasiOpen&& ante) noexcept;
			KasiOpen& operator=(KasiOpen&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiOpen(const KasiOpen& ante);
	};

	/**
	 * @brief tenpo ali la li lon pini 
	 */
	class KasiPini : public KasiLipu {
		public:
			KasiPini() = default;
			KasiPini& operator=(const KasiPini&)          = delete;
			virtual KasiPini* paliSama() const override;
			KasiPini(KasiPini&& ante) noexcept            = default;
			KasiPini& operator=(KasiPini&& ante) noexcept = default;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiPini(const KasiPini& ante) = default;
	};

	/**
	 * @brief li kama jo e nimi tan poki nimi.
	 */
	class KasiPiPokiNimi : public KasiLipu {
		public:
			/**
			 * @brief nimi lon poki nimi.
			 */
			std::string nimi;

			KasiPiPokiNimi() = default;
			KasiPiPokiNimi& operator=(const KasiPiPokiNimi&) = delete;
			virtual KasiPiPokiNimi* paliSama() const override;
			KasiPiPokiNimi(KasiPiPokiNimi&& ante) noexcept;
			KasiPiPokiNimi& operator=(KasiPiPokiNimi&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiPiPokiNimi(const KasiPiPokiNimi& ante) = default;
	};

	/**
	 * @brief li kama jo e nimi tan poki.
	 */
	class KasiPoki : public KasiLipu {
		public:
			/**
			 * @brief nimi pi poki ni.
			 */
			std::string nimiPoki;

			KasiPoki() = default;
			KasiPoki& operator=(const KasiPoki&) = delete;
			virtual KasiPoki* paliSama() const override;
			KasiPoki(KasiPoki&& ante) noexcept;
			KasiPoki& operator=(KasiPoki&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiPoki(const KasiPoki& kasiPoki) = default;
	};

	/**
	 * @brief li tomo pi kasi pi nimi wawa en nimi wawa tawa.
	 */
	class KasiTomoPiNimiWawa : public KasiLipu {
		public:
			/**
			 * @brief ni li ijo tawa nimi wawa. tenpo 1 la ona li lawa. tenpo 2 la ijo tan lawa ona li
			 * 		pana tawa nimi wawa.
			 */
			std::list<std::shared_ptr<KasiLipu>> ijoPiNimiWawa;

			KasiTomoPiNimiWawa() = default;
			KasiTomoPiNimiWawa& operator=(const KasiTomoPiNimiWawa&) = delete;
			KasiTomoPiNimiWawa(KasiTomoPiNimiWawa&& ante) noexcept;
			KasiTomoPiNimiWawa& operator=(KasiTomoPiNimiWawa&& ante) noexcept;

			virtual const TomoPiNimiWawa* tomoPiNimiWawa() const = 0;

		private:
			KasiTomoPiNimiWawa(const KasiTomoPiNimiWawa& ante);
	};

	/**
	 * @brief li kepeken pi nimi wawa.
	 */
	class KasiPiNimiWawa : public KasiTomoPiNimiWawa {
		public:
			const NimiWawa* nimiWawa = nullptr;

			KasiPiNimiWawa() = default;
			KasiPiNimiWawa(const NimiWawa* nimiWawa);
			KasiPiNimiWawa& operator=(const KasiPiNimiWawa&) = delete;
			virtual KasiPiNimiWawa* paliSama() const override;
			KasiPiNimiWawa(KasiPiNimiWawa&& ante) noexcept;
			KasiPiNimiWawa& operator=(KasiPiNimiWawa&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;
			virtual const TomoPiNimiWawa* tomoPiNimiWawa() const override;

		private:
			KasiPiNimiWawa(const KasiPiNimiWawa& ante);
	};

	/**
	 * @brief li kepeken pi nimi wawa tawa.
	 */
	class KasiPiNimiWawaTawa : public KasiTomoPiNimiWawa {
		public:
			const NimiWawaTawa* nimiWawaTawa = nullptr;
			/**
			 * @brief nimi wawa tawa li wile tawa la li tawa lon kasi pi nanpa ni lon kasi open.
			 */
			size_t lonTawaTawa               = static_cast<size_t>(-1);

			KasiPiNimiWawaTawa() = default;
			KasiPiNimiWawaTawa(const NimiWawaTawa* nimiWawaTawa);
			KasiPiNimiWawaTawa& operator=(const KasiPiNimiWawaTawa&) = delete;
			virtual KasiPiNimiWawaTawa* paliSama() const override;
			KasiPiNimiWawaTawa(KasiPiNimiWawaTawa&& ante) noexcept;
			KasiPiNimiWawaTawa& operator=(KasiPiNimiWawaTawa&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;
			virtual const TomoPiNimiWawa* tomoPiNimiWawa() const override;

		private:
			KasiPiNimiWawaTawa(const KasiPiNimiWawaTawa& ante);
	};

	/**
	 * @brief li pana e ijo lon poki pi nimi pana.
	 */
	class KasiPiPanaLonPoki : public KasiLipu {
		public:
			/**
			 * @brief nimi poki tawa poki e ijo.
			 */
			std::string               nimiPoki;
			/**
			 * @brief tenpo 1 la ni li lawa. tenpo 2 la li pana e ijo kama lon poki.
			 */
			std::shared_ptr<KasiLipu> ijoPana;

			KasiPiPanaLonPoki() = default;
			KasiPiPanaLonPoki& operator=(const KasiPiPanaLonPoki&) = delete;
			virtual KasiPiPanaLonPoki* paliSama() const override;
			KasiPiPanaLonPoki(KasiPiPanaLonPoki&& ante) noexcept;
			KasiPiPanaLonPoki& operator=(KasiPiPanaLonPoki&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante);
	};

	/**
	 * @brief li pali e lipu wawa tan kulupu nimi tan kipisi pi lipu wawa jan.
	 *
	 * @param ijoKipisi ijo tan kipisi lipu. o sona e ni: ni li kama ante tan nimi wawa ni!
	 * @param lonLipu   lon pi lipu wawa.
	 * @return lipu wawa (lon tomo AST) tan ijo kipisi.
	 */
	KasiOpen pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu);



	/**
	 * @brief li pana e lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasiOpen lipu wawa pali.
	 * @param lonLipu  lon pi lipu wawa.
	 */
	void tokiELipuPali(const KasiOpen& kasiOpen, const std::string& lonLipu);
}