#include <functional>
#include <cassert>
#include "kipisi_pi_lipu_wawa/kipisi.hpp"
#include "lawa_pi_ilo_nanpa/lawa.hpp"
#include "ante_toki/ante_toki.hpp"
#include "pali_pi_lipu_wawa_tan_kulupu_nimi/nimi_wawa.hpp"
#include <tclap/CmdLine.h>

/**
 * @brief li sama kipisi::kipisiELipuWawa. taso, ni li ken pini e lipu wawa "ilo li sina".
 */
std::vector<kipisi::KulupuNimi> kipisiELipuWawaLKP(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	auto [lipuWawaKipisi, nanpaIke] = kipisi::kipisiELipuWawa(nimiPiLipuWawa, nimiPiILO_LI_SINA);

	if (!lipuWawaKipisi.has_value())
		exit(nanpaIke);

	return *lipuWawaKipisi;
}

/**
 * @brief li sama pali::paliELipuWawa. taso, ni li ken pini e lipu wawa "ilo li sina".
 */
std::vector<std::shared_ptr<pali::KasiPiKasiSuli>> paliELipuWawaLKP(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	auto [lipuWawaPali, nanpaIke] = pali::paliELipuWawa(
		kipisiELipuWawaLKP(nimiPiLipuWawa, nimiPiILO_LI_SINA),
		nimiPiLipuWawa, nimiPiILO_LI_SINA);

	if (!lipuWawaPali.has_value())
		exit(nanpaIke);

	return *lipuWawaPali;
}

/**
 * @brief li lawa e ilo nanpa kepeken lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa lawa.
 */
void lawaEIloNanpa(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	std::unordered_map<std::string, std::string> pokiNanpaOpen;

	// nimi ni li lon open pi lipu wawa ali.
	pokiNanpaOpen["__nanpa_Ilo_Li_Sina"] = "0.0";
	pokiNanpaOpen["__nimi_Ilo_Li_Sina"]  = nimiPiILO_LI_SINA;
	pokiNanpaOpen["__nimi_lipu"] 		 = nimiPiLipuWawa;
	pali::string_lqueue pokiOSPiNimiJan(std::list<std::string>({"USER", "USERNAME", "LOGNAME"})); 
	const std::optional<std::string> nimiJan = *pali::kamaJoEPokiNanpaPiLawaOS(
		nimiPiILO_LI_SINA, "", nullptr, pokiOSPiNimiJan);
	pokiNanpaOpen["__nimi_jan"] 		 = nimiJan.has_value() ? *nimiJan : "";
	pokiNanpaOpen["_"] 					 = "";

	int nanpaIke = lawa::lawaEIloNanpa(
		paliELipuWawaLKP(nimiPiLipuWawa, nimiPiILO_LI_SINA), 
		pokiNanpaOpen,
		nimiPiLipuWawa, nimiPiILO_LI_SINA);

	exit(nanpaIke);
}

/**
 * @brief li toki e kulupu nimi tan lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa toki.
 */
void tokiEKulupuNimi(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	kipisi::tokiELipuWawa(kipisiELipuWawaLKP(nimiPiLipuWawa, nimiPiILO_LI_SINA), nimiPiLipuWawa);
}

/**
 * @brief li toki e kasi pi kasi suli tan lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa toki.
 */
void tokiEKasiSuli(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	pali::tokiEKasiSuli(paliELipuWawaLKP(nimiPiLipuWawa, nimiPiILO_LI_SINA), nimiPiLipuWawa);
}



/******************************************************************************
 * Copyright (c) 2003-2012 Michael E. Smoot 
 * Copyright (c) 2004-2016 Daniel Aarno
 * Copyright (c) 2017-2021 Google LLC
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * ---------------
 * 
 * 	The given copyright notice applies only to the following function, void(fmtPrintLine)(std::ostream&, 
 * 		const std::string&, int, int, int), pulled from TCLAP (http://tclap.sourceforge.net/index.html) 
 * 		- MIT licensed. This message is not apart of the notice itself.
 *****************************************************************************/
