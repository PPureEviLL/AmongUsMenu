#include "gui-helpers.hpp"

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto leftArrow = "##" + std::string(label) + "Left";
	auto rightArrow = "##" + std::string(label) + "Right";

	ImGuiStyle& style = ImGui::GetStyle();
	float w = ImGui::CalcItemWidth();
	float spacing = style.ItemInnerSpacing.x;
	float button_sz = ImGui::GetFrameHeight();
	ImGui::PushItemWidth(width);
	const bool response = ImGui::BeginCombo(comboLabel.c_str(), list.at(*value), ImGuiComboFlags_NoArrowButton | flags);
	if (response) {
		for (size_t i = 0; i < list.size(); i++) {
			bool is_selected = (*value == i);
			if (ImGui::Selectable(list.at(i), is_selected))
				*value = i;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PopItemWidth();
	ImGui::SameLine(0, spacing);

	const bool LeftResponse = ImGui::ArrowButton(leftArrow.c_str(), ImGuiDir_Left);
	if (LeftResponse) {
		*value -= 1;
		if (*value < 0) *value = (list.size() - 1);
		return LeftResponse;
	}
	ImGui::SameLine(0, spacing);
	const bool RightResponse = ImGui::ArrowButton(rightArrow.c_str(), ImGuiDir_Right);
	if (RightResponse) {
		*value += 1;
		if (*value > (int)(list.size() - 1)) *value = 0;
		return RightResponse;
	}
	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	ImGui::Text(label);

	return response;
}

bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
	char text_buf[64] = {};
	ImFormatString(text_buf, IM_ARRAYSIZE(text_buf), format, *v);

	const int stepCount = int((v_max - v_min) / v_step);
	int v_i = int((*v - v_min) / v_step);
	const bool valueChanged = ImGui::SliderInt(label, &v_i, 0, stepCount, text_buf);

	*v = v_min + float(v_i) * v_step;
	return valueChanged;
}

void hotkey(uint8_t & key)
{
	ImGui::Text((std::string("[ ") + virtualKeyToString(key) + std::string(" ]")).c_str());

	if (!ImGui::IsItemHovered())
		return;

	ImGui::SetTooltip("Press any key to change keybind");
	ImGuiIO& io = ImGui::GetIO();
	for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++)
		if (ImGui::IsKeyPressed(i))
			key = i != VK_ESCAPE ? i : 0;

	for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
		if (ImGui::IsMouseDown(i))
			key = i + (i > 1 ? 2 : 1);
}

const std::vector<std::pair<std::string, uint8_t>> keyMap = {
	{ "0", '0' },
	{ "1", '1' },
	{ "2", '2' },
	{ "3", '3' },
	{ "4", '4' },
	{ "5", '5' },
	{ "6", '6' },
	{ "7", '7' },
	{ "8", '8' },
	{ "9", '9' },
	{ "A", 'A' },
	{ "ADD", VK_ADD },
	{ "B", 'B' },
	{ "C", 'C' },
	{ "D", 'D' },
	{ "DECIMAL", VK_DECIMAL },
	{ "DIVIDE", VK_DIVIDE },
	{ "E", 'E' },
	{ "E", VK_END },
	{ "F", 'F' },
	{ "F1", VK_F1 },
	{ "F10", VK_F10 },
	{ "F11", VK_F11 },
	{ "F12", VK_F12 },
	{ "F2", VK_F2 },
	{ "F3", VK_F3 },
	{ "F4", VK_F4 },
	{ "F5", VK_F5 },
	{ "F6", VK_F6 },
	{ "F7", VK_F7 },
	{ "F8", VK_F8 },
	{ "F9", VK_F9 },
	{ "G", 'G' },
	{ "H", 'H' },
	{ "I", 'I' },
	{ "INSERT", VK_INSERT },
	{ "J", 'J' },
	{ "K", 'K' },
	{ "L", 'L' },
	{ "M", 'M' },
	{ "MOUSE1", VK_LBUTTON },
	{ "MOUSE2", VK_RBUTTON },
	{ "MOUSE3", VK_MBUTTON },
	{ "MOUSE4", VK_XBUTTON1 },
	{ "MOUSE5", VK_XBUTTON2 },
	{ "MULTIPLY", VK_MULTIPLY },
	{ "N", 'N' },
	{ "NONE", 0x00 },
	{ "NUMPAD_0", VK_NUMPAD0 },
	{ "NUMPAD_1", VK_NUMPAD1 },
	{ "NUMPAD_2", VK_NUMPAD2 },
	{ "NUMPAD_3", VK_NUMPAD3 },
	{ "NUMPAD_4", VK_NUMPAD4 },
	{ "NUMPAD_5", VK_NUMPAD5 },
	{ "NUMPAD_6", VK_NUMPAD6 },
	{ "NUMPAD_7", VK_NUMPAD7 },
	{ "NUMPAD_8", VK_NUMPAD8 },
	{ "NUMPAD_9", VK_NUMPAD9 },
	{ "O", 'O' },
	{ "P", 'P' },
	{ "Q", 'Q' },
	{ "R", 'R' },
	{ "S", 'S' },
	{ "SPACE", VK_SPACE },
	{ "SUBTRACT", VK_SUBTRACT },
	{ "T", 'T' },
	{ "U", 'U' },
	{ "V", 'V' },
	{ "W", 'W' },
	{ "X", 'X' },
	{ "Y", 'Y' },
	{ "Z", 'Z' },
	{ "`", VK_OEM_3 },
};

std::string virtualKeyToString(uint8_t vk) {
	for (std::pair<std::string, int> key : keyMap) {
		if (vk == key.second) {
			return key.first;
		}
	}
	return "NONE";
}