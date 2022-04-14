#include "ante_toki.hpp"
#include "nimi_toki.hpp"

namespace ante_toki {
    // TODO o pali e ni: "ilo li sina" li ken kama jo e toki jan tan ilo lawa OS pi ilo nanpa ona.
    // li ken ala la o kepeken e toki pona.
    std::string tokiWile = "en_US";

    const std::string& kamaJoENimiTawaJan(const std::string& nimiNimi) {
        try {
            return nimiTokiAli.at(tokiWile).at(nimiNimi);

        } catch (const std::out_of_range& liSuliAla) {
            return nimiNimi;
        }
    }
}