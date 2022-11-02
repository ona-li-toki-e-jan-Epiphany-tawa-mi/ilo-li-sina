#pragma once

#include "kipisi.hpp"

#include <memory>

#include "nimi_wawa.hpp"

/**
 * ilo pali tawa pali e lipu wawa tan ijo lipu tan kipisi.
 */
namespace ilo {
    class KasiLipu {

    };

	class KasiOpen : public KasiLipu {
		public:
			std::list<std::shared_ptr<KasiLipu>> kasiLonAnpa;
	};

	class KasiPiNimiWawa : KasiLipu {
		public:
			NimiWawa& nimiWawa;
			std::list<std::shared_ptr<KasiLipu>> ijoPiNimiWawa;
	};

	class KasiPiPanaLonPoki : KasiLipu {
		public:
			std::string nimiPoki;
			KasiLipu    ijoPana;
	};

	/**
	 * @brief li pali e lipu wawa tan kulupu nimi tan kipisi pi lipu wawa jan.
	 *
	 * @param ijoKipisi ijo tan kipisi lipu. o sona e ni: ni li kama ante tan nimi wawa ni!
	 * @param lonLipu   lon pi lipu wawa.
	 * @return //TODO
	 */
	KasiLipu pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu);
}