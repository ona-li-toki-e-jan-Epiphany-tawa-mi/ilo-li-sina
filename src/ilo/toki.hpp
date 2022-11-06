#include "pali/pali.hpp"

/**
 * ilo tawa toki e ijo pi nimi wawa tawa jan.
 */
namespace ilo {
    /**
	 * @brief li toki e ijo pi lipu wawa tawa jan pi lawa e ilo nanpa.
	 * 
	 * @param ijoLipu ijoLipu tan kipisi().
	 * @param lonLipu lon pi lipu wawa.
	 */
	void tokiELipuKipisi(const std::list<Ijo>& ijoLipu, const std::string& lonLipu);

    /**
	 * @brief li pana e lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasiOpen lipu wawa pali.
	 * @param lonLipu  lon pi lipu wawa.
	 */
	void tokiELipuPali(const KasiOpen& kasiOpen, const std::string& lonLipu);
}