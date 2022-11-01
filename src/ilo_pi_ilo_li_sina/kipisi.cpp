#include "kipisi.hpp"

#include <regex>
#include <iostream>
#include <fstream>

#include "../ijo_kepeken/ike.hpp"
#include "../ante_toki/ante_toki.hpp"

//TODO #define KAMA_JO_E_NANPA_SITELEN(linjaSitelen, alasaSitelen) static_cast<size_t>(std::distance(linjaSitelen.begin(), alasaSitelen)) + 1

namespace ilo {
    Ijo::Ijo(NimiIjo nimiIjo)
        : Ijo::Ijo(nimiIjo, "") {}

    Ijo::Ijo(NimiIjo&& nimiIjo, std::string&& ijo) {
        this->nimiIjo = nimiIjo;
        this->ijo.swap(ijo);
    }

    Ijo::Ijo(NimiIjo nimiIjo, const std::string& ijo) {
        this->nimiIjo = nimiIjo;
        this->ijo = ijo;
    }



    const std::regex SITELEN_PI_POKI_NANPA("[a-zA-Z0-9_]", std::regex_constants::optimize);
	const std::regex SITELEN_PI_LUKIN_ALA ("\\s",          std::regex_constants::optimize);
	const std::unordered_map<char, char> sitelenNasaTanNimi = {
		{'n', '\n'}, {'t', '\t'}, {'b', '\b'}, {'v', '\v'}, {'"', '"'}, {'\\', '\\'}};

    struct SonaKipisi {
        const std::string& lonLipu;

        std::list<Ijo>& pokiIjo;
        std::string& linja;
        std::string::const_iterator& alasaSitelen;
    };

    bool paliENimiTawaTawa(SonaKipisi& sonaKipisi) {
        bool liPaliELonTawaTawa = false;

        if (sonaKipisi.pokiIjo.size() >= 1) {
            auto ijoLonMonsi = sonaKipisi.pokiIjo.end();
            ijoLonMonsi--;

            if (ijoLonMonsi->nimiIjo == NimiIjo::POKI) {
                ijoLonMonsi->nimiIjo = NimiIjo::NIMI_TAWA_TAWA;
                liPaliELonTawaTawa = true;
            }
        }


        if (!liPaliELonTawaTawa) {
            kepeken::tokiEIke({ sonaKipisi.lonLipu
                              , ante_toki::kamaJoENimiTawaJan("ike.kipisi.nimi_tawa.nimi_li_wile")});
            return false;
        }

        if (sonaKipisi.pokiIjo.size() >= 2) { 
            auto ijoLonMonsi = sonaKipisi.pokiIjo.cend();
            for (int i = 0; i < 2; i++) ijoLonMonsi--;

            if (ijoLonMonsi->nimiIjo != NimiIjo::LINJA_SIN) {
                kepeken::tokiEIke({ sonaKipisi.lonLipu
                                  , ante_toki::kamaJoENimiTawaJan("ike.kipisi.nimi_tawa.li_ken_lon_open_linja_taso")});
                return false;
            }
        }


        return true;
    }

    bool paliEPokiNimi(SonaKipisi& sonaKipisi) {
        std::string pokiNimi;
        bool liJoEPini = false;
        const auto openPoki = sonaKipisi.alasaSitelen;

        sonaKipisi.alasaSitelen++;
        for (; sonaKipisi.alasaSitelen < sonaKipisi.linja.cend(); sonaKipisi.alasaSitelen++) {
            switch (*sonaKipisi.alasaSitelen) {
                // pini pi poki nimi.
                case '"':
                    sonaKipisi.alasaSitelen++;
                    liJoEPini = true;
                    goto liPiniPiPokiSitelen;

                // nimi pi sitelen nasa (sama \n anu \v).
                case '\\':
                    sonaKipisi.alasaSitelen++;
                    if (sonaKipisi.alasaSitelen == sonaKipisi.linja.cend())
                        goto liPiniPiPokiSitelen;

                    try {
                        pokiNimi.push_back(sitelenNasaTanNimi.at(*sonaKipisi.alasaSitelen));
                    
                    } catch (const std::out_of_range& liSitelenAlaTawaSitelenNasa) {	
                        kepeken::tokiEIke({ sonaKipisi.lonLipu
                                          , ante_toki::anteENimi( ante_toki::kamaJoENimiTawaJan("ike.kipisi.poki_nimi.nimi_pi_sitelen_nasa_pi_sona_ala")
                                                                  , "%s", std::string(1, *sonaKipisi.alasaSitelen))});
                        return false;
                    }

                    continue;

                default:
                    pokiNimi.push_back(*sonaKipisi.alasaSitelen);
            }
        }
    liPiniPiPokiSitelen:
        sonaKipisi.alasaSitelen--;

        if (!liJoEPini) {
            kepeken::tokiEIke({ sonaKipisi.lonLipu
                                , ante_toki::kamaJoENimiTawaJan("ike.kipisi.poki_nimi.li_jo_ala_e_pini")});
            return false;
        }

        sonaKipisi.pokiIjo.emplace_back(NimiIjo::POKI_NIMI, std::move(pokiNimi));
        return true;
    }

