#pragma once

#include <unordered_map>
#include <string>
#include <queue>
#include <list>
#include <optional>
#include "../ijo_kepeken/ike.hpp"

/**
 * ilo tawa pali e nimi wawa pi "ilo li sina".
 */
namespace pali {
	typedef std::queue<std::string, std::list<std::string>> string_lqueue;

	/**
	 * @brief nimi wawa pi toki "ilo li sina".
	 * 
	 * @param const std::string& 					  - nimi pi lipu wawa.
	 * @param const kepeken::LonIjoLonLipuLawa *const - lon kasi pi nimi wawa lon lipu wawa.
	 * @param string_lqueue& 	 					  - li jo e poki tawa nimi wawa tan ijo kepeken. nimi wawa li lawa la poki ni li moku li kama ala.
	 * 
	 * @return std::string poki sitelen tan lawa e nimi wawa.
	 */
	typedef std::optional<std::string>(*nimi_wawa)(const std::string&, const kepeken::LonIjoLonLipuLawa *const, string_lqueue&);


	/**
	 * @brief li kama jo e nimi lon poki nanpa pi nimi pana pi lawa OS.
	 * 
	 * li lukin e poki nanpa pana li kama jo e nimi tan poki nanpa pi nanpa 1 pi jo e nimi.
	 * sina pana e nimi mute tan ni: ken la ona li ante lon lawa OS ante. pana la nimi jan li ken lon
	 * 		"USER" anu "USERNAME" anu "LOGNAME" anu ante. taso, ken la "USER" en "LOGNAME" li jo e ala
	 * 		"USERNAME" li jo e nimi la nimi lon "USERNAME" li pana tawa sina.
	 * 
	 * @param nimiPiLipuWawa 	nimi pi lipu wawa.
	 * @param lonKasi			lon kasi pi nimi wawa lon lipu wawa.
	 * @param ijoTawaNi         nimi ken pi poki nanpa pi lawa OS.
	 * 
	 * @return    nimi lon poki nanpa pi nanpa 1 pi jo e nimi.
	 * @retval "" poki nanpa pana li jo e ala.
	 */
	std::optional<std::string> kamaJoEPokiNanpaPiLawaOS(const std::string& nimiPiLipuWawa, const kepeken::LonIjoLonLipuLawa *const lonKasi, pali::string_lqueue& ijoTawaNi);

	extern const std::unordered_map<std::string, nimi_wawa> pokiPiNimiWawaAli;


	/**
	 * @return poki pi nimi pi nimi wawa ali.
	 */
	const std::unordered_map<nimi_wawa, std::string>& kamaJoEPokiPiNimiPiNimiWawa();
}
