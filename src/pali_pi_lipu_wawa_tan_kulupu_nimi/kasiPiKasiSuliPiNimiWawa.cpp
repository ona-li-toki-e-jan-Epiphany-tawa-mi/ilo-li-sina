#include "kasiPiKasiSuliPiNimiWawa.hpp"

namespace pali {
	std::string kamaJoENimiPiNimiKasi(NimiKasi nimiKasi) noexcept(false) {
		switch (nimiKasi) {
			case NimiKasi::PANA_LON_POKI:
				return "PANA_LON_POKI";
			case NimiKasi::KAMA_JO_TAN_POKI:
				return "KAMA_JO_TAN_POKI";
			case NimiKasi::KAMA_JO_TAN_POKI_PI_ANTE_ALA:
				return "KAMA_JO_TAN_POKI_PI_ANTE_ALA";
			case NimiKasi::NIMI_WAWA:
				return "NIMI_WAWA";
			case NimiKasi::NIMI_TAWA:
				return "NIMI_TAWA";
			case NimiKasi::TAWA:
				return "TAWA";
			case NimiKasi::TAWA_KEN:
				return "TAWA_KEN";
			case NimiKasi::ALA:
				return "ALA";

			default:
				throw std::out_of_range("li kama jo e nimi kasi pi sona ala pi nanpa " + static_cast<int>(nimiKasi));
		}
	}



	KasiPiKasiSuli::KasiPiKasiSuli(const size_t nanpaLinja, const size_t nanpaSitelenLonLinja) {
		this->lonKasiLonLipuWawa = {nanpaLinja, nanpaSitelenLonLinja};
	}

	NimiKasi KasiPiKasiSuli::kamaJoENimiKasi() const {
		return NimiKasi::ALA;
	}

	KasiPiKasiSuli::~KasiPiKasiSuli() {}

	const kepeken::LonIjoLonLipuLawa& KasiPiKasiSuli::kamaJoELonKasi() const {
		return this->lonKasiLonLipuWawa;
	}



	KasiPiPanaLonPoki::KasiPiPanaLonPoki(const std::string& nimiPoki, const std::shared_ptr<KasiPiKasiSuli>& ijoTawaPana, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPoki = nimiPoki;
		this->ijoTawaPana = ijoTawaPana;
	}

	KasiPiPanaLonPoki* KasiPiPanaLonPoki::paliSama() const noexcept {
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



	KasiPiKamaJoTanPoki::KasiPiKamaJoTanPoki(const std::string& nimiPoki, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPoki = nimiPoki;
	}

	KasiPiKamaJoTanPoki* KasiPiKamaJoTanPoki::paliSama() const noexcept {
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



	KasiPiKamaJoTanPokiPiAnteAla::KasiPiKamaJoTanPokiPiAnteAla(const std::string& ijoTawaKama, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja) 
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->ijoTawaKama = ijoTawaKama;
	}

	KasiPiKamaJoTanPokiPiAnteAla* KasiPiKamaJoTanPokiPiAnteAla::paliSama() const noexcept {
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



	KasiPiNimiWawa::KasiPiNimiWawa(const nimi_wawa nimiWawa, const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaNimiWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiWawa = nimiWawa;
		this->kulupuPiIjoTawaNimiWawa = kulupuPiIjoTawaNimiWawa;
	}

	KasiPiNimiWawa* KasiPiNimiWawa::paliSama() const noexcept {
		std::vector<std::shared_ptr<KasiPiKasiSuli>> ijoTawaNimiWawa;
		ijoTawaNimiWawa.reserve(this->kulupuPiIjoTawaNimiWawa.size());

		for (auto alasaIjo = this->kulupuPiIjoTawaNimiWawa.cbegin(); alasaIjo != this->kulupuPiIjoTawaNimiWawa.cend(); alasaIjo++)
			ijoTawaNimiWawa.push_back(std::shared_ptr<KasiPiKasiSuli>((*alasaIjo)->paliSama()));

		return new KasiPiNimiWawa(
			this->nimiWawa, 
			ijoTawaNimiWawa,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiNimiWawa::~KasiPiNimiWawa() {}

	NimiKasi KasiPiNimiWawa::kamaJoENimiKasi() const {
		return NimiKasi::NIMI_WAWA;
	}

	nimi_wawa KasiPiNimiWawa::kamaJoENimiWawa() const {
		return this->nimiWawa;
	}

	const std::vector<std::shared_ptr<KasiPiKasiSuli>>& KasiPiNimiWawa::kamaJoEKulupuPiIjoTawaNimiWawa() const {
		return this->kulupuPiIjoTawaNimiWawa;
	}



	KasiPiNimiTawa::KasiPiNimiTawa(const std::string& nimiPiNimiTawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiPiNimiTawa = nimiPiNimiTawa;
	}

	KasiPiNimiTawa* KasiPiNimiTawa::paliSama() const noexcept {
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



	KasiTawa::KasiTawa(const size_t nanpaLinja, const size_t nanpaSitelenLonLinja) 
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->linjaTawaTawa = -1;
	}

	KasiTawa* KasiTawa::paliSama() const noexcept {
		KasiTawa* kasiTawaSin = new KasiTawa(
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
		kasiTawaSin->linjaTawaTawa = this->linjaTawaTawa;

		return kasiTawaSin;
	}

	KasiTawa::~KasiTawa() {}

	NimiKasi KasiTawa::kamaJoENimiKasi() const {
		return NimiKasi::TAWA;
	}



	KasiPiTawaKen::KasiPiTawaKen(const std::shared_ptr<KasiPiKasiSuli>& kasiLon, const std::shared_ptr<KasiPiKasiSuli>& kasiPiLonAla, const std::vector<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaToki, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja) 
		: KasiTawa(nanpaLinja, nanpaSitelenLonLinja) {
		this->kasiLon = kasiLon;
		this->kasiPiLonAla = kasiPiLonAla;
		this->kulupuPiIjoTawaToki = kulupuPiIjoTawaToki;
	}

	KasiPiTawaKen* KasiPiTawaKen::paliSama() const noexcept {
		std::vector<std::shared_ptr<KasiPiKasiSuli>> ijoTawaToki;
		ijoTawaToki.reserve(this->kulupuPiIjoTawaToki.size());

		for (auto alasaIjo = this->kulupuPiIjoTawaToki.cbegin(); alasaIjo != this->kulupuPiIjoTawaToki.cend(); alasaIjo++)
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
