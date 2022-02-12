#include "Config.h"

#include <filesystem>
#include <fstream>

#include <ThemidaSDK.h>

#include "../../Utilities/Security/xorstr.hpp"
#include "../Utilities/Directories/DirectoryHelper.h"

bool Config::isSameName(const std::string& a, const std::string& b)
{
	std::string aLowerCase = a;
	std::string bLowerCase = b;
	std::transform(aLowerCase.begin(), aLowerCase.end(), aLowerCase.begin(), tolower);
	std::transform(bLowerCase.begin(), bLowerCase.end(), bLowerCase.begin(), tolower);

	return aLowerCase == bLowerCase;
}

bool Config::isValidName(std::string name)
{
	return !name.empty() && !isSameName(name, xor ("default"));
}

ImVec4 Config::parseImVec4(std::string vec)
{
	float result[4];
	int pos = 0;
	int index = 0;
	while ((pos = vec.find(',')) != std::string::npos)
	{
		result[index] = std::stof(vec.substr(0, pos));
		vec.erase(0, pos + 1);

		index++;
	}

	result[3] = std::stof(vec);

	return ImVec4(result[0], result[1], result[2], result[3]);
}

void Config::loadDefaults()
{
	STR_ENCRYPT_START
	
	Relax::Enabled = false;
	Relax::Distribution = 1;
	Relax::Playstyle = 0;
	Relax::PrimaryKey = 1;
	Relax::SecondaryKey = 3;
	Relax::MaxSingletapBPM = 100;
	Relax::HitSpread = 70;
	Relax::AlternationHitSpread = 90;
	Relax::HoldConsecutiveSpinners = false;
	Relax::SliderAlternationOverride = false;
	Relax::PredictionEnabled = false;
	Relax::SliderPredictionEnabled = false;
	Relax::PredictionAngle = 45;
	Relax::PredictionScale = 0.8f;
	Relax::UseLowestPossibleHoldTimes = false;

	AimAssist::Enabled = false;
	AimAssist::Algorithm = 0;
	AimAssist::EasyMode = true;
	AimAssist::EasyModeStrength = 0.5f;
	AimAssist::Strength = 0.6f;
	AimAssist::BaseFOV = 45;
	AimAssist::MaximumFOVScale = 2.5f;
	AimAssist::MinimumFOVTotal = 0.f;
	AimAssist::MaximumFOVTotal = 225.f;
	AimAssist::SliderballDeadzone = 12.5f;
	AimAssist::FlipSliderballDeadzone = true;
	AimAssist::AssistOnSliders = true;
	AimAssist::StrengthMultiplier = 1.f;
	AimAssist::AssistDeadzone = 3.f;
	AimAssist::ResyncLeniency = 3.5f;
	AimAssist::ResyncLeniencyFactor = 0.698f;
	AimAssist::DrawDebugOverlay = false;
	AimAssist::Algorithmv2Power = 0.5f;
	AimAssist::Algorithmv2AssistOnSliders = true;
	AimAssist::Algorithmv3Strength = 0.6f;
	AimAssist::Algorithmv3AssistOnSliders = true;
	AimAssist::Algorithmv3BaseFOV = 45;
	AimAssist::Algorithmv3MaximumFOVScale = 2.5f;
	AimAssist::Algorithmv3MinimumFOVTotal = 0.f;
	AimAssist::Algorithmv3MaximumFOVTotal = 225.f;
	AimAssist::Algorithmv3AccelerationFactor = 1.f;

	Timewarp::Enabled = false;
	Timewarp::Type = 0;
	Timewarp::Rate = 100;
	Timewarp::Multiplier = 1.;

	Visuals::ARChangerEnabled = false;
	Visuals::AR = 9.2f;
	Visuals::ARChangerAdjustToMods = false;
	Visuals::ARChangerAdjustToRate = false;
	Visuals::ARChangerDrawPreemptiveDot = false;
	Visuals::ARChangerPreemptiveDotColour = ImColor(232, 93, 155, 255).Value;
	Visuals::CSChangerEnabled = false;
	Visuals::CS = 4.2f;
	Visuals::HiddenDisabled = false;
	Visuals::FlashlightDisabled = false;
	Visuals::MenuScale = 2;
	Visuals::MenuBackground[0] = '\0';
	Visuals::AccentColour = ImColor(232, 93, 155, 255).Value;
	Visuals::MenuColour = ImColor(65, 65, 65, 255).Value;
	Visuals::ControlColour = ImColor(76, 76, 76, 255).Value;
	Visuals::TextColour = ImVec4(ImColor(255, 255, 255, 255));

	Misc::DisableSpectators = false;
	Misc::PromptOnScoreSubmissionEnabled = false;
	Misc::DisableLogging = false;
	Misc::RichPresenceSpooferEnabled = false;
	strcpy_s(Misc::SpoofedName, xor ("maple.software"));
	strcpy_s(Misc::SpoofedRank, xor("rocking osu! since 2021"));

	STR_ENCRYPT_END
}

