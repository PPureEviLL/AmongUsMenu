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
	if (j_object.contains("ShowMenu_Hotkey"))
		Settings::Shortcuts[0].Combo.Keys = j_object["ShowMenu_Hotkey"].get<uint32_t>();

	if (j_object.contains("SelectedColor_x"))
		Settings::SelectedColor.x = j_object["SelectedColor_x"].get<float>();
	if (j_object.contains("SelectedColor_y"))
		Settings::SelectedColor.y = j_object["SelectedColor_y"].get<float>();
	if (j_object.contains("SelectedColor_z"))
		Settings::SelectedColor.z = j_object["SelectedColor_z"].get<float>();
	if (j_object.contains("ShowGhosts"))
		Settings::ShowGhosts = j_object["ShowGhosts"].get<bool>();
	if (j_object.contains("ShowRadar"))
		Settings::ShowRadar = j_object["ShowRadar"].get<bool>();
	if (j_object.contains("ShowRadar_Hotkey"))
		Settings::Shortcuts[1].Combo.Keys = j_object["ShowRadar_Hotkey"].get<uint32_t>();
	if (j_object.contains("ShowRadar_DeadBodies"))
		Settings::ShowRadar_DeadBodies = j_object["ShowRadar_DeadBodies"].get<bool>();
	if (j_object.contains("ShowRadar_Ghosts"))
		Settings::ShowRadar_Ghosts = j_object["ShowRadar_Ghosts"].get<bool>();
	if (j_object.contains("HideRadar_During_Meetings"))
		Settings::HideRadar_During_Meetings = j_object["HideRadar_During_Meetings"].get<bool>();
	if (j_object.contains("LockRadar"))
		Settings::LockRadar = j_object["LockRadar"].get<bool>();
	if (j_object.contains("ShowRadar_RightClick_Teleport"))
		Settings::ShowRadar_RightClick_Teleport = j_object["ShowRadar_RightClick_Teleport"].get<bool>();
	if (j_object.contains("Radar_Opacity"))
		Settings::SelectedColor.w = j_object["Radar_Opacity"].get<float>();

	if (j_object.contains("RepairSabotage_Hotkey"))
		Settings::Shortcuts[3].Combo.Keys = j_object["RepairSabotage_Hotkey"].get<uint32_t>();

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
	if (j_object.contains("Console_Hotkey"))
		Settings::Shortcuts[2].Combo.Keys = j_object["Console_Hotkey"].get<uint32_t>();

#ifdef _DEBUG
	if (j_object.contains("showDebugTab"))
		Settings::showDebugTab = j_object["showDebugTab"].get<uint32_t>();
#endif
}

void Settings::Save() {
	json j_object = json{
		{"ShowMenu", Settings::ShowMenu},
		{"ShowMenu_Hotkey", Settings::Shortcuts[0].Combo.Keys},
#ifdef _DEBUG
		{"showDebugTab", Settings::showDebugTab},
#endif
		{"SelectedColor_x", Settings::SelectedColor.x},
		{"SelectedColor_y", Settings::SelectedColor.y},
		{"SelectedColor_z", Settings::SelectedColor.z},

		{"ShowGhosts", Settings::ShowGhosts},
		{"ShowRadar", Settings::ShowRadar},
		{"ShowRadar_Hotkey", Settings::Shortcuts[1].Combo.Keys},
		{"ShowRadar_DeadBodies", Settings::ShowRadar_DeadBodies},
		{"ShowRadar_Ghosts", Settings::ShowRadar_Ghosts},
		{"HideRadar_During_Meetings", Settings::HideRadar_During_Meetings},
		{"LockRadar", Settings::LockRadar},
		{"ShowRadar_RightClick_Teleport", Settings::ShowRadar_RightClick_Teleport},
		{"Radar_Opacity", Settings::SelectedColor.w},

		{"RepairSabotage_Hotkey", Settings::Shortcuts[3].Combo.Keys},

		{"MaxVision", Settings::MaxVision},
		{"Wallhack", Settings::Wallhack},
		{"UnlockVents", Settings::UnlockVents},
		{"RevealImpostors", Settings::RevealImpostors},
		{"ChatAlwaysActive", Settings::ChatAlwaysActive},
		{"ReadGhostMessages", Settings::ReadGhostMessages},

		{"ShowConsole", Settings::ShowConsole},
		{"Console_Hotkey", Settings::Shortcuts[2].Combo.Keys}
	};

	std::ofstream outSettings(pSettings);
	outSettings << std::setw(4) << j_object << std::endl;
}