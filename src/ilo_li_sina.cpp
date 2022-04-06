#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include "kipisi_pi_lipu_wawa/kipisi.hpp"
#include "pali_pi_lipu_wawa_tan_kulupu_nimi/pali.hpp"
#include "lawa_pi_ilo_nanpa/lawa.hpp"

// TODO o pona e ike lon toki pona.
// TODO o ken e ni: jan li ken sitelen e nimi wawa 1 e ijo ante 1 lon linja mute kepeken sitelen '\' lon pini pi linja pi pini ala. 
// TODO o pali e ni: sina ken sitelen e ijo tawa ni: lipu wawa ni li toki e kasi pi lipu wawa li lawa ala kekpeken ona.
// TODO o kepeken e poki List en ForwardList lon ni: ona li kepeken li lili e tenpo tawa lawa.

int main(int argc, char** argv) {
	if (argc <= 1) {
		std::cerr << "Insufficient number of arguments!" << std::endl;
		return 1;
	}

	std::vector<std::shared_ptr<pali::KasiPiKasiSuli>> lipuWawaTanKulupuNimi;
	lipuWawaTanKulupuNimi.reserve(25);

	{
		std::vector<kipisi::KulupuNimi> kulupuNimiPiLipuWawa;
		kulupuNimiPiLipuWawa.reserve(500);
		kipisi::kipisiELipuWawa(kulupuNimiPiLipuWawa, argv[1]);

		pali::paliELipuWawa(lipuWawaTanKulupuNimi, kulupuNimiPiLipuWawa, argv[1]);
		//pali::tokiEKasiSuli(lipuWawaTanKulupuNimi);
	}

	lawa::lawaEIloNanpa(lipuWawaTanKulupuNimi, argv[1]);

	return 0;
}
