#pragma once

#include "../pali/pali.hpp"

namespace ilo {
    void lawaELipu(const KasiOpen& lipuWawa, const std::string& lonLipu);

    void lawaELipu(const KasiOpen& lipuWawa
             , std::unordered_map<std::string, std::string>& pokiAli
             , const std::string& lonLipu);
}