void fmtPrintLine(std::ostream &os, const std::string &s, int maxWidth,
                         int indentTabs, int secondLineOffset) {
    const std::string splitChars(" ,|");
    int maxChars = maxWidth - indentTabs;
    std::string indentString(indentTabs, '\t');
    int from = 0;
    int to = 0;
    int end = s.length();
    for (;;) {
        if (end - from <= maxChars) {
            // Rest of string fits on line, just print the remainder
            os << indentString << s.substr(from) << std::endl;
            return;
        }

        // Find the next place where it is good to break the string
        // (to) by finding the place where it is too late (tooFar) and
        // taking the previous one.
        int tooFar = to;
        while (tooFar - from <= maxChars &&
               static_cast<std::size_t>(tooFar) != std::string::npos) {
            to = tooFar;
            tooFar = s.find_first_of(splitChars, to + 1);
        }

        if (to == from) {
            // In case there was no good place to break the string,
            // just break it in the middle of a word at line length.
            to = from + maxChars - 1;
        }

        if (s[to] != ' ') {
            // Include delimiter before line break, unless it's a space
            to++;
        }

        os << indentString << s.substr(from, to - from) << '\n';

        // Avoid printing extra white space at start of a line
        for (; s[to] == ' '; to++) {
        }
        from = to;

        if (secondLineOffset != 0) {
            // Adjust offset for following lines
            indentString.insert(indentString.end(), secondLineOffset, '\t');
            maxChars -= secondLineOffset;
            secondLineOffset = 0;
        }
    }
}

/**
 * @brief nimi pi ilo pilin ali. li tawa poki en kama jo.
 */
enum class NimiPiIloPilin {
	TOKI_E_NIMI,
	TOKI_E_KASI,
	HELP,
	VERSION
};

/**
 * @brief ilo pilin tawa lawa e lipu ni tan ilo CLI pi pana nimi (sama -h anu --toki-e-kasi).
 */
struct IloPilin {
	// nimi lili pi ilo pilin. li ken \0 tawa ala.
	char nimiLili = '\0'; 
	// nimi suli pi ilo pilin. li ken "" tawa ala.
	std::string nimiSuli;
	// nimi pi kama sona kepeken pi ilo pilin.
	std::string sonaKepeken;
	// jan li kepeken e ilo pilin ni.
	bool liLon = false;
};

/**
 * @brief ilo pilin ali pi lipu ni.
 * 
 * ni li lon tan ni: pana e ilo pilin sin li ken lon tenpo lili.
 */
std::unordered_map<NimiPiIloPilin, IloPilin> iloPilinAli = {
	{NimiPiIloPilin::TOKI_E_NIMI, {'n',  "toki-e-nimi", "ilo_CLI.ilo_pilin.toki_e_nimi", false}},
	{NimiPiIloPilin::TOKI_E_KASI, {'k',  "toki-e-kasi", "ilo_CLI.ilo_pilin.toki_e_kasi", false}},
	{NimiPiIloPilin::HELP,		  {'h',  "help", 		"ilo_CLI.ilo_pilin.help",		 false}},
	{NimiPiIloPilin::VERSION,     {'\0', "version", 	"ilo_CLI.ilo_pilin.version", 	 false}}
};

/**
 * @brief li toki e sona kepeken pi ilo ni tawa jan.
 */
