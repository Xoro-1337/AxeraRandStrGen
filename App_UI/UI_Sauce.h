#pragma once
#include "../imgui/imgui_internal.h"
#include <string>
#include <vector>
#include <functional>
#include <random>
#include "../Global_Vars/Global_Vars.h"

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

// Randomize Strings.
std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&()~-_=+[{]{|;:<.>/?" };
std::string chars2{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890" };
std::random_device rd;
std::mt19937 generator(rd());
std::string RandStr(size_t length, bool specialChar)
{
	if (specialChar)
	{
		const size_t char_size = chars.size();
		std::uniform_int_distribution<> random_int(0, char_size - 1);
		std::string output;
		for (size_t i = 0; i < length; ++i)
			output.push_back(chars[random_int(generator)]);
		return output;
	}
	else if (!specialChar)
	{
		const size_t char_size = chars2.size();
		std::uniform_int_distribution<> random_int(0, char_size - 1);
		std::string output;
		for (size_t i = 0; i < length; ++i)
			output.push_back(chars[random_int(generator)]);
		return output;
	}
}

namespace ImGui
{
	void Line(int newId)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void Linevertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
	}

	void CenterText(const char* text, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			Line(lineId);
	}

	void CenterTextEx(const char* text, float width, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			Line(lineId);
	}

	float GetX()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float GetY()
	{
		return ImGui::GetContentRegionAvail().y;
	} 

	void SubSectionGUITheme()
	{
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowBorderSize = 4;
		Style->FrameBorderSize = 0;
		Style->ChildBorderSize = 4;
		Style->WindowRounding = 0;
		Style->ChildRounding = 0;
		Style->FrameRounding = 0;
		Style->ScrollbarSize = 0;
		Style->WindowPadding = ImVec2(0, 0);
		Style->FramePadding = ImVec2(0, 0);
		Style->ItemSpacing = ImVec2(0, 0);
		Style->ItemInnerSpacing = ImVec2(0, 0);
		Style->IndentSpacing = 0;
		Style->DisplayWindowPadding = ImVec2(0, 0);
		Style->Colors[ImGuiCol_Border] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		//Style->Colors[ImGuiCol_WindowBg] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_CheckMark] = ImColor(15, 110, 15);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 155); // 40, 40, 40, 155
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255);
	}

#pragma region ARSG Gui Setup
	void DisplayTopHeader()
	{
		ImGui::SetCursorPosY(10);
		CenterText("Axera Random String Generator", 1, false);
		ImGui::SetCursorPos(ImVec2(290, 8));
		if (ImGui::Button("Exit", ImVec2(50, 20)))
		{
			exit(0);
		}
	}

	void DisplayGenRandString()
	{
		SubSectionGUITheme();

		if (ImGui::BeginChild("DisplayGenRandString", ImVec2(350, 400), true, ImGuiWindowFlags_NoDecoration))
		{
			ImGui::SetCursorPosY(25);
			CenterText("[ Generate Random Strings ]", 0, false);
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Indent(15);
			ImGui::Text("Number of Strings  [ ");
			ImGui::Unindent(15);
			ImGui::SameLine();
			ImGui::PushItemWidth(50);
			ImGui::InputInt("##InputNumberOfStringsToGenerate", &Global_Vars::iRandStringAmount, 1);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			ImGui::Text(" ]");
			ImGui::Indent(15);
			ImGui::Text("Length of Strings    [ ");
			ImGui::Unindent(15);
			ImGui::SameLine();
			ImGui::PushItemWidth(50);
			ImGui::InputInt("##InputLengthOfStringsToGenerate", &Global_Vars::iRandStringLength, 1);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			ImGui::Text(" ]");
			ImGui::SetCursorPos(ImVec2(210, 80));
			if (ImGui::Button("Generate String(s)", ImVec2(125, 20)))
			{
				Global_Vars::bGenerateStrings = true;
			}
			if (Global_Vars::bGenerateStrings)
			{
				Global_Vars::bStringsGenerated = false;
				ImGui::NewLine();
				ImGui::CenterText("Do you want Special Characters?", 0, false);
				ImGui::Indent(125);
				if (ImGui::Button("Yes", ImVec2(45, 20)))
				{
					Global_Vars::bSpecialCharsSelected = true;
					Global_Vars::bGenerateStrings = false;
					Global_Vars::sRandStringArray.clear();
				}
				ImGui::SameLine();
				ImGui::Text("  ");
				ImGui::SameLine();
				if (ImGui::Button("No", ImVec2(45, 20)))
				{
					Global_Vars::bSpecialCharsNotSelected = true;
					Global_Vars::bGenerateStrings = false;
					Global_Vars::sRandStringArray.clear();
				}
			}
			if (Global_Vars::bSpecialCharsSelected)
			{
				if (!Global_Vars::bStringsGenerated)
				{
					for (int i = 0; i < Global_Vars::iRandStringAmount; i++)
					{
						Global_Vars::sRandStringText = RandStr(Global_Vars::iRandStringLength, true);
						Global_Vars::sRandStringArray.push_back(Global_Vars::sRandStringText);
					}
					Global_Vars::bStringsGenerated = true;
				}
				Global_Vars::bSpecialCharsSelected = false;
			}
			if (Global_Vars::bSpecialCharsNotSelected)
			{
				if (!Global_Vars::bStringsGenerated)
				{
					for (int i = 0; i < Global_Vars::iRandStringAmount; i++)
					{
						Global_Vars::sRandStringText = RandStr(Global_Vars::iRandStringLength, false);
						Global_Vars::sRandStringArray.push_back(Global_Vars::sRandStringText);
					}
					Global_Vars::bStringsGenerated = true;
				}
				Global_Vars::bSpecialCharsNotSelected = false;
			}
			if (Global_Vars::bStringsGenerated)
			{
				ImGui::NewLine();
				ImGui::Indent(125);
				if (ImGui::Button("Copy String(s)", ImVec2(100, 20)))
				{
					Global_Vars::bCopyKeysSelected = true;
				}
				ImGui::Unindent(125);
				ImGui::NewLine();
				if (Global_Vars::bCopyKeysSelected)
				{
					ImGui::LogToClipboard();
					Global_Vars::bCopyKeysSelected = false;
				}
				for (int i = 0; i < Global_Vars::sRandStringArray.size(); i++)
				{
					ImGui::CenterText(Global_Vars::sRandStringArray[i].c_str(), 0, false);
				}
				ImGui::NewLine();
			}
		} ImGui::EndChild();
	}
#pragma endregion
}