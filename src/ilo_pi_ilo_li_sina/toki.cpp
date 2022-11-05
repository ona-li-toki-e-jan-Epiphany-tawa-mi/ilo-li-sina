#include "toki.hpp"

#include <cassert>

#include "../ante_toki/ante_toki.hpp"

namespace ilo {
    void tokiELipuKipisi(const std::list<Ijo>& ijoLipu, const std::string& lonLipu) {
		static const std::string sitelenAlaLonMonsi(8, ' ');
		const std::string sinpin(lonLipu.size() + 2, '-');

		std::cout << '/'  << sinpin  << "\\\n"
			      << "| " << lonLipu << " |\n" 
			      << '\\' << sinpin  << "/\n";
		
		if (!ijoLipu.empty()) {
			size_t nanpaLinja = 1;
			std::cout << ante_toki::anteENimi(
				ante_toki::nimiTawaJan("toki.nanpa_linja"),
				"%d", std::to_string(nanpaLinja))
				<< ":\n";

			for (auto alasaIjo = ijoLipu.cbegin(); alasaIjo != ijoLipu.cend(); alasaIjo++) {
				std::cout << sitelenAlaLonMonsi 
                          << ante_toki::nimiTawaJan(nimiIjoTawaNimiPiNimiIjo(alasaIjo->nimiIjo)) 
                          << "=\"";

				for (const char sitelen : alasaIjo->ijo)
					try {
						const char sitelenNasa = sitelenNasaTawaNimi().at(sitelen);
						std::cout << '\\' << sitelenNasa;

					} catch (const std::out_of_range& liSitelenNasaAla) {
						std::cout << sitelen;
					}

				std::cout << "\"\n";


                auto ijoLonMonsi = ijoLipu.cend();
                ijoLonMonsi--;

				if (alasaIjo->nimiIjo == NimiIjo::LINJA_SIN && alasaIjo != ijoLonMonsi)
					std::cout << ante_toki::anteENimi(
						ante_toki::nimiTawaJan("toki.nanpa_linja"),
						"%d", std::to_string(++nanpaLinja))
						<< ":\n";
			}

		} else
			std::cout << '\n' << ante_toki::nimiTawaJan("toki.li_jo_e_ala") << "\n\n";

		std::cout << "\\" << sinpin << "/\n";
	}



    /**
	 * @brief li toki e sitelen pi lukin ala lon open pi toki kasi.
	 * 
	 * @param lonInsaPiNanpaNi nanpa ni li nanpa sitelen tawa toki. kasi li lon insa pi kasi pi nanpa ni.
	 */
	void tokiEOpenPiTokiKasi(const unsigned int lonInsaPiNanpaNi) {
		static std::unordered_map<unsigned int, std::string> pokiPiTokiOpen;

		try {
			std::cout << pokiPiTokiOpen.at(lonInsaPiNanpaNi);
		
		} catch (const std::out_of_range liPokiAlaEOpenNi) {
			std::string openSin(lonInsaPiNanpaNi * 8, ' ');
			pokiPiTokiOpen[lonInsaPiNanpaNi] = openSin;
			std::cout << openSin;
		}
	}

