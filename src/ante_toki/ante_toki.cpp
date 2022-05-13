#include "ante_toki.hpp"
#include "nimi_toki.hpp"

namespace ante_toki {
    const std::unordered_map<std::string, std::string>* tokiWile = nullptr;

    bool alasaETokiWile() {
        if (nimiTokiAli.size() == 0)
            return false;


        // lawa OS mute li pana e toki wile lon "LANG". sin la ni li ken ni: jan li pilin e toki pi ilo ni.
        const char *const tokiJan = getenv("LANG");

        if (tokiJan != nullptr) {
            std::string nimiTokiPona = tokiJan;
            // li weka e ijo sama ".utf8". mi mute li wile e nimi toki taso.
            size_t lonPini = nimiTokiPona.find('.');
            if (lonPini != std::string::npos)
                nimiTokiPona.erase(lonPini);

            try {
                tokiWile = &nimiTokiAli.at(nimiTokiPona);
                return true;
            } catch (const std::out_of_range& tokiWileLiLonAla) {}
        }


        // li lukin kama jo e toki kepeken ala tan jan en lawa OS. ni li nasin pi nanpa pini.
        try {
            tokiWile = &nimiTokiAli.at("tok");

        } catch (const std::out_of_range& tokiPonaLiLonAla) {
            // toki wile en toki pona li lon ala la toki ante li lon la li wile kepeken e ona.
            // toki ala li ike.
            tokiWile = &nimiTokiAli.cbegin()->second;
        }


        return false;
    }

    const std::string& kamaJoENimiTawaJan(const std::string& nimiNimi) {
        try {
            if (tokiWile != nullptr)
                return tokiWile->at(nimiNimi);

        } catch (const std::out_of_range& nimiWileLiLonAla) {}

        return nimiNimi;
    }

    std::string anteENimi(std::string nimiTawaAnte, const std::string& nimiWeka, const std::string& nimiKama) {
        size_t lonNimi = nimiTawaAnte.find(nimiWeka);
        if (lonNimi == std::string::npos)
            return nimiTawaAnte;

        return nimiTawaAnte.replace(lonNimi, nimiWeka.size(), nimiKama);
    }
}