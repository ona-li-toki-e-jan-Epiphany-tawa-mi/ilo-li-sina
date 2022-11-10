#include "ike.hpp"
#include <optional>
#include "../ante_toki/ante_toki.hpp"
#include "toki.hpp"

namespace kepeken {
	std::optional<std::string> nimiPiILO_LI_SINA = std::nullopt;

	void anteENimiPiILO_LI_SINA(const std::string& nimi) {
		nimiPiILO_LI_SINA = nimi;
	}
	
	const std::string& kamaJoENimiPiILO_LI_SINA() noexcept(false) {
		if (nimiPiILO_LI_SINA.has_value())
			return *nimiPiILO_LI_SINA;

		throw std::logic_error("poki pi nimi pi ilo Ilo Li Sina li jo ala e nimi. o kepeken e void(anteENimiPiILO_LI_SINA)(const std::string&) lon tenpo 1 o kepeken e ni lon tenpo 2");
	}



	IjoPiTokiIke::IjoPiTokiIke(const std::string& nimiIke)
			: nimiPiLipuWawa(nullptr), lonIjo(nullptr), nimiIke(nimiIke) {}

	IjoPiTokiIke::IjoPiTokiIke(const std::string& nimiPiLipuWawa, const std::string& nimiIke)
			: nimiPiLipuWawa(std::make_unique<std::string>(nimiPiLipuWawa)), lonIjo(nullptr), 
			nimiIke(nimiIke) {}

	IjoPiTokiIke::IjoPiTokiIke(const std::string& nimiPiLipuWawa, const size_t nanpaLinja, const size_t nanpaSitelenLonLinja, const std::string& nimiIke)
			: nimiPiLipuWawa(std::make_unique<std::string>(nimiPiLipuWawa)), 
			lonIjo(std::make_unique<LonIjo>(LonIjo{nanpaLinja, nanpaSitelenLonLinja})), 
			nimiIke(nimiIke) {}

	IjoPiTokiIke::IjoPiTokiIke(const std::string& nimiPiLipuWawa, const LonIjo& lonIjo, const std::string& nimiIke)
			: nimiPiLipuWawa(std::make_unique<std::string>(nimiPiLipuWawa)), 
			lonIjo(std::make_unique<LonIjo>(lonIjo)),
			nimiIke(nimiIke) {}

	IjoPiTokiIke::IjoPiTokiIke(const std::string& nimiPiLipuWawa, const LonIjo *const lonIjo, const std::string& nimiIke)
			: nimiPiLipuWawa(std::make_unique<std::string>(nimiPiLipuWawa)), 
			lonIjo(lonIjo != nullptr ? std::make_unique<LonIjo>(*lonIjo) : nullptr),
			nimiIke(nimiIke) {}
	
	const std::string* IjoPiTokiIke::kamaJoENimiPiLipuWawa() const {
		return this->nimiPiLipuWawa.get();
	}
	
	const LonIjo* IjoPiTokiIke::kamaJoELonIjo() const {
		return this->lonIjo.get();
	}
	
	const std::string& IjoPiTokiIke::kamaJoENimiIke() const {
		return this->nimiIke;
	}



	void tokiEIke(const IjoPiTokiIke& ike) {
		std::string ikePini(kamaJoENimiPiILO_LI_SINA());
		ikePini.append(": ");

		if (ike.kamaJoENimiPiLipuWawa() != nullptr) {
			ikePini.append(*ike.kamaJoENimiPiLipuWawa());

			if (ike.kamaJoELonIjo() != nullptr) {
				const auto [linja, sitelen] = *ike.kamaJoELonIjo();
				ikePini.append(1, '(').append(std::to_string(linja)).append(1, ',')
					.append(std::to_string(sitelen)).append(1, ')');
			}

			ikePini.append(": ");
		}

		ikePini.append(ante_toki::nimiTawaJan("ike.nimi")).append(": ")
			.append(ike.kamaJoENimiIke());


		tokiELinjaPiLukinPona(std::cerr, ikePini, 0, 8);
	}
}