    bool paliEPokiPiIjoPiNimiWawa(SonaKipisi& sonaKipisi) {
        sonaKipisi.pokiIjo.emplace_back( NimiIjo::POKI_PI_IJO_PI_NIMI_WAWA
                                       , std::string(1, *sonaKipisi.alasaSitelen));

        if (*sonaKipisi.alasaSitelen == '(') {
            bool liPaliENimiWawa = false;

            if (sonaKipisi.pokiIjo.size() > 1) {
                auto ijoLonMonsi = sonaKipisi.pokiIjo.end();
                for (int i = 0; i < 2; i++) ijoLonMonsi--;

                if (ijoLonMonsi->nimiIjo == NimiIjo::POKI) {
                    ijoLonMonsi->nimiIjo = NimiIjo::NIMI_WAWA;
                    liPaliENimiWawa = true;
                }
            }

            if (!liPaliENimiWawa) {
                kepeken::tokiEIke({ sonaKipisi.lonLipu
                                  , ante_toki::kamaJoENimiTawaJan("ike.kipisi.nimi_wawa.nimi_li_wile")});
                return false;
            }
        }

        return true;
    }

    void paliEPoki(SonaKipisi& sonaKipisi) {
        std::string nimiPiPokiNanpa(1, *sonaKipisi.alasaSitelen);
        const auto openPiPokiNanpa = sonaKipisi.alasaSitelen;

        sonaKipisi.alasaSitelen++;
        for (; sonaKipisi.alasaSitelen < sonaKipisi.linja.cend(); sonaKipisi.alasaSitelen++) {
            if ((*sonaKipisi.alasaSitelen & 0b10000000) == 0
                    && !std::regex_match( sonaKipisi.alasaSitelen
                                        , sonaKipisi.alasaSitelen + 1
                                        , SITELEN_PI_POKI_NANPA))
                break;

            nimiPiPokiNanpa.push_back(*sonaKipisi.alasaSitelen);
        }
        sonaKipisi.alasaSitelen--;

        sonaKipisi.pokiIjo.emplace_back(NimiIjo::POKI, std::move(nimiPiPokiNanpa));
    }

	std::list<Ijo> kipisi(const std::string& lonLipu) {
		std::list<Ijo> pokiIjo;


		std::ifstream lipu(lonLipu);

		if (!lipu.is_open()) {
			kepeken::tokiEIke({ 
				ante_toki::anteENimi(
					ante_toki::kamaJoENimiTawaJan("ike.kipisi.li_ken_ala_open_e_lipu"),
					"%s", lonLipu)});
            return {}; // TODO o "throw" e ike.
		}


		std::string linja;
		size_t nanpaLinja = 1;
        auto alasaSitelen = linja.cbegin();
        SonaKipisi sonaKipisi = {lonLipu, pokiIjo, linja, alasaSitelen};
        bool liLipuPona = true;

		// ona li lon la li weka e sitelen BOM.
		std::getline(lipu, linja);
		if (linja.compare(0, 3, "\xEF\xBB\xBF") == 0)
			linja.erase(0, 3);
    
		do {
			if (linja.size() != 0) 
				for (alasaSitelen = linja.cbegin(); alasaSitelen < linja.cend(); alasaSitelen++) {
                    sonaKipisi.alasaSitelen = alasaSitelen;

					switch (*alasaSitelen) {
						case '=': {
							pokiIjo.emplace_back(NimiIjo::PANA_LON_POKI);
							break;
						}

						case ':': {
                            liLipuPona = liLipuPona && paliENimiTawaTawa(sonaKipisi);
							break;
						}

						case '"': {
                            liLipuPona = liLipuPona && paliEPokiNimi(sonaKipisi);
							break;
						}

						// li ken e ni: jan li sitelen e nimi sona tawa toki e sona.
						case '#':
							goto liNimiSona;

						// li ken e ni: jan li sitelen e ijo wan lon linja mute.
						case '\\':
							goto linjaSinLiWileAla;

						case '(':
						case ')': {
							liLipuPona = liLipuPona && paliEPokiPiIjoPiNimiWawa(sonaKipisi);
							break;
						}

						default:
							// sitelen li lon ala kulupu ASCII la ona li ken lon nimi poki. '& 0b1000_0000' li alasa e ona.
							if ((*alasaSitelen & 0b10000000) != 0
									|| std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_POKI_NANPA)) {
								paliEPoki(sonaKipisi);
								break;
							}

							// li weka e sitelen pi lukin ala.
							if (std::regex_match(alasaSitelen, alasaSitelen+1, SITELEN_PI_LUKIN_ALA))
								break;



							// TODO li toki e sitelen ike. TODO
                            /*
							size_t lonSitelen = KAMA_JO_E_NANPA_SITELEN(linja, alasaSitelen);
							size_t suliSitelen = ante_toki::UTF8LaKamaJoESuliSitelen(linja, lonSitelen - 1);

							alasaSitelen += suliSitelen;

							kepeken::tokiEIke({
								nimiPiLipuWawa, 
								nanpaLinja, lonSitelen, 
								ante_toki::anteENimi(
									ante_toki::kamaJoENimiTawaJan("ike.kulupu_nimi_pi_wile_ala"),
									"%s", linja.substr(lonSitelen - 1, suliSitelen))});
							liLipuPiPonaAla = true;*/
					}
				}
		liNimiSona:

            // linja sin mute lon poka ona li wile ala. 1 taso li wile.
            if (pokiIjo.back().nimiIjo != NimiIjo::LINJA_SIN)
			    pokiIjo.emplace_back(NimiIjo::LINJA_SIN);
		linjaSinLiWileAla:
			nanpaLinja++;

		} while (std::getline(lipu, linja));

        if (!liLipuPona)
            throw std::runtime_error("lipu wawa ike!");

        // tenpo ali la linja li wile jo e LINJA_SIN lon pini. ken la linja pini lon pokiIjo li jo ala 
        //      e ni. ni li pona e ni.
		if (!pokiIjo.empty() && pokiIjo.back().nimiIjo != NimiIjo::LINJA_SIN)
			pokiIjo.emplace_back(NimiIjo::LINJA_SIN);


		return pokiIjo;
	}
}