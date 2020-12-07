#include "state.hpp"

Settings State;

const char* pSettings = "settings.json";

inline bool Settings::Exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void Settings::Load() {
	if (!Settings::Exists(pSettings))
		return;

	std::ifstream inSettings(pSettings);
	json j_object = json::parse(inSettings, nullptr, false);

	if (j_object.contains("ShowMenu"))
		Settings::ShowMenu = j_object["ShowMenu"].get<bool>();
	if (j_object.contains("KeyBinds"))
		Settings::KeyBinds = KeyBindsTest::fromJson(j_object["KeyBinds"].get<json>());

	if (j_object.contains("ShowRadar"))
		Settings::ShowRadar = j_object["ShowRadar"].get<bool>();
	if (j_object.contains("ShowRadar_DeadBodies"))
		Settings::ShowRadar_DeadBodies = j_object["ShowRadar_DeadBodies"].get<bool>();
	if (j_object.contains("ShowRadar_Ghosts"))
		Settings::ShowRadar_Ghosts = j_object["ShowRadar_Ghosts"].get<bool>();
	if (j_object.contains("ShowRadar_RightClick_Teleport"))
		Settings::ShowRadar_RightClick_Teleport = j_object["ShowRadar_RightClick_Teleport"].get<bool>();

	if (j_object.contains("MaxVision"))
		Settings::MaxVision = j_object["MaxVision"].get<bool>();
	if (j_object.contains("Wallhack"))
		Settings::Wallhack = j_object["Wallhack"].get<bool>();
	if (j_object.contains("UnlockVents"))
		Settings::UnlockVents = j_object["UnlockVents"].get<bool>();
	if (j_object.contains("RevealImpostors"))
		Settings::RevealImpostors = j_object["RevealImpostors"].get<bool>();
	if (j_object.contains("ChatAlwaysActive"))
		Settings::ChatAlwaysActive = j_object["ChatAlwaysActive"].get<bool>();
	if (j_object.contains("ReadGhostMessages"))
		Settings::ReadGhostMessages = j_object["ReadGhostMessages"].get<bool>();

	if (j_object.contains("ShowConsole"))
		Settings::ShowConsole = j_object["ShowConsole"].get<bool>();


#ifdef _DEBUG
	if (j_object.contains("showDebugTab"))
		Settings::showDebugTab = j_object["showDebugTab"].get<uint32_t>();
#endif
}

void Settings::Save() {
	json j_object = json{
		{"ShowMenu", Settings::ShowMenu},
#ifdef _DEBUG
		{"showDebugTab", Settings::showDebugTab},
#endif

		{"ShowRadar", Settings::ShowRadar},
		{"ShowRadar_DeadBodies", Settings::ShowRadar_DeadBodies},
		{"ShowRadar_Ghosts", Settings::ShowRadar_Ghosts},
		{"ShowRadar_RightClick_Teleport", Settings::ShowRadar_RightClick_Teleport},
		{"KeyBinds", KeyBindsTest::toJson(Settings::KeyBinds) },
		{"MaxVision", Settings::MaxVision},
		{"Wallhack", Settings::Wallhack},
		{"UnlockVents", Settings::UnlockVents},
		{"RevealImpostors", Settings::RevealImpostors},
		{"ChatAlwaysActive", Settings::ChatAlwaysActive},
		{"ReadGhostMessages", Settings::ReadGhostMessages},

		{"ShowConsole", Settings::ShowConsole},
	};

	std::ofstream outSettings(pSettings);
	outSettings << std::setw(4) << j_object << std::endl;
}