#pragma once

#include <unordered_map>
#include <stack>

#include "../../ijo_kepeken/ike.hpp"

//TODO
namespace ilo {
    //TODO
    struct SonaLawa {
        const std::string& lonLipu;

        std::unordered_map<std::string, std::string>& pokiAli;
        std::stack<std::string>                       pokiPali;
        size_t&                                       kasiPiTenpoNi;
        const kepeken::LonIjo*                        lonPiKasiPiTenpoNi;
    };
}