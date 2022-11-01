#include "ante_toki.hpp"
#include <algorithm>
#include <iostream>
#include <clocale>
#include <cwchar>
#include <cassert>
#include "nimi_toki.hxx"

namespace ante_toki {
    const std::unordered_map<std::string, std::string>* tokiWile = nullptr;
    std::locale ijoPiTokiWile;
    const char* ijoCPiTokiWile = nullptr;

    bool alasaETokiWile() {
        if (nimiTokiAli.size() == 0)
            return false;

        // li wile tawa kama jo e suli pi poki nimi UTF-8 tawa ijo toki ante.
        ijoCPiTokiWile = setlocale(LC_ALL, "");

        // li ante e nasin pi toki ijo tawa toki wile.
        ijoPiTokiWile = std::locale("");
        std::cout.imbue(ijoPiTokiWile);
        std::cerr.imbue(ijoPiTokiWile);

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

    const std::string& nimiTawaJan(const std::string& nimiNimi) {
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



    size_t UTF8LaSuliSitelen(const std::string& pokiNimi, const size_t open, const size_t pini) {
        assert(open <= pokiNimi.size() && "open alasa lon poki nimi li ken ala suli tawa suli pi poki ni");

        size_t suliSitelen;
        if (pini != std::string::npos) {
            suliSitelen = mbrlen(
                &pokiNimi.at(open), 
                std::min(pini - open, MB_CUR_MAX), 
                nullptr);

        } else
            suliSitelen = mbrlen(
                &pokiNimi.at(open), 
                std::min(pokiNimi.size() - open, MB_CUR_MAX), 
                nullptr);

        // sitelen li jo e nanpa Byte mute li ike la li en taso e 1 tan ni: li ken ala pali ante tan sitelen ike.
        return suliSitelen > 0 && suliSitelen != static_cast<size_t>(-1) && suliSitelen != static_cast<size_t>(-2) ?
            suliSitelen : 1;
    }

    size_t UTF8LaNanpaSitelen(const std::string& pokiNimi, size_t open, const size_t pini) {
        assert(open <= pokiNimi.size() && pini <= pokiNimi.size() && "open alasa en pini alasa lon poki nimi li ken ala suli tawa suli pi poki ni");
        assert(open <= pini && "open alasa li ken ala suli tawa pini alasa");

        // li sona ala e ijo pi toki wile la li ken taso pana e suli tan open tawa pini.
        if (ijoCPiTokiWile == nullptr)
            return pini - open;

        size_t suli = 0;

        while (open < pini) {
            open += UTF8LaSuliSitelen(pokiNimi, open, pini);
            suli++;
        }

        return suli;
    }

    size_t UTF8LaNanpaBYTE(const std::string& pokiNimi, size_t open, size_t nanpaSitelen) {
        assert(open <= pokiNimi.size() && "open alasa lon poki nimi li ken ala suli tawa suli pi poki ni");
        
        if (ijoCPiTokiWile == nullptr)
            return std::min(pokiNimi.size() - open, nanpaSitelen);
        
        size_t nanpa = 0;

        for (; open < pokiNimi.size() && nanpaSitelen > 0; nanpaSitelen--) {
            size_t suliSitelen = mbrlen(
                &pokiNimi.at(open), 
                std::min(pokiNimi.size() - open, MB_CUR_MAX), 
                nullptr);
            
            suliSitelen = UTF8LaSuliSitelen(pokiNimi, open);

            open += suliSitelen;
            nanpa += suliSitelen;
        }

        return nanpa;
    }
}