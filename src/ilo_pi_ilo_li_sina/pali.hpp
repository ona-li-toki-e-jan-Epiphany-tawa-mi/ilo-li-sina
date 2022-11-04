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
			kepeken::LonIjo lonKasi;

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

	class KasiPiPokiNimi : public KasiLipu {
		public:
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

	class KasiPoki : public KasiLipu {
		public:
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

	class KasiPiNimiWawa : public KasiLipu {
		public:
			const NimiWawa* nimiWawa = nullptr;
			std::list<std::shared_ptr<KasiLipu>> ijoPiNimiWawa;

			KasiPiNimiWawa(const NimiWawa* nimiWawa);
			KasiPiNimiWawa& operator=(const KasiPiNimiWawa&) = delete;
			virtual KasiPiNimiWawa* paliSama() const override;
			KasiPiNimiWawa(KasiPiNimiWawa&& ante) noexcept;
			KasiPiNimiWawa& operator=(KasiPiNimiWawa&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiPiNimiWawa(const KasiPiNimiWawa& ante);
	};

	class KasiPiNimiWawaTawa : public KasiPiNimiWawa {
		public:
			std::shared_ptr<KasiLipu> kasiTawaTawa = nullptr;

			KasiPiNimiWawaTawa(const NimiWawa* nimiWawa);
			KasiPiNimiWawaTawa& operator=(const KasiPiNimiWawaTawa&) = delete;
			virtual KasiPiNimiWawaTawa* paliSama() const override;
			KasiPiNimiWawaTawa(KasiPiNimiWawaTawa&& ante) noexcept;
			KasiPiNimiWawaTawa& operator=(KasiPiNimiWawaTawa&& ante) noexcept;

			virtual std::string nimiPiNimiKasi() const override;

		private:
			KasiPiNimiWawaTawa(const KasiPiNimiWawaTawa& ante);
	};

	class KasiPiPanaLonPoki : public KasiLipu {
		public:
			std::string               nimiPoki;
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