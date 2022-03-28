#include <fstream>
#include <iostream>
#include <vector>
#include "kipisi_pi_lipu_wawa/kipisi.hpp"
#include "pali_pi_lipu_wawa_tan_kulupu_nimi/pali.hpp"
#include "lawa_pi_ilo_nanpa/lawa.hpp"

// TODO o pona e ike lon toki pona.
// TODO o pali e ni: toki ike li pini ala e lipu wawa ni.

int main(int argc, char** argv) {
	if (argc <= 1) {
		std::cerr << "Insufficient number of arguments!" << std::endl;
		return 1;
	}

	std::vector<pali::KasiPiKasiSuli*> lipuWawaTanKulupuNimi;
	lipuWawaTanKulupuNimi.reserve(25);

	{
		std::vector<kipisi::KulupuNimi> kulupuNimiPiLipuWawa;
		kulupuNimiPiLipuWawa.reserve(500);
		kipisi::kipisiELipuWawa(kulupuNimiPiLipuWawa, argv[1]);

		pali::paliELipuWawa(lipuWawaTanKulupuNimi, kulupuNimiPiLipuWawa, argv[1]);
	}

	lawa::lawaEIloNanpa(lipuWawaTanKulupuNimi);

	for (pali::KasiPiKasiSuli* kasi : lipuWawaTanKulupuNimi)
		delete kasi;

	return 0;
}
