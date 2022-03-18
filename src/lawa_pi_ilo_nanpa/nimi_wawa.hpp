#pragma once

#include <unordered_map>
#include <string>

/**
 * ilo tawa pali e nimi wawa pi "ilo li sina".
 */
namespace lawa {
	// poki pi nimi wawa ali.
	extern const std::unordered_map<std::string, std::string(*)(size_t, std::string[])> pokiPiNimiWawaAli;
}
