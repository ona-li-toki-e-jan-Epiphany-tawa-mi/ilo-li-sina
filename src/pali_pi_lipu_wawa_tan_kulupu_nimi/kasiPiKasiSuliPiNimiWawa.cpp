#include "kasiPiKasiSuliPiNimiWawa.hpp"

namespace pali {
	NimiKasi KasiPiKasiSuli::kamaJoENimiKasi() const {
		return NimiKasi::ALA;
	}

	KasiPiKasiSuli::~KasiPiKasiSuli() {}



	KasiPiPanaLonPoki::KasiPiPanaLonPoki(const std::string& nimiPoki, KasiPiKasiSuli* ijoTawaPana) {
		this->nimiPoki = nimiPoki;
		this->ijoTawaPana = ijoTawaPana;
	}

	KasiPiPanaLonPoki* KasiPiPanaLonPoki::paliSama() const {
		return new KasiPiPanaLonPoki(
			this->nimiPoki, this->ijoTawaPana->paliSama());
	}

	KasiPiPanaLonPoki::KasiPiPanaLonPoki(KasiPiPanaLonPoki&& ante) {
		*this = std::move(ante);
	}

	KasiPiPanaLonPoki& KasiPiPanaLonPoki::operator=(KasiPiPanaLonPoki&& ante) {
		this->nimiPoki = std::move(ante.nimiPoki);
		this->ijoTawaPana = ante.ijoTawaPana;

		ante.ijoTawaPana = nullptr;

		return *this;
	}

	KasiPiPanaLonPoki::~KasiPiPanaLonPoki() {
		delete this->ijoTawaPana;
	}

	NimiKasi KasiPiPanaLonPoki::kamaJoENimiKasi() const {
		return NimiKasi::PANA_LON_POKI;
	}

	const std::string& KasiPiPanaLonPoki::kamaJoENimiPoki() const {
		return this->nimiPoki;
	}

	const KasiPiKasiSuli* KasiPiPanaLonPoki::kamaJoEIjoTawaPana() const {
		return this->ijoTawaPana;
	}



	KasiPiKamaJoTanPoki::KasiPiKamaJoTanPoki(const std::string& nimiPoki) {
		this->nimiPoki = nimiPoki;
	}

	KasiPiKamaJoTanPoki* KasiPiKamaJoTanPoki::paliSama() const {
		return new KasiPiKamaJoTanPoki(
			this->nimiPoki);
	}

	KasiPiKamaJoTanPoki::~KasiPiKamaJoTanPoki() {}

	NimiKasi KasiPiKamaJoTanPoki::kamaJoENimiKasi() const {
		return NimiKasi::KAMA_JO_TAN_POKI;
	}

	const std::string& KasiPiKamaJoTanPoki::kamaJoENimiPoki() const {
		return nimiPoki;
	}



	KasiPiKamaJoTanPokiPiAnteAla::KasiPiKamaJoTanPokiPiAnteAla(const std::string& ijoTawaKama) {
		this->ijoTawaKama = ijoTawaKama;
	}

	KasiPiKamaJoTanPokiPiAnteAla* KasiPiKamaJoTanPokiPiAnteAla::paliSama() const {
		return new KasiPiKamaJoTanPokiPiAnteAla(
			this->ijoTawaKama);
	}

	KasiPiKamaJoTanPokiPiAnteAla::~KasiPiKamaJoTanPokiPiAnteAla() {}

	NimiKasi KasiPiKamaJoTanPokiPiAnteAla::kamaJoENimiKasi() const {
		return NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA;
	}

	const std::string& KasiPiKamaJoTanPokiPiAnteAla::kamaJoEIjoPoki() const {
		return this->ijoTawaKama;
	}



	KasiPiNimiWawa::KasiPiNimiWawa(const std::string& nimiPiNimiWawa, const std::vector<KasiPiKasiSuli*>& kulupuPiIjoTawaNimiWawa) {
		this->nimiPiNimiWawa = nimiPiNimiWawa;
		this->kulupuPiIjoTawaNimiWawa = kulupuPiIjoTawaNimiWawa;
	}

	KasiPiNimiWawa* KasiPiNimiWawa::paliSama() const {
		std::vector<KasiPiKasiSuli*> ijoTawaNimiWawa;
		ijoTawaNimiWawa.reserve(this->kulupuPiIjoTawaNimiWawa.size());

		for (KasiPiKasiSuli* ijo : this->kamaJoEKulupuPiIjoTawaNimiWawa())
			ijoTawaNimiWawa.push_back(ijo->paliSama());

		return new KasiPiNimiWawa(
			this->nimiPiNimiWawa, ijoTawaNimiWawa);
	}

