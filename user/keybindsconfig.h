#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bitset>
#include <functional>
#include "json.hpp"

#ifndef KEYBINDS_H
#define KEYBINDS_H
namespace KeyBinds
{
	struct KeyBindsConfig {
		uint8_t Toggle_Menu{ VK_DELETE };
		uint8_t Toggle_Radar{ VK_INSERT };
		uint8_t Toggle_Console{ VK_HOME };
		uint8_t Repair_Sabotage{ VK_END };
	};

	enum KeyBindCallBackType {
		None,
		Toggle_Menu,
		Toggle_Radar,
		Toggle_Console,
		Repair_Sabotage
	};

	using json = nlohmann::ordered_json;

	static std::bitset<0xFF> KeyState;

	static void WndProc(UINT uMsg, WPARAM wParam) {
		if (uMsg == WM_KEYDOWN)
			KeyBinds::KeyState[uint8_t(wParam)] = true;

		if (uMsg == WM_KEYUP)
			KeyBinds::KeyState[uint8_t(wParam)] = false;
	}

	static bool CheckKey(uint8_t key) {
		if (key == 0xFF) return true;
		return KeyBinds::KeyState[key];
	}

	static KeyBindsConfig fromJson(json data) {
		KeyBindsConfig config = KeyBindsConfig();
		config.Toggle_Menu = data["Toggle_Menu"].get<uint8_t>();
		config.Toggle_Radar = data["Toggle_Radar"].get<uint8_t>();
		config.Toggle_Console = data["Toggle_Console"].get<uint8_t>();
		config.Repair_Sabotage = data["Repair_Sabotage"].get<uint8_t>();

		return config;
	}

	static json toJson(KeyBindsConfig config) {
		json jsonconfig = json::object();
		jsonconfig["Toggle_Menu"] = config.Toggle_Menu;
		jsonconfig["Toggle_Radar"] = config.Toggle_Radar;
		jsonconfig["Toggle_Console"] = config.Toggle_Console;
		jsonconfig["Repair_Sabotage"] = config.Repair_Sabotage;
		return jsonconfig;
	}

	static KeyBindCallBackType GetKeyBinds(KeyBindsConfig* keybinds) {
		if (CheckKey(keybinds->Toggle_Menu)) return KeyBindCallBackType::Toggle_Menu;
		if (CheckKey(keybinds->Toggle_Radar)) return KeyBindCallBackType::Toggle_Radar;
		if (CheckKey(keybinds->Toggle_Console)) return KeyBindCallBackType::Toggle_Console;
		if (CheckKey(keybinds->Repair_Sabotage)) return KeyBindCallBackType::Repair_Sabotage;

		return KeyBindCallBackType::None;
	}
}
#endif