#pragma once

#include <memory>

#include "kipisi.hpp"
#include "nimi_wawa.hpp"
#include "../ijo_kepeken/ike.hpp"

/**
 * ilo pali tawa pali e lipu wawa tan ijo lipu tan kipisi.
 */
namespace ilo {
    class KasiLipu {
		public:
			kepeken::LonIjo lonKasi;

			virtual std::string nimiPiNimiKasi() const = 0;
	};

	class KasiOpen : public KasiLipu {
		public:
			std::list<std::shared_ptr<KasiLipu>> kasiLonAnpa;

			KasiOpen();

			virtual std::string nimiPiNimiKasi() const override;
	};

	class KasiPiPokiNimi : public KasiLipu {
		public:
			std::string nimi;

			virtual std::string nimiPiNimiKasi() const override;
	};

	class KasiPoki : public KasiLipu {
		public:
			std::string nimiPoki;

			virtual std::string nimiPiNimiKasi() const override;
	};

	class KasiPiNimiWawa : public KasiLipu {
		public:
			const NimiWawa* nimiWawa = nullptr;
			std::list<std::shared_ptr<KasiLipu>> ijoPiNimiWawa;

			virtual std::string nimiPiNimiKasi() const override;
	};

	class KasiPiPanaLonPoki : public KasiLipu {
		public:
			std::string               nimiPoki;
			std::shared_ptr<KasiLipu> ijoPana;

			virtual std::string nimiPiNimiKasi() const override;
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