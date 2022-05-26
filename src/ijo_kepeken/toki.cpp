#include "toki.hpp"
#include "../ante_toki/ante_toki.hpp"

namespace kepeken {
    void tokiELinjaPiLukinPona(std::ostream& lupaTawaToki, const std::string& nimi, const int nanpaPiSitelenAla, int nanpaPiSitelenAlaSin) {
        const std::string sitelenPiKipisiNimi(" \n");
        /**
         * @brief nanpa sitelen ken lon sitelen 1 tan tokiELinjaPiLukinPona().
         */
        constexpr size_t suliWilePiLinjaAli = 75;

        size_t suliWileLinja = suliWilePiLinjaAli - nanpaPiSitelenAla;
        std::string sitelenAlaLonMonsi(nanpaPiSitelenAla, ' ');
        size_t tan = 0, tawa = 0;

        while (true) {
            // linja awen li lili tawa suli wile la li ken pona toki e ona li ken pini.
            if (ante_toki::UTF8LaKamaJoENanpaSitelen(nimi, tan, nimi.size()) <= suliWileLinja) {
                lupaTawaToki << sitelenAlaLonMonsi << nimi.substr(tan) << '\n';
                return;
            }

            size_t suliPiLinjaLonLinja = 0;
            size_t maPiKenAla = tawa;
            // li kipisi e nimi kepeken sitelen kipisi tawa ni: ona li alasa e nanpa nimi ken lon linja 1.
            while (suliPiLinjaLonLinja <= suliWileLinja && maPiKenAla != std::string::npos) {
                tawa = maPiKenAla;
                maPiKenAla = nimi.find_first_of(sitelenPiKipisiNimi, tawa + 1);

                if (maPiKenAla != std::string::npos) 
                    suliPiLinjaLonLinja += ante_toki::UTF8LaKamaJoENanpaSitelen(nimi, tawa, maPiKenAla);
            }

            // li ken ala pana e nimi lon linja 1 la li ken kipisi e ona.
            if (tawa == tan) 
                tawa = tan + ante_toki::UTF8LaKamaJoENanpaBYTE(nimi, tan, suliWileLinja) - 1;

            lupaTawaToki << sitelenAlaLonMonsi << nimi.substr(tan, tawa - tan) << '\n';

            // li weka e nimi kipisi tan open linja.
            for (; sitelenPiKipisiNimi.find(nimi.at(tawa)) != std::string::npos; tawa++) {}
            tan = tawa;

            // li linja pi nanpa 1 ala la li en e sitelen sin pi lukin ala.
            if (nanpaPiSitelenAlaSin != 0) {
                sitelenAlaLonMonsi.append(nanpaPiSitelenAlaSin, ' ');
                suliWileLinja -= nanpaPiSitelenAlaSin;
                nanpaPiSitelenAlaSin = 0;
            }
        }
    }
}