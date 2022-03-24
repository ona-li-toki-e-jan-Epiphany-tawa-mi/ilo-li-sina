#include "kasiPiKasiSuliPiNimiWawa.hpp"

// FIXME o kepeken e nimi wawa pi pali sama pi kiwen ala e nimi wawa pali ala pi pali sama.

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
		for (KasiPiKasiSuli* ijo : ante.kulupuPiIjoTawaNimiWawa)
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



	KasiPiNimiTawa::KasiPiNimiTawa(const std::string* nimiPiNimiTawa) {
		this->nimiPiNimiTawa = nimiPiNimiTawa;

		this->nimiKasi = NimiKasi::NIMI_TAWA;
	}

	const std::string* KasiPiNimiTawa::kamaJoENimiPiNimiTawa() const {
		return this->nimiPiNimiTawa;
	}



	KasiTawa::KasiTawa() {
		this->linjaTawaTawa = -1;
		this->nimiKasi = NimiKasi::TAWA;
	}



	KasiPiTawaKen::KasiPiTawaKen(KasiPiKasiSuli* kasiLon, KasiPiKasiSuli* kasiPiLonAla, const std::vector<KasiPiKasiSuli*>& kulupuPiIjoTawaToki) {
		this->linjaTawaTawa = -1;
		this->kasiLon = kasiLon;
		this->kasiPiLonAla = kasiPiLonAla;
		this->kulupuPiIjoTawaToki = kulupuPiIjoTawaToki;

		this->nimiKasi = NimiKasi::TAWA_KEN;
	}

	KasiPiTawaKen::KasiPiTawaKen(const KasiPiTawaKen& ante) {
		this->linjaTawaTawa = ante.linjaTawaTawa;
		this->kasiLon = new KasiPiKasiSuli(*ante.kasiLon);
		this->kasiPiLonAla = new KasiPiKasiSuli(*ante.kasiPiLonAla);
		for (KasiPiKasiSuli* ijo : ante.kulupuPiIjoTawaToki)
			this->kulupuPiIjoTawaToki.push_back(new KasiPiKasiSuli(*ijo));

		this->nimiKasi = NimiKasi::TAWA_KEN;
	}

	KasiPiTawaKen::KasiPiTawaKen(KasiPiTawaKen&& ante) {
		*this = std::move(ante);
	}

	KasiPiTawaKen& KasiPiTawaKen::operator=(KasiPiTawaKen&& ante) {
		this->linjaTawaTawa = ante.linjaTawaTawa;
		this->kasiLon = ante.kasiLon;
		this->kasiPiLonAla = ante.kasiPiLonAla;
		this->kulupuPiIjoTawaToki = std::move(ante.kulupuPiIjoTawaToki);

		this->nimiKasi = NimiKasi::TAWA_KEN;

		ante.linjaTawaTawa = -1;
		ante.kasiLon = nullptr;
		ante.kasiPiLonAla = nullptr;
		ante.nimiKasi = NimiKasi::ALA;

		return *this;
	}

	KasiPiTawaKen::~KasiPiTawaKen() {
		delete this->kasiLon;
		delete this->kasiPiLonAla;
		for (pali::KasiPiKasiSuli* ijo : this->kulupuPiIjoTawaToki)
			delete ijo;
	}

	const KasiPiKasiSuli* KasiPiTawaKen::kamaJoEKasiLon() const {
		return this->kasiLon;
	}

	const KasiPiKasiSuli* KasiPiTawaKen::kamaJoEKasiPiLonAla() const {
		return this->kasiPiLonAla;
	}

	const std::vector<KasiPiKasiSuli*>& KasiPiTawaKen::kamaJoEKulupuPiIjoToki() const {
		return this->kulupuPiIjoTawaToki;
	}
}
