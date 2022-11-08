#include "kasi.hpp"

namespace ilo {
    KasiOpen::KasiOpen() {
        this->lonKasi = {0, 0};
    }

    KasiOpen* KasiOpen::paliSama() const {
        return new KasiOpen(*this);
    }

    std::string KasiOpen::nimiPiNimiKasi() const {
        return "";
    }

    KasiOpen::KasiOpen(KasiOpen&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiOpen& KasiOpen::operator=(KasiOpen&& ante) noexcept {
        if (this != &ante)
            this->kasiLonAnpa = std::move(ante.kasiLonAnpa);

        return *this;
    }

    KasiOpen::KasiOpen(const KasiOpen& ante) {
        for (const auto& kasi : ante.kasiLonAnpa)
            this->kasiLonAnpa.push_back(
                    std::unique_ptr<KasiLipu>(kasi->paliSama()));
    }



    KasiPini* KasiPini::paliSama() const {
        return new KasiPini(*this);
    }

    std::string KasiPini::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.pini"; 
    }



    KasiPiPokiNimi* KasiPiPokiNimi::paliSama() const {
        return new KasiPiPokiNimi(*this);
    }

    KasiPiPokiNimi::KasiPiPokiNimi(KasiPiPokiNimi&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPiPokiNimi& KasiPiPokiNimi::operator=(KasiPiPokiNimi&& ante) noexcept {
        if (this != &ante)
            this->nimi = std::move(ante.nimi);

        return *this;
    }
    
    std::string KasiPiPokiNimi::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.poki_nimi";
    }



    KasiPoki* KasiPoki::paliSama() const {
        return new KasiPoki(*this);
    }

    KasiPoki::KasiPoki(KasiPoki&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPoki& KasiPoki::operator=(KasiPoki&& ante) noexcept {
        if (this != &ante)
            this->nimiPoki = std::move(ante.nimiPoki);

        return *this;
    }

    std::string KasiPoki::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.kama_jo_tan_poki";
    }



    KasiTomoPiNimiWawa::KasiTomoPiNimiWawa(KasiTomoPiNimiWawa&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiTomoPiNimiWawa& KasiTomoPiNimiWawa::operator=(KasiTomoPiNimiWawa&& ante) noexcept {
        if (this != &ante)
            this->ijoPiNimiWawa = std::move(ante.ijoPiNimiWawa);

        return *this;
    }

    KasiTomoPiNimiWawa::KasiTomoPiNimiWawa(const KasiTomoPiNimiWawa& ante) {
        for (const auto& kasi : ante.ijoPiNimiWawa)
            this->ijoPiNimiWawa.push_back(
                    std::unique_ptr<KasiLipu>(kasi->paliSama()));
    }



    KasiPiNimiWawa::KasiPiNimiWawa(const NimiWawa* nimiWawa) 
        : nimiWawa(nimiWawa) {}

    KasiPiNimiWawa* KasiPiNimiWawa::paliSama() const {
        return new KasiPiNimiWawa(*this);
    }

    KasiPiNimiWawa::KasiPiNimiWawa(KasiPiNimiWawa&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPiNimiWawa& KasiPiNimiWawa::operator=(KasiPiNimiWawa&& ante) noexcept {
        if (this != &ante) {
            this->nimiWawa = ante.nimiWawa;
            ante.nimiWawa = nullptr;
        }

        return *this;
    }

    std::string KasiPiNimiWawa::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.nimi_wawa";
    }

    const TomoPiNimiWawa* KasiPiNimiWawa::tomoPiNimiWawa() const {
        return this->nimiWawa;
    }

    KasiPiNimiWawa::KasiPiNimiWawa(const KasiPiNimiWawa& ante) {
        this->nimiWawa = ante.nimiWawa;
    }



    KasiPiNimiWawaTawa::KasiPiNimiWawaTawa(const NimiWawaTawa* nimiWawaTawa) {
        this->nimiWawaTawa = nimiWawaTawa;
    }

    KasiPiNimiWawaTawa* KasiPiNimiWawaTawa::paliSama() const {
        return new KasiPiNimiWawaTawa(*this);
    }

    KasiPiNimiWawaTawa::KasiPiNimiWawaTawa(KasiPiNimiWawaTawa&& ante) noexcept {
        *this = std::move(ante);
    }

    KasiPiNimiWawaTawa& KasiPiNimiWawaTawa::operator=(KasiPiNimiWawaTawa&& ante) noexcept {
        if (this != &ante) {
            this->nimiWawaTawa = ante.nimiWawaTawa;
            ante.nimiWawaTawa  = nullptr;

            this->lonTawaTawa = ante.lonTawaTawa;
            ante.lonTawaTawa  = static_cast<size_t>(-1);
        }

        return *this;
    }

    std::string KasiPiNimiWawaTawa::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.nimi_wawa_tawa"; 
    }

    const TomoPiNimiWawa* KasiPiNimiWawaTawa::tomoPiNimiWawa() const {
        return this->nimiWawaTawa;
    }

    KasiPiNimiWawaTawa::KasiPiNimiWawaTawa(const KasiPiNimiWawaTawa& ante) {
        this->nimiWawaTawa = ante.nimiWawaTawa; 
        this->lonTawaTawa  = ante.lonTawaTawa;
    }



    KasiPiPanaLonPoki* KasiPiPanaLonPoki::paliSama() const {
        return new KasiPiPanaLonPoki(*this);
    }

    KasiPiPanaLonPoki::KasiPiPanaLonPoki(KasiPiPanaLonPoki&& ante) noexcept {
        *this = std::move(ante);
    }

	KasiPiPanaLonPoki& KasiPiPanaLonPoki::operator=(KasiPiPanaLonPoki&& ante) noexcept {
        if (this != &ante) {
            this->nimiPoki = std::move(ante.nimiPoki);
            this->ijoPana  = std::move(ante.ijoPana);
        }

        return *this;
    }

    std::string KasiPiPanaLonPoki::nimiPiNimiKasi() const {
        return "toki.nimi_kasi.pana_lon_poki";
    }

    KasiPiPanaLonPoki::KasiPiPanaLonPoki(const KasiPiPanaLonPoki& ante) {
        this->nimiPoki = ante.nimiPoki;
        this->ijoPana  = std::unique_ptr<KasiLipu>(ante.ijoPana->paliSama());
    }
}