void Config::Initialize()
{
	Refresh();

	const auto it = std::find(Configs.begin(), Configs.end(), DirectoryHelper::DefaultConfig);

	if (it != Configs.end())
		CurrentConfig = std::distance(Configs.begin(), it);
	else
		CurrentConfig = 0;

	Load();
}

void Config::Load()
{
	STR_ENCRYPT_START
	
	DirectoryHelper::EnsureDirectoriesExist();
	loadDefaults(); //load default config first to ensure that old configs are fully initialized

	DirectoryHelper::DefaultConfig = Configs[CurrentConfig];
	DirectoryHelper::SaveConfig();

	if (CurrentConfig == 0)
		return;

	std::ifstream file(DirectoryHelper::ConfigsDirectory + "\\" + Configs[CurrentConfig] + ".cfg");
	std::string line;

	while (std::getline(file, line))
	{
		const int delimiterIndex = line.find('=');
		std::string variable = line.substr(0, delimiterIndex);
		std::string value = line.substr(delimiterIndex + 1, std::string::npos);

		if (variable == "RelaxEnabled")
			Relax::Enabled = value == "1";
		if (variable == "RelaxDistribution")
			Relax::Distribution = std::stoi(value);
		if (variable == "RelaxPlaystyle")
			Relax::Playstyle = std::stoi(value);
		if (variable == "RelaxPrimaryKey")
			Relax::PrimaryKey = std::stoi(value);
		if (variable == "RelaxSecondaryKey")
			Relax::SecondaryKey = std::stoi(value);
		if (variable == "RelaxMaxSingletapBPM")
			Relax::MaxSingletapBPM = std::stoi(value);
		if (variable == "RelaxHitSpread")
			Relax::HitSpread = std::stoi(value);
		if (variable == "RelaxAlternationHitSpread")
			Relax::AlternationHitSpread = std::stoi(value);
		if (variable == "RelaxHoldConsecutiveSpinners")
			Relax::HoldConsecutiveSpinners = value == "1";
		if (variable == "RelaxSliderAlternationOverride")
			Relax::SliderAlternationOverride = value == "1";
		if (variable == "RelaxPredictionEnabled")
			Relax::PredictionEnabled = value == "1";
		if (variable == "RelaxSliderPredictionEnabled")
			Relax::SliderPredictionEnabled = value == "1";
		if (variable == "RelaxPredictionAngle")
			Relax::PredictionAngle = std::stoi(value);
		if (variable == "RelaxPredictionScale")
			Relax::PredictionScale = std::stof(value);
		if (variable == "RelaxUseLowestPossibleHoldTimes")
			Relax::UseLowestPossibleHoldTimes = value == "1";

		if (variable == "AimAssistEnabled")
			AimAssist::Enabled = value == "1";
		if (variable == "AimAssistAlgorithm")
			AimAssist::Algorithm = std::stoi(value);
		if (variable == "AimAssistEasyMode")
			AimAssist::EasyMode = value == "1";
		if (variable == "AimAssistEasyModeStrength")
			AimAssist::EasyModeStrength = std::stof(value);
		if (variable == "AimAssistStrength")
			AimAssist::Strength = std::stof(value);
		if (variable == "AimAssistBaseFOV")
			AimAssist::BaseFOV = std::stoi(value);
		if (variable == "AimAssistMaximumFOVScale")
			AimAssist::MaximumFOVScale = std::stof(value);
		if (variable == "AimAssistMinimumFOVTotal")
			AimAssist::MinimumFOVTotal = std::stof(value);
		if (variable == "AimAssistMaximumFOVTotal")
			AimAssist::MaximumFOVTotal = std::stof(value);
		if (variable == "AimAssistAssistOnSliders")
			AimAssist::AssistOnSliders = value == "1";
		if (variable == "AimAssistStrengthMultiplier")
			AimAssist::StrengthMultiplier = std::stof(value);
		if (variable == "AimAssistAssistDeadzone")
			AimAssist::AssistDeadzone = std::stof(value);
		if (variable == "AimAssistResyncLeniency")
			AimAssist::ResyncLeniency = std::stof(value);
		if (variable == "AimAssistResyncLeniencyFactor")
			AimAssist::ResyncLeniencyFactor = std::stof(value);
		if (variable == "AimAssistDrawDebugOverlay")
			AimAssist::DrawDebugOverlay = value == "1";
		if (variable == "AimAssistFlipSliderballDeadzone")
			AimAssist::FlipSliderballDeadzone = value == "1";
		if (variable == "AimAssistSliderballDeadzone")
			AimAssist::SliderballDeadzone = std::stof(value);
		if (variable == "AimAssistAlgorithmv2Power")
			AimAssist::Algorithmv2Power = std::stof(value);
		if (variable == "AimAssistAlgorithmv2AssistOnSliders")
			AimAssist::Algorithmv2AssistOnSliders = value == "1";
		if (variable == "AimAssistAlgorithmv3Strength")
			AimAssist::Algorithmv3Strength = std::stof(value);
		if (variable == "AimAssistAlgorithmv3AssistOnSliders")
			AimAssist::Algorithmv3AssistOnSliders = value == "1";
		if (variable == "AimAssistAlgorithmv3BaseFOV")
			AimAssist::Algorithmv3BaseFOV = std::stoi(value);
		if (variable == "AimAssistAlgorithmv3MaximumFOVScale")
			AimAssist::Algorithmv3MaximumFOVScale = std::stof(value);
		if (variable == "AimAssistAlgorithmv3MinimumFOVTotal")
			AimAssist::Algorithmv3MinimumFOVTotal = std::stof(value);
		if (variable == "AimAssistAlgorithmv3MaximumFOVTotal")
			AimAssist::Algorithmv3MaximumFOVTotal = std::stof(value);
		if (variable == "AimAssistAlgorithmv3AccelerationFactor")
			AimAssist::Algorithmv3AccelerationFactor = std::stof(value);

		if (variable == "TimewarpEnabled")
			Timewarp::Enabled = value == "1";
		if (variable == "TimewarpType")
			Timewarp::Type = std::stoi(value);
		if (variable == "TimewarpRate")
			Timewarp::Rate = std::stoi(value);
		if (variable == "TimewarpMultiplier")
			Timewarp::Multiplier = std::stof(value);

		if (variable == "VisualsARChangerEnabled")
			Visuals::ARChangerEnabled = value == "1";
		if (variable == "VisualsARChangerAR")
			Visuals::AR = std::stof(value);
		if (variable == "VisualsAdjustToMods")
			Visuals::ARChangerAdjustToMods = value == "1";
		if (variable == "VisualsAdjustToRate")
			Visuals::ARChangerAdjustToRate = value == "1";
		if (variable == "VisualsDrawPreemptiveDot")
			Visuals::ARChangerDrawPreemptiveDot = value == "1";
		if (variable == "VisualsPreemptiveDotColour")
			Visuals::ARChangerPreemptiveDotColour = parseImVec4(value);
		if (variable == "VisualsCSChangerEnabled")
			Visuals::CSChangerEnabled = value == "1";
		if (variable == "VisualsCSChangerCS")
			Visuals::CS = std::stof(value);
		if (variable == "VisualsHiddenDisabled")
			Visuals::HiddenDisabled = value == "1";
		if (variable == "VisualsFlashlightDisabled")
			Visuals::FlashlightDisabled = value == "1";
		if (variable == "VisualsMenuScale")
			Visuals::MenuScale = std::stoi(value);
		if (variable == "VisualsMenuBackground")
			strcpy_s(Visuals::MenuBackground, value.c_str());
		if (variable == "VisualsAccentColour")
			Visuals::AccentColour = parseImVec4(value);
		if (variable == "VisualsMenuColour")
			Visuals::MenuColour = parseImVec4(value);
		if (variable == "VisualsControlColour")
			Visuals::ControlColour = parseImVec4(value);
		if (variable == "VisualsTextColour")
			Visuals::TextColour = parseImVec4(value);

		if (variable == "MiscDisableSpectators")
			Misc::DisableSpectators = value == "1";
		if (variable == "MiscPromptOnScoreSubmissionEnabled")
			Misc::PromptOnScoreSubmissionEnabled = value == "1";
		if (variable == "MiscDisableLogging")
			Misc::DisableLogging = value == "1";
		if (variable == "MiscRichPresenceSpooferEnabled")
			Misc::RichPresenceSpooferEnabled = value == "1";
		if (variable == "MiscSpoofedName")
			strcpy_s(Misc::SpoofedName, value.c_str());
		if (variable == "MiscSpoofedRank")
			strcpy_s(Misc::SpoofedRank, value.c_str());
	}

	file.close();

	STR_ENCRYPT_END
}

