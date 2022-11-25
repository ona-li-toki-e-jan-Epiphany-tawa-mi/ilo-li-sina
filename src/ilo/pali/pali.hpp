#pragma once

#include <memory>

#include "../kipisi.hpp"
#include "kasi.hpp"

/**
 * ilo pali tawa pali e lipu wawa tan ijo lipu tan kipisi.
 */
namespace ilo {
	/**
	 * @brief li pali e lipu wawa tan kulupu nimi tan kipisi pi lipu wawa jan.
	 *
	 * @param ijoKipisi ijo tan kipisi lipu. o sona e ni: ni li kama ante tan nimi wawa ni!
	 * @param lonLipu   lon pi lipu wawa.
	 * @return lipu wawa (lon tomo AST) tan ijo kipisi.
	 */
	KasiOpen pali(std::list<Ijo>& ijoKipisi, const std::string& lonLipu);
}