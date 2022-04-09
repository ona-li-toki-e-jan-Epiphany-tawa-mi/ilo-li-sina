#include <functional>
#include "kipisi_pi_lipu_wawa/kipisi.hpp"
#include "lawa_pi_ilo_nanpa/lawa.hpp"
#include <tclap/CmdLine.h>

// TODO o pona e ike lon toki pona en toki ante.
// TODO o kepeken e poki List en ForwardList lon ni: ona li kepeken li lili e tenpo tawa lawa.
// TODO o pana e pali pi poki Vector lon nimi wawa.
// TODO o pana e nimi noexcept lon nimi wawa ken.
// TODO o pali e ni: toki ike li kepeken e argv[0] tawa toki e nimi pi lipu wawa ni.

/**
 * @brief li lawa e ilo nanpa kepeken lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa lawa.
 */
void lawaEIloNanpa(const std::string& nimiPiLipuWawa) {
	std::vector<std::shared_ptr<pali::KasiPiKasiSuli>> lipuWawa;

	{
		std::vector<kipisi::KulupuNimi> kulupuNimi;
		kipisi::kipisiELipuWawa(kulupuNimi, nimiPiLipuWawa);
		pali::paliELipuWawa(lipuWawa, kulupuNimi, nimiPiLipuWawa);
	}

	lawa::lawaEIloNanpa(lipuWawa, nimiPiLipuWawa);
}

/**
 * @brief li toki e kulupu nimi tan lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa toki.
 */
void tokiEKulupuNimi(const std::string& nimiPiLipuWawa) {
	std::vector<kipisi::KulupuNimi> kulupuNimi;
	kipisi::kipisiELipuWawa(kulupuNimi, nimiPiLipuWawa);
	kipisi::tokiELipuWawa(kulupuNimi, nimiPiLipuWawa);
}

/**
 * @brief li toki e kasi pi kasi suli tan lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa toki.
 */
void tokiEKasiSuli(const std::string& nimiPiLipuWawa) {
	std::vector<std::shared_ptr<pali::KasiPiKasiSuli>> lipuWawa;

	{
		std::vector<kipisi::KulupuNimi> kulupuNimi;
		kipisi::kipisiELipuWawa(kulupuNimi, nimiPiLipuWawa);
		pali::paliELipuWawa(lipuWawa, kulupuNimi, nimiPiLipuWawa);
	}

	pali::tokiEKasiSuli(lipuWawa, nimiPiLipuWawa);
}

const std::string sonaPiIloLiSina = 
		"An interpreter for ilo li sina, an unstructured procedural human-oriented possibly "
		"turing-complete string-based programming language for the aspiring homebody computer. ;)"
		
		"\n\n\b\b\b\bAUTHORS:"
		"\nona li toki e jan Epiphany tawa mi"

		"\n\n\b\b\b\bBUGS:"
		"\nReport bugs to <https://github.com/ona-li-toki-e-jan-Epiphany-tawa-mi/ilo-li-sina/issues>"
		
		"\n\n\b\b\b\bCOPYRIGHT:"
		"\nCopyright © 2022 Nathaniel Needham"
		"\nThis is free software; see the source or visit <https://mit-license.org> for the full "
		"license. THIS SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND."
		
		"\n\n\b\b\b\bSEE ALSO:"
		"\nSource code avalible at <https://github.com/ona-li-toki-e-jan-Epiphany-tawa-mi/ilo-li-sina>";

/**
 * An interpreter for ilo li sina, an unstructured procedural human-oriented possibly 
 * turing-complete string-based programming language for the aspiring homebody computer. ;)
 * 
 * @author ona li toki e jan Epiphany tawa mi.
 *
 * @see <https://github.com/ona-li-toki-e-jan-Epiphany-tawa-mi/ilo-li-sina> GitHub repository.
 */
int main(const int nanpaPiNimiPilin, const char *const *const nimiPilin) {
	try {
		TCLAP::CmdLine iloPiNimiPilin(sonaPiIloLiSina, '=', "0.0");

		TCLAP::SwitchArg oTokiEKulupuNimi("t", "toki-e-nimi", "Prints out the tokens generated from the given programs.", iloPiNimiPilin, false);
		TCLAP::SwitchArg oTokiEKasiSuli("a", "toki-e-kasi", "Prints out the abstract syntax trees generated from the given programs.", iloPiNimiPilin, false);
		TCLAP::UnlabeledMultiArg<std::string> nimiPiLipuWawa("LIPU_WAWA", "Program files to run.", true, "LIPU_WAWA", iloPiNimiPilin, true, static_cast<TCLAP::Visitor*>(nullptr));

		iloPiNimiPilin.parse(nanpaPiNimiPilin, nimiPilin);


		std::function<void(const std::string&)> paliWile = lawaEIloNanpa;

		if (oTokiEKulupuNimi.getValue()) {
			paliWile = tokiEKulupuNimi;

		} else if (oTokiEKasiSuli.getValue())
			paliWile = tokiEKasiSuli;
		
		for (const std::string& lipuWawa : nimiPiLipuWawa.getValue())
			paliWile(lipuWawa);

	} catch (const TCLAP::ArgException& ikePiNimiPilin) {
		kepeken::tokiEIke(ikePiNimiPilin.what());
	}

	return 0;
}
