#pragma once

#include <unordered_map>
#include <stack>

#include "../../ijo_kepeken/ike.hpp"

/**
 * ijo pona tawa lawa.
 */
namespace ilo {
    /**
     * @brief ilo lawa la sona ni li wile lon mute. ni li pona e pana pi sona ni tawa ona.
     */
    struct SonaLawa {
        const std::string& lonLipu;

        std::unordered_map<std::string, std::string>& pokiAli;
        std::stack<std::string>&                      pokiPali;
        size_t&                                       kasiPiTenpoNi;
        const kepeken::LonIjo*                        lonPiKasiPiTenpoNi;
    };
}