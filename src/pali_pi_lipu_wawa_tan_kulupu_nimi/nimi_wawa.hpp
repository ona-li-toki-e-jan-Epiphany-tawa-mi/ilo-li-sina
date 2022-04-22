#pragma once

#include <unordered_map>
#include <string>
#include <queue>
#include <list>
#include <optional>

/**
 * ilo tawa pali e nimi wawa pi "ilo li sina".
 */
namespace pali {
	typedef std::queue<std::string, std::list<std::string>> string_lqueue;

	/**
	 * @brief nimi wawa pi toki "ilo li sina".
	 * 
	 * @param const std::string& - nimi pi lipu "ilo li sina".
	 * @param string_lqueue& - li jo e poki tawa nimi wawa tan ijo kepeken. nimi wawa li lawa la poki ni li moku li kama ala.
	 * 
	 * @return std::string poki sitelen tan lawa e nimi wawa.
	 */
	typedef std::optional<std::string>(*nimi_wawa)(const std::string&, string_lqueue&);

	extern const std::unordered_map<std::string, nimi_wawa> pokiPiNimiWawaAli;

	/**
	 * @return poki pi nimi pi nimi wawa ali.
	 */
	const std::unordered_map<nimi_wawa, std::string>& kamaJoEPokiPiNimiPiNimiWawa();
}
