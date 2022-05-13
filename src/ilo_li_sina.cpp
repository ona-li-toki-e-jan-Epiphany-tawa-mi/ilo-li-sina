#include <functional>
#include "kipisi_pi_lipu_wawa/kipisi.hpp"
#include "lawa_pi_ilo_nanpa/lawa.hpp"
#include "ante_toki/ante_toki.hpp"
#include "pali_pi_lipu_wawa_tan_kulupu_nimi/nimi_wawa.hpp"
#include <tclap/CmdLine.h>

// TODO o pini ante toki e sona kepeken pi lipu ni.
// TODO o pana e lupu tawa lipu pi nasin kepeken lon sona kepeken pi lipu ni.

// TODO o pali e lipu pi pana ike.

// TODO ken la o ante e niLaTawa() tawa ni: ona li pana e nimi tan jan.

// TODO o pona e nimi ike lon tomo Try/catch ali.

// TODO o ante e ike throw() ken tawa assert().

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
	pokiNanpaOpen["__nimi_jan"] 		 = *pali::kamaJoEPokiNanpaPiLawaOS(
		nimiPiILO_LI_SINA, "", nullptr, pokiOSPiNimiJan);
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
	std::string nimiPiILO_LI_SINA(nimiPilin[0]);

	// kama jo e toki wile li wile lon monsi pi toki e ijo.
	ante_toki::alasaETokiWile();

	try {
		TCLAP::CmdLine iloPiNimiPilin(ante_toki::kamaJoENimiTawaJan("ilo_CLI.sona_kepeken"), '=', "0.0");

		TCLAP::SwitchArg oTokiEKulupuNimi("n", "toki-e-nimi", ante_toki::kamaJoENimiTawaJan("ilo_CLI.toki_e_nimi.sona_kepeken"), iloPiNimiPilin, false);
		TCLAP::SwitchArg oTokiEKasiSuli("k", "toki-e-kasi", ante_toki::kamaJoENimiTawaJan("ilo_CLI.toki_e_kasi.sona_kepeken"), iloPiNimiPilin, false);
		TCLAP::UnlabeledMultiArg<std::string> nimiPiLipuWawa(ante_toki::kamaJoENimiTawaJan("ilo_CLI.lipu_wawa.nimi"), ante_toki::kamaJoENimiTawaJan("ilo_CLI.lipu_wawa.sona_kepeken"), true, ante_toki::kamaJoENimiTawaJan("ilo_CLI.lipu_wawa.nimi"), iloPiNimiPilin, true, static_cast<TCLAP::Visitor*>(nullptr));

		iloPiNimiPilin.parse(nanpaPiNimiPilin, nimiPilin);


		std::function<void(const std::string&, const std::string&)> paliWile = &lawaEIloNanpa;

		if (oTokiEKulupuNimi.getValue()) {
			paliWile = &tokiEKulupuNimi;

		} else if (oTokiEKasiSuli.getValue())
			paliWile = &tokiEKasiSuli;
		
		for (const std::string& lipuWawa : nimiPiLipuWawa.getValue())
			paliWile(lipuWawa, nimiPiILO_LI_SINA);

	} catch (const TCLAP::ArgException& ikePiNimiPilin) {
		kepeken::tokiEIke(nimiPiILO_LI_SINA, ikePiNimiPilin.what());
	}

	return 0;
}
