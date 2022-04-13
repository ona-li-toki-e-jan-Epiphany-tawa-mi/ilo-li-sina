#include <functional>
#include "kipisi_pi_lipu_wawa/kipisi.hpp"
#include "lawa_pi_ilo_nanpa/lawa.hpp"
#include <tclap/CmdLine.h>

// TODO o pona e toki ike lon toki pona en toki ante.
// TODO o pali e ni: nimi wawa throw() ali li kepeken e toki pona.
// TODO o pali e ni: nimi wawa pi pali e lipu wawa li kepeken ala e nimi exit() li kepeken e optional<> tawa lipu ike.

/**
 * @brief li lawa e ilo nanpa kepeken lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa lawa.
 */
void lawaEIloNanpa(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	std::vector<std::shared_ptr<pali::KasiPiKasiSuli>> lipuWawa = pali::paliELipuWawa(
		kipisi::kipisiELipuWawa(nimiPiLipuWawa, nimiPiILO_LI_SINA), 
		nimiPiLipuWawa, nimiPiILO_LI_SINA);
	lawa::lawaEIloNanpa(lipuWawa, nimiPiLipuWawa, nimiPiILO_LI_SINA);
}

/**
 * @brief li toki e kulupu nimi tan lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa toki.
 */
void tokiEKulupuNimi(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	kipisi::tokiELipuWawa(
		kipisi::kipisiELipuWawa(nimiPiLipuWawa, nimiPiILO_LI_SINA), 
		nimiPiLipuWawa);
}

/**
 * @brief li toki e kasi pi kasi suli tan lipu wawa pana.
 * 
 * @param nimiPiLipuWawa nimi pi lipu wawa tawa toki.
 */
void tokiEKasiSuli(const std::string& nimiPiLipuWawa, const std::string& nimiPiILO_LI_SINA) {
	std::vector<std::shared_ptr<pali::KasiPiKasiSuli>> lipuWawa = pali::paliELipuWawa(
		kipisi::kipisiELipuWawa(nimiPiLipuWawa, nimiPiILO_LI_SINA), 
		nimiPiLipuWawa, nimiPiILO_LI_SINA);
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
		"terms of the license. THIS SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND."
		
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
	std::string nimiPiILO_LI_SINA(nimiPilin[0]);

	try {
		TCLAP::CmdLine iloPiNimiPilin(sonaPiIloLiSina, '=', "0.0");

		TCLAP::SwitchArg oTokiEKulupuNimi("t", "toki-e-nimi", "Prints out the tokens generated from the given programs.", iloPiNimiPilin, false);
		TCLAP::SwitchArg oTokiEKasiSuli("a", "toki-e-kasi", "Prints out the abstract syntax trees generated from the given programs.", iloPiNimiPilin, false);
		TCLAP::UnlabeledMultiArg<std::string> nimiPiLipuWawa("LIPU_WAWA", "Program files to run.", true, "LIPU_WAWA", iloPiNimiPilin, true, static_cast<TCLAP::Visitor*>(nullptr));

		iloPiNimiPilin.parse(nanpaPiNimiPilin, nimiPilin);


		std::function<void(const std::string&, const std::string&)> paliWile = lawaEIloNanpa;

		if (oTokiEKulupuNimi.getValue()) {
			paliWile = tokiEKulupuNimi;

		} else if (oTokiEKasiSuli.getValue())
			paliWile = tokiEKasiSuli;
		
		for (const std::string& lipuWawa : nimiPiLipuWawa.getValue())
			paliWile(lipuWawa, nimiPiILO_LI_SINA);

	} catch (const TCLAP::ArgException& ikePiNimiPilin) {
		kepeken::tokiEIke(nimiPiILO_LI_SINA, ikePiNimiPilin.what());
	}

	return 0;
}