	KasiPiNimiWawa::KasiPiNimiWawa(KasiPiNimiWawa&& ante) {
		*this = std::move(ante);
	}

	KasiPiNimiWawa& KasiPiNimiWawa::operator=(KasiPiNimiWawa&& ante) {
		this->nimiPiNimiWawa = std::move(ante.nimiPiNimiWawa);
		this->kulupuPiIjoTawaNimiWawa = std::move(ante.kulupuPiIjoTawaNimiWawa);

		return *this;
	}

	KasiPiNimiWawa::~KasiPiNimiWawa() {
		for (pali::KasiPiKasiSuli* ijo : this->kulupuPiIjoTawaNimiWawa)
			delete ijo;
	}

	NimiKasi KasiPiNimiWawa::kamaJoENimiKasi() const {
		return NimiKasi::NIMI_WAWA;
	}

	const std::string& KasiPiNimiWawa::kamaJoENimiPiNimiWawa() const {
		return this->nimiPiNimiWawa;
	}

	const std::vector<KasiPiKasiSuli*>& KasiPiNimiWawa::kamaJoEKulupuPiIjoTawaNimiWawa() const {
		return this->kulupuPiIjoTawaNimiWawa;
	}



	KasiPiNimiTawa::KasiPiNimiTawa(const std::string nimiPiNimiTawa) {
		this->nimiPiNimiTawa = nimiPiNimiTawa;
	}

	KasiPiNimiTawa* KasiPiNimiTawa::paliSama() const {
		return new KasiPiNimiTawa(this->nimiPiNimiTawa);
	}

	KasiPiNimiTawa::~KasiPiNimiTawa() {}

	NimiKasi KasiPiNimiTawa::kamaJoENimiKasi() const {
		return NimiKasi::NIMI_TAWA;
	}

	const std::string KasiPiNimiTawa::kamaJoENimiPiNimiTawa() const {
		return this->nimiPiNimiTawa;
	}



	KasiTawa::KasiTawa() {
		this->linjaTawaTawa = -1;
	}

	KasiTawa* KasiTawa::paliSama() const {
		KasiTawa* kasiTawaSin = new KasiTawa();
		kasiTawaSin->linjaTawaTawa = this->linjaTawaTawa;

		return kasiTawaSin;
	}

	NimiKasi KasiTawa::kamaJoENimiKasi() const {
		return NimiKasi::TAWA;
	}

	KasiTawa::~KasiTawa() {}



	KasiPiTawaKen::KasiPiTawaKen(KasiPiKasiSuli* kasiLon, KasiPiKasiSuli* kasiPiLonAla, const std::vector<KasiPiKasiSuli*>& kulupuPiIjoTawaToki) 
		: KasiTawa() {
		this->kasiLon = kasiLon;
		this->kasiPiLonAla = kasiPiLonAla;
		this->kulupuPiIjoTawaToki = kulupuPiIjoTawaToki;
	}

	KasiPiTawaKen* KasiPiTawaKen::paliSama() const {
		std::vector<KasiPiKasiSuli*> ijoTawaToki;
		ijoTawaToki.reserve(this->kulupuPiIjoTawaToki.size());

		for (KasiPiKasiSuli* ijo : this->kulupuPiIjoTawaToki)
			ijoTawaToki.push_back(ijo->paliSama());

		return new KasiPiTawaKen(
			this->kasiLon->paliSama(), this->kasiPiLonAla->paliSama(), ijoTawaToki);
	}

	KasiPiTawaKen::KasiPiTawaKen(KasiPiTawaKen&& ante) {
		*this = std::move(ante);
	}

	KasiPiTawaKen& KasiPiTawaKen::operator=(KasiPiTawaKen&& ante) {
		this->linjaTawaTawa = ante.linjaTawaTawa;
		this->kasiLon = ante.kasiLon;
		this->kasiPiLonAla = ante.kasiPiLonAla;
		this->kulupuPiIjoTawaToki = std::move(ante.kulupuPiIjoTawaToki);

		ante.linjaTawaTawa = -1;
		ante.kasiLon = nullptr;
		ante.kasiPiLonAla = nullptr;

		return *this;
	}

	KasiPiTawaKen::~KasiPiTawaKen() {
		delete this->kasiLon;
		delete this->kasiPiLonAla;
		for (pali::KasiPiKasiSuli* ijo : this->kulupuPiIjoTawaToki)
			delete ijo;
	}

	NimiKasi KasiPiTawaKen::kamaJoENimiKasi() const {
		return NimiKasi::TAWA_KEN;
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
