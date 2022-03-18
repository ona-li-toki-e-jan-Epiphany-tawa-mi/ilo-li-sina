#include "kasiPiKasiSuliPiNimiWawa.hpp"

namespace pali {
	KasiPiKasiSuli::~KasiPiKasiSuli() {}

	NimiKasi KasiPiKasiSuli::kamaJoENimiKasi() const {
		return this->nimiKasi;
	}



	KasiPiPanaLonPoki::KasiPiPanaLonPoki(const std::string& nimiPoki, KasiPiKasiSuli* ijoTawaPana) {
		this->nimiPoki = nimiPoki;
		this->ijoTawaPana = ijoTawaPana;

		this->nimiKasi = NimiKasi::PANA_LON_POKI;
	}

	KasiPiPanaLonPoki::KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante) {
		this->nimiPoki = ante.nimiPoki;
		this->ijoTawaPana = new KasiPiKasiSuli(*ante.ijoTawaPana);

		this->nimiKasi = NimiKasi::PANA_LON_POKI;
	}

	KasiPiPanaLonPoki::KasiPiPanaLonPoki(KasiPiPanaLonPoki&& ante) {
		*this = std::move(ante);
	}

	KasiPiPanaLonPoki& KasiPiPanaLonPoki::operator=(KasiPiPanaLonPoki&& ante) {
		this->nimiPoki = std::move(ante.nimiPoki);
		this->ijoTawaPana = ante.ijoTawaPana;

		this->nimiKasi = NimiKasi::PANA_LON_POKI;

		ante.nimiKasi = NimiKasi::ALA;
		ante.ijoTawaPana = nullptr;

		return *this;
	}

	KasiPiPanaLonPoki::~KasiPiPanaLonPoki() {
		delete this->ijoTawaPana;
	}

	const std::string& KasiPiPanaLonPoki::kamaJoENimiPoki() const {
		return this->nimiPoki;
	}

	const KasiPiKasiSuli* KasiPiPanaLonPoki::kamaJoEIjoTawaPana() const {
		return this->ijoTawaPana;
	}



	KasiPiKamaJoTanPoki::KasiPiKamaJoTanPoki(const std::string& nimiPoki) {
		this->nimiPoki = nimiPoki;
		this->nimiKasi = NimiKasi::KAMA_JO_TAN_POKI;
	}

	const std::string& KasiPiKamaJoTanPoki::kamaJoENimiPoki() const {
		return nimiPoki;
	}



	KasiPiKamaJoTanPokiPiAnteAla::KasiPiKamaJoTanPokiPiAnteAla(const std::string& ijoTawaKama) {
		this->ijoTawaKama = ijoTawaKama;
		this->nimiKasi = NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA;
	}

	const std::string& KasiPiKamaJoTanPokiPiAnteAla::kamaJoEIjoPoki() const {
		return this->ijoTawaKama;
	}



	KasiPiNimiWawa::KasiPiNimiWawa(const std::string& nimiPiNimiWawa, const std::vector<KasiPiKasiSuli*>& kulupuPiIjoTawaNimiWawa) {
		this->nimiPiNimiWawa = nimiPiNimiWawa;
		this->kulupuPiIjoTawaNimiWawa = kulupuPiIjoTawaNimiWawa;

		this->nimiKasi = NimiKasi::NIMI_WAWA;
	}

	KasiPiNimiWawa::KasiPiNimiWawa(const KasiPiNimiWawa& ante) {
		this->nimiPiNimiWawa = ante.nimiPiNimiWawa;
		for (pali::KasiPiKasiSuli* ijo : ante.kulupuPiIjoTawaNimiWawa)
			this->kulupuPiIjoTawaNimiWawa.push_back(new KasiPiKasiSuli(*ijo));

		this->nimiKasi = NimiKasi::NIMI_WAWA;
	}

	KasiPiNimiWawa::KasiPiNimiWawa(KasiPiNimiWawa&& ante) {
		*this = std::move(ante);
	}

	KasiPiNimiWawa& KasiPiNimiWawa::operator=(KasiPiNimiWawa&& ante) {
		this->nimiPiNimiWawa = std::move(ante.nimiPiNimiWawa);
		this->kulupuPiIjoTawaNimiWawa = std::move(ante.kulupuPiIjoTawaNimiWawa);

		this->nimiKasi = NimiKasi::NIMI_WAWA;

		ante.nimiKasi = NimiKasi::ALA;

		return *this;
	}

	KasiPiNimiWawa::~KasiPiNimiWawa() {
		for (pali::KasiPiKasiSuli* ijo : this->kulupuPiIjoTawaNimiWawa)
			delete ijo;
	}

	const std::string& KasiPiNimiWawa::kamaJoENimiPiNimiWawa() const {
		return this->nimiPiNimiWawa;
	}

	const std::vector<KasiPiKasiSuli*>& KasiPiNimiWawa::kamaJoEKulupuPiIjoTawaNimiWawa() const {
		return this->kulupuPiIjoTawaNimiWawa;
	}
}
