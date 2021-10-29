#pragma once

#include <imgui.h>

class Widgets
{
	static inline const char* const keyNames[] = {
		"Unknown",
		"VK_LBUTTON",
		"VK_RBUTTON",
		"VK_CANCEL",
		"VK_MBUTTON",
		"VK_XBUTTON1",
		"VK_XBUTTON2",
		"Unknown",
		"VK_BACK",
		"VK_TAB",
		"Unknown",
		"Unknown",
		"VK_CLEAR",
		"VK_RETURN",
		"Unknown",
		"Unknown",
		"VK_SHIFT",
		"VK_CONTROL",
		"VK_MENU",
		"VK_PAUSE",
		"VK_CAPITAL",
		"VK_KANA",
		"Unknown",
		"VK_JUNJA",
		"VK_FINAL",
		"VK_KANJI",
		"Unknown",
		"VK_ESCAPE",
		"VK_CONVERT",
		"VK_NONCONVERT",
		"VK_ACCEPT",
		"VK_MODECHANGE",
		"VK_SPACE",
		"VK_PRIOR",
		"VK_NEXT",
		"VK_END",
		"VK_HOME",
		"VK_LEFT",
		"VK_UP",
		"VK_RIGHT",
		"VK_DOWN",
		"VK_SELECT",
		"VK_PRINT",
		"VK_EXECUTE",
		"VK_SNAPSHOT",
		"VK_INSERT",
		"VK_DELETE",
		"VK_HELP",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"VK_LWIN",
		"VK_RWIN",
		"VK_APPS",
		"Unknown",
		"VK_SLEEP",
		"VK_NUMPAD0",
		"VK_NUMPAD1",
		"VK_NUMPAD2",
		"VK_NUMPAD3",
		"VK_NUMPAD4",
		"VK_NUMPAD5",
		"VK_NUMPAD6",
		"VK_NUMPAD7",
		"VK_NUMPAD8",
		"VK_NUMPAD9",
		"VK_MULTIPLY",
		"VK_ADD",
		"VK_SEPARATOR",
		"VK_SUBTRACT",
		"VK_DECIMAL",
		"VK_DIVIDE",
		"VK_F1",
		"VK_F2",
		"VK_F3",
		"VK_F4",
		"VK_F5",
		"VK_F6",
		"VK_F7",
		"VK_F8",
		"VK_F9",
		"VK_F10",
		"VK_F11",
		"VK_F12",
		"VK_F13",
		"VK_F14",
		"VK_F15",
		"VK_F16",
		"VK_F17",
		"VK_F18",
		"VK_F19",
		"VK_F20",
		"VK_F21",
		"VK_F22",
		"VK_F23",
		"VK_F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"VK_NUMLOCK",
		"VK_SCROLL",
		"VK_OEM_NEC_EQUAL",
		"VK_OEM_FJ_MASSHOU",
		"VK_OEM_FJ_TOUROKU",
		"VK_OEM_FJ_LOYA",
		"VK_OEM_FJ_ROYA",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"VK_LSHIFT",
		"VK_RSHIFT",
		"VK_LCONTROL",
		"VK_RCONTROL",
		"VK_LMENU",
		"VK_RMENU"
	};

	static const char* patchFormatStringFloatToInt(const char* fmt);
	static inline int stepInt = 1;
	static inline int stepFastInt = 10;
	static inline float stepFloat = 0.1f;
	static inline float stepFastFloat = 1.f;
public:
	static bool Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size_arg = ImVec2(0, 0));
	static bool Tab(const char* label, void* icon, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg);
	static float CalcPanelHeight(int widgetCount, int textCount = 0, int spacingCount = 0);
	static void BeginPanel(const char* label, const ImVec2& size);
	static void EndPanel();
	static bool Checkbox(const char* label, bool* v);
	static bool ButtonEx(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags);
	static bool Button(const char* label, const ImVec2& size_arg = ImVec2(0, 0));
	static bool SmallButton(const char* label);
	static bool Hotkey(const char* label, int* k);
	static bool InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
	static bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
	static bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
	static bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
};