void tokiESonaKepeken() {
	// nimi lipu.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.nimi_lipu") << ":\n"; 
	fmtPrintLine(std::cout, 
		"ilo_li_sina - " + ante_toki::kamaJoENimiTawaJan("ilo_CLI.nimi_lipu.nimi"),
		75, 1, 0);
	

	std::cout << '\n';


	// nasin kepeken.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.nasin_kepeken") << ":\n";
	std::string nimiPiNasinKepeken("ilo_li_sina ");

	if (!iloPilinAli.empty()) {
		nimiPiNasinKepeken.append("[-");
		for (const auto& [nimiPiIloPilin, iloPilin] : iloPilinAli) 
			if (iloPilin.nimiLili != '\0')
				nimiPiNasinKepeken.append(1, iloPilin.nimiLili);
		nimiPiNasinKepeken.append("] ");
	}

	fmtPrintLine(std::cout, 
		nimiPiNasinKepeken + ante_toki::kamaJoENimiTawaJan("ilo_CLI.ilo_pilin.lipu_wawa") + "...",
		75, 1, 1);


	std::cout << '\n';


	// sona.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.sona") << ":\n";
	fmtPrintLine(std::cout,
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.sona.nimi"),
		75, 1, 0);


	std::cout << '\n';


	// ilo pilin.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.ilo_pilin") << ":\n";

	if (!iloPilinAli.empty()) {
		for (const auto& [nimiPiIloPilin, iloPilin] : iloPilinAli) {
			std::string nimi;
			if (iloPilin.nimiLili != '\0')
				nimi.append(1, '-').append(1, iloPilin.nimiLili);
			if (iloPilin.nimiLili != '\0' && !iloPilin.nimiSuli.empty())
				nimi.append(", ");
			if (!iloPilin.nimiSuli.empty())
				nimi.append("--").append(iloPilin.nimiSuli);
			fmtPrintLine(std::cout,
				nimi,
				75, 1, 1);

			fmtPrintLine(std::cout,
				ante_toki::kamaJoENimiTawaJan(iloPilin.sonaKepeken),
				75, 2, 0);
			std::cout << '\n';
		}
	}

	fmtPrintLine(std::cout,
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.ilo_pilin.lipu_wawa"),
		75, 1, 1);
	fmtPrintLine(std::cout, 
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.ilo_pilin.lipu_wawa.sona"),
		75, 2, 0);

	
	std::cout << '\n';


	// jan pali.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.jan_pali") << ":\n";
	fmtPrintLine(std::cout, 
		"ona li toki e jan Epiphany tawa mi.",
		75, 1, 0);


	std::cout << '\n';


	// ike.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.ike") << ":\n";
	fmtPrintLine(std::cout, 
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.ike.ma_pi_toki_ike"),
		75, 1, 0);


	std::cout << '\n';


	// jo lipu.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.jo_lipu") << ":\n";
	fmtPrintLine(std::cout, 
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.jo_lipu.nimi"),
		75, 1, 0);


	std::cout << '\n';


	// ijo sin.
	std::cout << ante_toki::kamaJoENimiTawaJan("ilo_CLI.ijo_sin") << ":\n";
	fmtPrintLine(std::cout, 
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.ijo_sin.nimi_wawa"),
		75, 1, 0);
	fmtPrintLine(std::cout, 
		ante_toki::kamaJoENimiTawaJan("ilo_CLI.ijo_sin.nasin_kepeken"),
		75, 1, 0);
}

/**
 * @brief li toki e nanpa pi ilo ni tawa jan.
 */
void tokiENanpaPiIloNi() {
	std::cout << "ilo_li_sina 0.0\n";
}

/**
 * ilo tawa lawa e ilo nanpa kepeken toki "ilo li sina". toki "ilo li sina" li toki pi lawa e ilo 
 * nanpa li kepeken e nimi wawa GOTO li lawa e nimi wawa lon nasin pona li kepeken e jan tawa nanpa 
 * e nanpa li kepeken taso e poki pi sitelen nimi li tawa ilo nanpa pi wile pi pali ala en awen lon 
 * tomo. ;)
 * 
 * @author ona li toki e jan Epiphany tawa mi.
 *
 * @see <https://github.com/ona-li-toki-e-jan-Epiphany-tawa-mi/ilo-li-sina> poki pi lipu wawa ni lon
 * 		lipu KiApu.
 */
