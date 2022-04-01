#pragma once

#include <unordered_map>
#include <string>
#include <optional>

/**
 * ilo tawa pali e nimi wawa pi "ilo li sina".
 */
namespace pali {
	/**
	 * @brief nimi wawa pi toki "ilo li sina"
	 * 
	 * nanpa size_t li suli pi poki sitelen string[].
	 * poki string[] li jo e poki tawa nimi wawa tan ijo kepeken.
	 */
	typedef std::string(*nimi_wawa)(const size_t, const std::string[]);

	// poki pi nimi wawa ali.
	extern const std::unordered_map<std::string, nimi_wawa> pokiPiNimiWawaAli;

	/**
	 * @brief li kama jo e nimi pi nimi wawa tan ijo pana tawa ona.
	 * 
	 * @param nimiWawa ijo pana tawa nimi wawa.
	 * 
	 * @return nimi pi nimi wawa.
	 */
	std::optional<std::string> kamaJoENimiTanNimiWawa(const nimi_wawa nimiWawa);
}