void Config::Save()
{
	STR_ENCRYPT_START
	
	if (CurrentConfig == 0)
		return;

	DirectoryHelper::EnsureDirectoriesExist();

	const std::string cfgPath = DirectoryHelper::ConfigsDirectory + "\\" + Configs[CurrentConfig] + ".cfg";

	std::ofstream ofs;
	ofs.open(cfgPath, std::ofstream::out | std::ofstream::trunc);

	ofs << "RelaxEnabled=" << Relax::Enabled << std::endl;
	ofs << "RelaxDistribution=" << Relax::Distribution << std::endl;
	ofs << "RelaxPlaystyle=" << Relax::Playstyle << std::endl;
	ofs << "RelaxPrimaryKey=" << Relax::PrimaryKey << std::endl;
	ofs << "RelaxSecondaryKey=" << Relax::SecondaryKey << std::endl;
	ofs << "RelaxMaxSingletapBPM=" << Relax::MaxSingletapBPM << std::endl;
	ofs << "RelaxHitSpread=" << Relax::HitSpread << std::endl;
	ofs << "RelaxAlternationHitSpread=" << Relax::AlternationHitSpread << std::endl;
	ofs << "RelaxHoldConsecutiveSpinners=" << Relax::HoldConsecutiveSpinners << std::endl;
	ofs << "RelaxSliderAlternationOverride=" << Relax::SliderAlternationOverride << std::endl;
	ofs << "RelaxPredictionEnabled=" << Relax::PredictionEnabled << std::endl;
	ofs << "RelaxSliderPredictionEnabled=" << Relax::SliderPredictionEnabled << std::endl;
	ofs << "RelaxPredictionAngle=" << Relax::PredictionAngle << std::endl;
	ofs << "RelaxPredictionScale=" << Relax::PredictionScale << std::endl;
	ofs << "RelaxUseLowestPossibleHoldTimes=" << Relax::UseLowestPossibleHoldTimes << std::endl;

	ofs << "AimAssistEnabled=" << AimAssist::Enabled << std::endl;
	ofs << "AimAssistAlgorithm=" << AimAssist::Algorithm << std::endl;
	ofs << "AimAssistEasyMode=" << AimAssist::EasyMode << std::endl;
	ofs << "AimAssistEasyModeStrength=" << AimAssist::EasyModeStrength << std::endl;
	ofs << "AimAssistStrength=" << AimAssist::Strength << std::endl;
	ofs << "AimAssistBaseFOV=" << AimAssist::BaseFOV << std::endl;
	ofs << "AimAssistMaximumFOVScale=" << AimAssist::MaximumFOVScale << std::endl;
	ofs << "AimAssistMinimumFOVTotal=" << AimAssist::MinimumFOVTotal << std::endl;
	ofs << "AimAssistMaximumFOVTotal=" << AimAssist::MaximumFOVTotal << std::endl;
	ofs << "AimAssistAssistOnSliders=" << AimAssist::AssistOnSliders << std::endl;
	ofs << "AimAssistStrengthMultiplier=" << AimAssist::StrengthMultiplier << std::endl;
	ofs << "AimAssistAssistDeadzone=" << AimAssist::AssistDeadzone << std::endl;
	ofs << "AimAssistResyncLeniency=" << AimAssist::ResyncLeniency << std::endl;
	ofs << "AimAssistResyncLeniencyFactor=" << AimAssist::ResyncLeniencyFactor << std::endl;
	ofs << "AimAssistDrawDebugOverlay=" << AimAssist::DrawDebugOverlay << std::endl;
	ofs << "AimAssistFlipSliderballDeadzone=" << AimAssist::FlipSliderballDeadzone << std::endl;
	ofs << "AimAssistSliderballDeadzone=" << AimAssist::SliderballDeadzone << std::endl;
	ofs << "AimAssistAlgorithmv2Power=" << AimAssist::Algorithmv2Power << std::endl;
	ofs << "AimAssistAlgorithmv2AssistOnSliders=" << AimAssist::Algorithmv2AssistOnSliders << std::endl;
	ofs << "AimAssistAlgorithmv3Strength=" << AimAssist::Algorithmv3Strength << std::endl;
	ofs << "AimAssistAlgorithmv3AssistOnSliders=" << AimAssist::Algorithmv3AssistOnSliders << std::endl;
	ofs << "AimAssistAlgorithmv3BaseFOV=" << AimAssist::Algorithmv3BaseFOV << std::endl;
	ofs << "AimAssistAlgorithmv3MaximumFOVScale=" << AimAssist::Algorithmv3MaximumFOVScale << std::endl;
	ofs << "AimAssistAlgorithmv3MinimumFOVTotal=" << AimAssist::Algorithmv3MinimumFOVTotal << std::endl;
	ofs << "AimAssistAlgorithmv3MaximumFOVTotal=" << AimAssist::Algorithmv3MaximumFOVTotal << std::endl;
	ofs << "AimAssistAlgorithmv3AccelerationFactor=" << AimAssist::Algorithmv3AccelerationFactor << std::endl;

	ofs << "TimewarpEnabled=" << Timewarp::Enabled << std::endl;
	ofs << "TimewarpType=" << Timewarp::Type << std::endl;
	ofs << "TimewarpRate=" << Timewarp::Rate << std::endl;
	ofs << "TimewarpMultiplier=" << Timewarp::Multiplier << std::endl;

	ofs << "VisualsARChangerEnabled=" << Visuals::ARChangerEnabled << std::endl;
	ofs << "VisualsARChangerAR=" << Visuals::AR << std::endl;
	ofs << "VisualsAdjustToMods=" << Visuals::ARChangerAdjustToMods << std::endl;
	ofs << "VisualsAdjustToRate=" << Visuals::ARChangerAdjustToRate << std::endl;
	ofs << "VisualsDrawPreemptiveDot=" << Visuals::ARChangerDrawPreemptiveDot << std::endl;
	ofs << "VisualsPreemptiveDotColour=" << Visuals::ARChangerPreemptiveDotColour.x << "," << Visuals::ARChangerPreemptiveDotColour.y << "," << Visuals::ARChangerPreemptiveDotColour.z << "," << Visuals::ARChangerPreemptiveDotColour.w << std::endl;
	ofs << "VisualsCSChangerEnabled=" << Visuals::CSChangerEnabled << std::endl;
	ofs << "VisualsCSChangerCS=" << Visuals::CS << std::endl;
	ofs << "VisualsHiddenDisabled=" << Visuals::HiddenDisabled << std::endl;
	ofs << "VisualsFlashlightDisabled=" << Visuals::FlashlightDisabled << std::endl;
	ofs << "VisualsMenuScale=" << Visuals::MenuScale << std::endl;
	ofs << "VisualsMenuBackground=" << Visuals::MenuBackground << std::endl;
	ofs << "VisualsAccentColour=" << Visuals::AccentColour.x << "," << Visuals::AccentColour.y << "," << Visuals::AccentColour.z << "," << Visuals::AccentColour.w << std::endl;
	ofs << "VisualsMenuColour=" << Visuals::MenuColour.x << "," << Visuals::MenuColour.y << "," << Visuals::MenuColour.z << "," << Visuals::MenuColour.w << std::endl;
	ofs << "VisualsControlColour=" << Visuals::ControlColour.x << "," << Visuals::ControlColour.y << "," << Visuals::ControlColour.z << "," << Visuals::ControlColour.w << std::endl;
	ofs << "VisualsTextColour=" << Visuals::TextColour.x << "," << Visuals::TextColour.y << "," << Visuals::TextColour.z << "," << Visuals::TextColour.w << std::endl;

	ofs << "MiscDisableSpectators=" << Misc::DisableSpectators << std::endl;
	ofs << "MiscPromptOnScoreSubmissionEnabled=" << Misc::PromptOnScoreSubmissionEnabled << std::endl;
	ofs << "MiscDisableLogging=" << Misc::DisableLogging << std::endl;
	ofs << "MiscRichPresenceSpooferEnabled=" << Misc::RichPresenceSpooferEnabled << std::endl;
	ofs << "MiscSpoofedName=" << Misc::SpoofedName << std::endl;
	ofs << "MiscSpoofedRank=" << Misc::SpoofedRank << std::endl;

	ofs.close();

	STR_ENCRYPT_END
}

void Config::Create()
{
	DirectoryHelper::EnsureDirectoriesExist();

	const std::string cfgPath = DirectoryHelper::ConfigsDirectory + "\\" + NewConfigName + ".cfg";

	if (!isValidName(NewConfigName) || std::filesystem::exists(cfgPath))
		return;

	std::ofstream ofs(cfgPath);
	ofs.close();

	Refresh();

	const auto it = std::find(Configs.begin(), Configs.end(), NewConfigName);

	if (it != Configs.end())
		CurrentConfig = std::distance(Configs.begin(), it);

	loadDefaults();
}

void Config::Refresh()
{
	DirectoryHelper::EnsureDirectoriesExist();

	Configs.clear();
	Configs.emplace_back("default");

	for (const auto& file : std::filesystem::directory_iterator(DirectoryHelper::ConfigsDirectory))
		if (file.path().extension() == ".cfg" && isValidName(file.path().filename().stem().string()))
			Configs.push_back(file.path().filename().stem().string());
}