#include "kasiPiKasiSuliPiNimiWawa.hpp"

namespace pali {
	KasiPiKasiSuli::KasiPiKasiSuli(size_t nanpaLinja, size_t nanpaSitelenLonLinja) {
		this->lonKasiLonLipuWawa = {nanpaLinja, nanpaSitelenLonLinja};
	}

	NimiKasi KasiPiKasiSuli::kamaJoENimiKasi() const {
		return NimiKasi::ALA;
	}

	KasiPiKasiSuli::~KasiPiKasiSuli() {}

	const LonKasiLonLipuWawa& KasiPiKasiSuli::kamaJoELonKasi() const {
		return this->lonKasiLonLipuWawa;
	}



	KasiPiPanaLonPoki::KasiPiPanaLonPoki(const std::string& nimiPoki, const std::shared_ptr<KasiPiKasiSuli>& ijoTawaPana, size_t nanpaLinja, size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPoki = nimiPoki;
		this->ijoTawaPana = ijoTawaPana;
	}

	KasiPiPanaLonPoki* KasiPiPanaLonPoki::paliSama() const {
		return new KasiPiPanaLonPoki(
			this->nimiPoki, 
			std::shared_ptr<KasiPiKasiSuli>(this->ijoTawaPana->paliSama()), 
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiPanaLonPoki::~KasiPiPanaLonPoki() {}

	NimiKasi KasiPiPanaLonPoki::kamaJoENimiKasi() const {
		return NimiKasi::PANA_LON_POKI;
	}

	const std::string& KasiPiPanaLonPoki::kamaJoENimiPoki() const {
		return this->nimiPoki;
	}

	std::shared_ptr<const KasiPiKasiSuli> KasiPiPanaLonPoki::kamaJoEIjoTawaPana() const {
		return this->ijoTawaPana;
	}



	KasiPiKamaJoTanPoki::KasiPiKamaJoTanPoki(const std::string& nimiPoki, size_t nanpaLinja, size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPoki = nimiPoki;
	}

	KasiPiKamaJoTanPoki* KasiPiKamaJoTanPoki::paliSama() const {
		return new KasiPiKamaJoTanPoki(
			this->nimiPoki,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiKamaJoTanPoki::~KasiPiKamaJoTanPoki() {}

	NimiKasi KasiPiKamaJoTanPoki::kamaJoENimiKasi() const {
		return NimiKasi::KAMA_JO_TAN_POKI;
	}

	const std::string& KasiPiKamaJoTanPoki::kamaJoENimiPoki() const {
		return nimiPoki;
	}



	KasiPiKamaJoTanPokiPiAnteAla::KasiPiKamaJoTanPokiPiAnteAla(const std::string& ijoTawaKama, size_t nanpaLinja, size_t nanpaSitelenLonLinja) 
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->ijoTawaKama = ijoTawaKama;
	}

	KasiPiKamaJoTanPokiPiAnteAla* KasiPiKamaJoTanPokiPiAnteAla::paliSama() const {
		return new KasiPiKamaJoTanPokiPiAnteAla(
			this->ijoTawaKama,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiKamaJoTanPokiPiAnteAla::~KasiPiKamaJoTanPokiPiAnteAla() {}

	NimiKasi KasiPiKamaJoTanPokiPiAnteAla::kamaJoENimiKasi() const {
		return NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA;
	}

	const std::string& KasiPiKamaJoTanPokiPiAnteAla::kamaJoEIjoPoki() const {
		return this->ijoTawaKama;
	}



	KasiPiNimiWawa::KasiPiNimiWawa(const std::string& nimiPiNimiWawa, const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaNimiWawa, size_t nanpaLinja, size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPiNimiWawa = nimiPiNimiWawa;
		this->kulupuPiIjoTawaNimiWawa = kulupuPiIjoTawaNimiWawa;
	}

	KasiPiNimiWawa* KasiPiNimiWawa::paliSama() const {
		std::vector<std::shared_ptr<KasiPiKasiSuli>> ijoTawaNimiWawa;
		ijoTawaNimiWawa.reserve(this->kulupuPiIjoTawaNimiWawa.size());

		for (auto alasaIjo = this->kulupuPiIjoTawaNimiWawa.begin(); alasaIjo != this->kulupuPiIjoTawaNimiWawa.end(); alasaIjo++)
			ijoTawaNimiWawa.push_back(std::shared_ptr<KasiPiKasiSuli>((*alasaIjo)->paliSama()));

		return new KasiPiNimiWawa(
			this->nimiPiNimiWawa, 
			ijoTawaNimiWawa,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiNimiWawa::~KasiPiNimiWawa() {}

	NimiKasi KasiPiNimiWawa::kamaJoENimiKasi() const {
		return NimiKasi::NIMI_WAWA;
	}

	const std::string& KasiPiNimiWawa::kamaJoENimiPiNimiWawa() const {
		return this->nimiPiNimiWawa;
	}

	const std::vector<std::shared_ptr<KasiPiKasiSuli>>& KasiPiNimiWawa::kamaJoEKulupuPiIjoTawaNimiWawa() const {
		return this->kulupuPiIjoTawaNimiWawa;
	}



	KasiPiNimiTawa::KasiPiNimiTawa(const std::string nimiPiNimiTawa, size_t nanpaLinja, size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPiNimiTawa = nimiPiNimiTawa;
	}

	KasiPiNimiTawa* KasiPiNimiTawa::paliSama() const {
		return new KasiPiNimiTawa(
			this->nimiPiNimiTawa,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiNimiTawa::~KasiPiNimiTawa() {}

	NimiKasi KasiPiNimiTawa::kamaJoENimiKasi() const {
		return NimiKasi::NIMI_TAWA;
	}

	const std::string& KasiPiNimiTawa::kamaJoENimiPiNimiTawa() const {
		return this->nimiPiNimiTawa;
	}



	KasiTawa::KasiTawa(size_t nanpaLinja, size_t nanpaSitelenLonLinja) 
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->linjaTawaTawa = -1;
	}

	KasiTawa* KasiTawa::paliSama() const {
		KasiTawa* kasiTawaSin = new KasiTawa(
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
		kasiTawaSin->linjaTawaTawa = this->linjaTawaTawa;

		return kasiTawaSin;
	}

	KasiTawa::~KasiTawa() {}

	NimiKasi KasiTawa::kamaJoENimiKasi() const {
		return NimiKasi::TAWA;
	}



	KasiPiTawaKen::KasiPiTawaKen(const std::shared_ptr<KasiPiKasiSuli>& kasiLon, const std::shared_ptr<KasiPiKasiSuli>& kasiPiLonAla, const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaToki, size_t nanpaLinja, size_t nanpaSitelenLonLinja) 
		: KasiTawa(nanpaLinja, nanpaSitelenLonLinja) {
		this->kasiLon = kasiLon;
		this->kasiPiLonAla = kasiPiLonAla;
		this->kulupuPiIjoTawaToki = kulupuPiIjoTawaToki;
	}

	KasiPiTawaKen* KasiPiTawaKen::paliSama() const {
		std::vector<std::shared_ptr<KasiPiKasiSuli>> ijoTawaToki;
		ijoTawaToki.reserve(this->kulupuPiIjoTawaToki.size());

		for (auto alasaIjo = this->kulupuPiIjoTawaToki.begin(); alasaIjo != this->kulupuPiIjoTawaToki.end(); alasaIjo++)
			ijoTawaToki.push_back(std::shared_ptr<KasiPiKasiSuli>((*alasaIjo)->paliSama()));

		return new KasiPiTawaKen(
			std::shared_ptr<KasiPiKasiSuli>(this->kasiLon->paliSama()), 
			std::shared_ptr<KasiPiKasiSuli>(this->kasiPiLonAla->paliSama()), 
			ijoTawaToki,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiTawaKen::~KasiPiTawaKen() {}

	NimiKasi KasiPiTawaKen::kamaJoENimiKasi() const {
		return NimiKasi::TAWA_KEN;
	}

	std::shared_ptr<const KasiPiKasiSuli> KasiPiTawaKen::kamaJoEKasiLon() const {
		return this->kasiLon;
	}

	std::shared_ptr<const KasiPiKasiSuli> KasiPiTawaKen::kamaJoEKasiPiLonAla() const {
		return this->kasiPiLonAla;
	}

	const std::vector<std::shared_ptr<KasiPiKasiSuli>>& KasiPiTawaKen::kamaJoEKulupuPiIjoToki() const {
		return this->kulupuPiIjoTawaToki;
	}
}