	/**
	 * @brief li pana e kasi pi lipu wawa lon nimi li toki e ona lon ilo pi pana nimi.
	 *
	 * @param kasi 				 kasi pi kasi suli tawa pana.
	 * @param lonInsaPiNanpaNi	 kasi li lon insa pi kasi pi nanpa ni.
	 * @param nanpaPiKasiLonSewi kasi li kasi pi nanpa ni lon poki pi lipu wawa anu lon kasi ni.
	 */
	void tokiEKasiPiKasiSuli(const KasiLipu* kasi, const unsigned int lonInsaPiNanpaNi, const size_t nanpaPiKasiLonSewi) {
		tokiEOpenPiTokiKasi(lonInsaPiNanpaNi);

		auto kasiPiPanaLonPoki = dynamic_cast<const KasiPiPanaLonPoki*>(kasi);
        if (kasiPiPanaLonPoki != nullptr) {
            std::cout << ante_toki::nimiTawaJan(kasiPiPanaLonPoki->nimiPiNimiKasi()) << "=\"" 
                      << kasiPiPanaLonPoki->nimiPoki << "\":\n";
            tokiEKasiPiKasiSuli(kasiPiPanaLonPoki->ijoPana.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);

            return;
        }

		auto kasiPoki = dynamic_cast<const KasiPoki*>(kasi);
        if (kasiPoki != nullptr) {
			std::cout << ante_toki::nimiTawaJan(kasiPoki->nimiPiNimiKasi()) << "=\"" 
                      << kasiPoki->nimiPoki << "\"\n";

			return;
		}

		auto kasiPiPokiNimi = dynamic_cast<const KasiPiPokiNimi*>(kasi);
        if (kasiPiPokiNimi != nullptr) {
			std::cout << ante_toki::nimiTawaJan(kasiPiPokiNimi->nimiPiNimiKasi()) << "=\"";
			const std::unordered_map<char, char>& nimiTanSitelenNasa = sitelenNasaTawaNimi();
				
            for (const char sitelen : kasiPiPokiNimi->nimi)
                try {
                    const char sitelenPiNasaAla = nimiTanSitelenNasa.at(sitelen);
                    std::cout << '\\' << sitelenPiNasaAla;

                } catch (const std::out_of_range& liSitelenNasaAla) {
                    std::cout << sitelen;
                }

            std::cout << "\"\n";

			return;
		}

		auto kasiTomoPiNimiWawa = dynamic_cast<const KasiTomoPiNimiWawa*>(kasi);

        if (kasiTomoPiNimiWawa != nullptr) {
            try {
                std::cout << ante_toki::nimiTawaJan(kasiTomoPiNimiWawa->nimiPiNimiKasi()) << "=\"" 
                            << tomoPiNimiWawaTawaNimi(kasiTomoPiNimiWawa->tomoPiNimiWawa())
                            << '"';
                
            } catch (const std::out_of_range& nimiWawaLiLonAla) {
                assert(false && "pali la li kama jo e lon nullptr anu lon tawa nimi wawa pi sona ala");
            }

            if (kasiTomoPiNimiWawa->ijoPiNimiWawa.size() > 0) {
                std::cout << ":\n";

                for (const std::shared_ptr<KasiLipu>& ijo : kasiTomoPiNimiWawa->ijoPiNimiWawa)
                    tokiEKasiPiKasiSuli(ijo.get(), lonInsaPiNanpaNi + 1, nanpaPiKasiLonSewi);
            
            } else
                std::cout << '\n';


            auto kasiPiNimiWawaTawa = dynamic_cast<const KasiPiNimiWawaTawa*>(kasi);
            
            if (kasiPiNimiWawaTawa != nullptr) {
                tokiEOpenPiTokiKasi(lonInsaPiNanpaNi + 1);

                std::cout << ante_toki::anteENimi( ante_toki::nimiTawaJan("toki.nanpa_linja")
                                                 , "%d"
                                                 , std::to_string(kasiPiNimiWawaTawa->lonTawaTawa)) // TODO o toki e lina pi sona pona.
                          << '\n';
            }


            return;
        }

        auto kasiPini = dynamic_cast<const KasiPini*>(kasi);
        if (kasiPini != nullptr) {
            std::cout << ante_toki::nimiTawaJan(kasiPini->nimiPiNimiKasi()) << '\n';
            return;
        }

		// kasi li lon ala ijo lon sewi ni la mi ken pona toki e nimi ona.
		std::cout << ante_toki::nimiTawaJan(kasi->nimiPiNimiKasi()) << '\n';
	}

	void tokiELipuPali(const KasiOpen& kasiOpen, const std::string& lonLipu) {
		const std::string sinpin(lonLipu.size() + 2, '-');

		std::cout << '/'  << sinpin  << "\\\n"
			      << "| " << lonLipu << " |\n"
			      << '\\' << sinpin  << "/\n";

		if (!kasiOpen.kasiLonAnpa.empty()) {
			for (auto alasaKasi = kasiOpen.kasiLonAnpa.cbegin()
                    ; alasaKasi != kasiOpen.kasiLonAnpa.cend()
                    ; alasaKasi++) {
				const KasiLipu *const kasi = alasaKasi->get();

				std::cout << ante_toki::anteENimi( ante_toki::nimiTawaJan("toki.nanpa_linja")
                                                 , "%d", std::to_string(kasi->lonKasi.nanpaLinja)) 
					      << ":\n";
				tokiEKasiPiKasiSuli(kasi, 1, kasi->lonKasi.nanpaLinja);
			}

		} else
			std::cout << '\n' << ante_toki::nimiTawaJan("toki.li_jo_e_ala") << "\n\n";

		std::cout << '\\' << sinpin << "/\n";
	}
}