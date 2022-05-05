#include "kasiPiKasiSuliPiNimiWawa.hpp"
#include <iostream>
#include "../ante_toki/ante_toki.hpp"

namespace pali {
	KasiPiKasiSuli::KasiPiKasiSuli(const size_t nanpaLinja, const size_t nanpaSitelenLonLinja) {
		this->lonKasiLonLipuWawa = {nanpaLinja, nanpaSitelenLonLinja};
	}

	NimiKasi KasiPiKasiSuli::kamaJoENimiKasi() const {
		// TODO ken la ni li kama la o toki e ike.
		return NimiKasi::ALA;
	}

	const std::string& KasiPiKasiSuli::kamaJoENimiPiNimiKasi() const {
		// TODO ken la ni li kama la o toki e ike.
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.ala");
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

	const std::string& KasiPiPanaLonPoki::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.pana_lon_poki");
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

	const std::string& KasiPiKamaJoTanPoki::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.kama_jo_tan_poki");
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

	const std::string& KasiPiKamaJoTanPokiPiAnteAla::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.kama_jo_tan_poki_pi_ante_ala");
	}

	const std::string& KasiPiKamaJoTanPokiPiAnteAla::kamaJoEIjoPoki() const {
		return this->ijoTawaKama;
	}



	KasiPiNimiWawa::KasiPiNimiWawa(const nimi_wawa nimiWawa, const std::list<std::shared_ptr<KasiPiKasiSuli>>& kulupuPiIjoTawaNimiWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: KasiPiKasiSuli(nanpaLinja, nanpaSitelenLonLinja) {
		this->nimiWawa = nimiWawa;
		this->kulupuPiIjoTawaNimiWawa = kulupuPiIjoTawaNimiWawa;
	}

	KasiPiNimiWawa* KasiPiNimiWawa::paliSama() const noexcept {
		std::list<std::shared_ptr<KasiPiKasiSuli>> ijoTawaNimiWawa;

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

	const std::string& KasiPiNimiWawa::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.nimi_wawa");
	}

	nimi_wawa KasiPiNimiWawa::kamaJoENimiWawa() const {
		return this->nimiWawa;
	}

	const std::list<std::shared_ptr<KasiPiKasiSuli>>& KasiPiNimiWawa::kamaJoEKulupuPiIjoTawaNimiWawa() const {
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

	const std::string& KasiPiNimiTawa::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.nimi_tawa");
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

	const std::string& KasiTawa::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.tawa");
	}

	const std::list<std::shared_ptr<KasiPiKasiSuli>>& KasiTawa::kamaJoEIjoTawaTawa() const {
		return this->ijoTawaTawa;
	}

	std::optional<bool> KasiTawa::liKenTawa(const std::string& nimiPiILO_LI_SINA, const std::string& nimiLipu, const std::list<std::string>& nimiTawaTawa) const {
		return true;
	}



	KasiPiTawaKen::KasiPiTawaKen(const std::list<std::shared_ptr<KasiPiKasiSuli>>& ijoTawaTawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja)
		: KasiTawa(nanpaLinja, nanpaSitelenLonLinja) {
		this->ijoTawaTawa = ijoTawaTawa;
	}

	KasiPiTawaKen* KasiPiTawaKen::paliSama() const noexcept {
		std::list<std::shared_ptr<KasiPiKasiSuli>> ijoSin;

		for (auto alasaIjo = this->ijoTawaTawa.cbegin(); alasaIjo != this->ijoTawaTawa.cend(); alasaIjo++)
			ijoSin.push_back(std::shared_ptr<KasiPiKasiSuli>((*alasaIjo)->paliSama()));

		return new KasiPiTawaKen(
			ijoSin,
			this->lonKasiLonLipuWawa.nanpaLinja, this->lonKasiLonLipuWawa.nanpaSitelenLonLinja);
	}

	KasiPiTawaKen::~KasiPiTawaKen() {}

	const std::string& KasiPiTawaKen::kamaJoENimiPiNimiKasi() const {
		return ante_toki::kamaJoENimiTawaJan("toki.nimi_kasi.tawa_ken");
	}

	std::optional<bool> KasiPiTawaKen::liKenTawa(const std::string& nimiPiILO_LI_SINA, const std::string& nimiLipu, const std::list<std::string>& nimiTawaTawa) const {
		// li wile e nimi lon e nimi pi lon ala.
		// TODO o pana e ni lon tenpo pali.
		if (nimiTawaTawa.size() < 2) {
			kepeken::tokiEIke(
				nimiPiILO_LI_SINA, nimiLipu,
				this->lonKasiLonLipuWawa,
				ante_toki::kamaJoENimiTawaJan("ike.pali.nimi_wawa.niLaTawa.nanpa_ijo_lili"));

			return std::nullopt;
		}
		
		auto alasaNimi = nimiTawaTawa.cbegin();
		const std::string& nimiLon 		= *(alasaNimi++);
		const std::string& nimiPiLonAla = *(alasaNimi++);
		// nimi lon en nimi pi lon ala li ken ala sama. 1 li ken jo e ala. taso, ona tu li ken ala jo e ala lon tenpo sama.
		if ((nimiLon.size() == 0 && nimiPiLonAla.size() == 0) || nimiLon == nimiPiLonAla) {
			kepeken::tokiEIke(
				nimiPiILO_LI_SINA, nimiLipu,
				this->lonKasiLonLipuWawa,
				ante_toki::anteENimi(
					ante_toki::kamaJoENimiTawaJan("ike.lawa.tawa_ken.nimi_pi_lon_en_lon_ala_li_ken_ala_sama"),
					"%s", nimiLon));

			return std::nullopt;
		}

		const auto openPiIjoTawaToki = alasaNimi;
		std::string nimiTanJan;

		// jan li toki e ike la li wile toki sin e ijo.
		while (true) {
			if (openPiIjoTawaToki != nimiTawaTawa.cend()) {
				for (alasaNimi = openPiIjoTawaToki; alasaNimi != nimiTawaTawa.cend(); alasaNimi++)
					std::cout << *alasaNimi;
				std::cout << ' ';
			}
			std::cout << "(" << nimiLon << '/' << nimiPiLonAla << ")\n";

			if (!std::getline(std::cin, nimiTanJan)) {
				kepeken::tokiEIke(
					nimiPiILO_LI_SINA, nimiPiILO_LI_SINA,
					this->lonKasiLonLipuWawa,
					ante_toki::kamaJoENimiTawaJan("ike.lawa.pini_lipu"));

				break;
			}

			if (nimiLon.size() == 0 && nimiTanJan != nimiPiLonAla) {
				return true;

			} else if (nimiPiLonAla.size() == 0 && nimiTanJan != nimiLon) {
				return false;

			} else if (nimiTanJan == nimiLon) {
				return true;
			
			} else if (nimiTanJan == nimiPiLonAla)
				return false;
		}

		return std::nullopt;
	}
}
