#pragma once

#include <unordered_map>
#include <stack>

#include "../../kepeken/ike.hpp"

/**
 * ijo pona tawa lawa.
 */
namespace ilo {
    /**
     * @brief ilo lawa la sona ni li wile lon mute. ni li pona e pana pi sona ni tawa ona.
     */
    struct SonaLawa {
        // lon pi lipu wawa.
        const std::string& lonLipu;

        // nimi pi poki ali en poki pali.
        std::unordered_map<std::string, std::string>& pokiAli;
        // poki pali tawa pana e ijo tawa nimi wawa en pana lon poki.
        std::stack<std::string>&                      pokiPali;
        // kasi pi tenpo ni lon kasi open.
        size_t&                                       kasiPiTenpoNi;
        /**
         * @brief lon pi nimi wawa.
         * @attention nimi wawa anu nimi wawa tawa la o pana e ijo lon ni.
         */
        const kepeken::LonIjo*                        lonPiKasiPiTenpoNi;
    };
}