int main(const int nanpaPiNimiPilin, const char *const *const nimiPilin) {
	const std::vector<std::string> iloPilinPana(nimiPilin + 1, nimiPilin + nanpaPiNimiPilin);
	const std::string nimiPiILO_LI_SINA(nimiPilin[0]);

	// kama jo e toki wile li wile lon monsi pi toki e ijo.
	ante_toki::alasaETokiWile();


	assert([&]() {
		for (auto& [nimi, iloPilin] : iloPilinAli)
			if (iloPilin.nimiLili == '\0' && iloPilin.nimiSuli.empty())
				return false;
		return true;

 	}() && "ilo pilin la nimi lili en nimi suli li ken ala ala lon tenpo sama");

	std::list<const std::string*> lipuWawaPana;

	for (auto alasaIloPilin = iloPilinPana.cbegin(); alasaIloPilin != iloPilinPana.cend(); alasaIloPilin++)
		if (alasaIloPilin->size() > 2 && alasaIloPilin->compare(0, 2, "--") == 0) {
			bool liLon = false;

			for (auto& [nimi, iloPilin] : iloPilinAli)
				// nimi suli li ala la ona li lon ala.
				if (!iloPilin.nimiSuli.empty() && alasaIloPilin->compare(2, std::string::npos, iloPilin.nimiSuli) == 0) {
					iloPilin.liLon = true;
					liLon = true;
					break;
				}

			if (!liLon) {
				kepeken::tokiEIke(
					nimiPiILO_LI_SINA, 
					ante_toki::anteENimi(ante_toki::kamaJoENimiTawaJan(
						"ike.ilo_CLI.ilo_pilin.ilo_pi_sona_ala"),
						"%s", *alasaIloPilin));

				std::cout << ante_toki::kamaJoENimiTawaJan("ike.ilo_CLI.o_lukin_e_sona_kepeken") << '\n';

				return 1;
			}

		} else if (alasaIloPilin->size() > 1 && alasaIloPilin->at(0) == '-') {
			for (auto alasaNimiLili = alasaIloPilin->cbegin() + 1; alasaNimiLili != alasaIloPilin->cend(); alasaNimiLili++) {
				bool liLon = false;

				for (auto& [nimi, iloPilin] : iloPilinAli)
					// nimi lili li \0 la ona li lon ala.
					if (iloPilin.nimiLili != '\0' && *alasaNimiLili == iloPilin.nimiLili) { 
						iloPilin.liLon = true;
						liLon = true;

						break;
					}

				if (!liLon) {
					kepeken::tokiEIke(
					nimiPiILO_LI_SINA, 
					ante_toki::anteENimi(ante_toki::kamaJoENimiTawaJan(
						"ike.ilo_CLI.ilo_pilin.ilo_pi_sona_ala"),
						"%s", std::string("-") + *alasaNimiLili));

					std::cout << ante_toki::kamaJoENimiTawaJan("ike.ilo_CLI.o_lukin_e_sona_kepeken") << '\n';

					return 1;
				}
			}

		} else
			// nimi li ilo pilin ala la ona li nimi pi lipu wawa.
			lipuWawaPana.push_back(&(*alasaIloPilin));


	if (iloPilinAli[NimiPiIloPilin::HELP].liLon) {
		tokiESonaKepeken();
		return 0;

	} else if (iloPilinAli[NimiPiIloPilin::VERSION].liLon) {
		tokiENanpaPiIloNi();
		return 0;
	}


	if (lipuWawaPana.empty()) {
		kepeken::tokiEIke(
			nimiPiILO_LI_SINA, 
			ante_toki::kamaJoENimiTawaJan("ike.ilo_CLI.ilo_pilin.lipu_lawa_li_wile"));

		std::cout << ante_toki::kamaJoENimiTawaJan("ike.ilo_CLI.o_lukin_e_sona_kepeken") << '\n';

		return 1;
	}

	std::function<void(const std::string&, const std::string&)> paliWile = &lawaEIloNanpa;

	if (iloPilinAli[NimiPiIloPilin::TOKI_E_NIMI].liLon) {
		paliWile = &tokiEKulupuNimi;

	} else if (iloPilinAli[NimiPiIloPilin::TOKI_E_KASI].liLon)
		paliWile = &tokiEKasiSuli;
	
	for (const std::string *const lipuWawa : lipuWawaPana)
		paliWile(*lipuWawa, nimiPiILO_LI_SINA);

	return 0;
}
