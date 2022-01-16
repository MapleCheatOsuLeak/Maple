#define NOMINMAX

#include "HitObjectManager.h"

#include <Vanilla.h>

#include "Player.h"

void HitObjectManager::Initialize()
{
	RawHitObjectManager   = Vanilla::Explorer["osu.GameplayElements.HitObjectManager"];
	RawHitObject		  = Vanilla::Explorer["osu.GameplayElements.HitObjects.HitObject"];
	RawHitObjectSliderOsu = Vanilla::Explorer["osu.GameplayElements.HitObjects.Osu.SliderOsu"];

	hitObjectManagerField				 = Player::RawPlayer["hitObjectManager"].Field;
	preEmptField						 = RawHitObjectManager["PreEmpt"].Field;
	preEmptSliderCompleteField			 = RawHitObjectManager["PreEmptSliderComplete"].Field;
	activeModsField						 = RawHitObjectManager["ActiveMods"].Field;
	hitWindow300Field					 = RawHitObjectManager["HitWindow300"].Field;
	hitWindow100Field					 = RawHitObjectManager["HitWindow100"].Field;
	hitWindow50Field					 = RawHitObjectManager["HitWindow50"].Field;
	spriteDisplaySizeField				 = RawHitObjectManager["SpriteDisplaySize"].Field;
	hitObjectRadiusField				 = RawHitObjectManager["HitObjectRadius"].Field;
	spriteRatioField					 = RawHitObjectManager["SpriteRatio"].Field;
	spriteManagerField					 = RawHitObjectManager["spriteManager"].Field;
	gamefieldSpriteRatioField			 = Vanilla::Explorer["osu.Graphics.Sprites.SpriteManager"]["GamefieldSpriteRatio"].Field;
	stackOffsetField					 = RawHitObjectManager["StackOffset"].Field;
	currentHitObjectIndexField			 = RawHitObjectManager["currentHitObjectIndex"].Field;
	hitObjectsCountField				 = RawHitObjectManager["hitObjectsCount"].Field;
	hitObjectTypeField					 = RawHitObject["Type"].Field;
	hitObjectStartTimeField				 = RawHitObject["StartTime"].Field;
	hitObjectEndTimeField				 = RawHitObject["EndTime"].Field;
	hitObjectPositionField				 = RawHitObject["Position"].Field;
	hitObjectEndPositionField			 = RawHitObjectSliderOsu["<EndPosition>k__BackingField"].Field;
	hitObjectSegmentCountField			 = RawHitObject["SegmentCount"].Field;
	hitObjectSpatialLengthField			 = RawHitObject["SpatialLength"].Field;
	hitObjectSliderCurvePointsField		 = RawHitObjectSliderOsu["sliderCurvePoints"].Field;
	hitObjectCumulativeLengthsField		 = RawHitObjectSliderOsu["cumulativeLengths"].Field;
	hitObjectSliderCurveSmoothLinesField = RawHitObjectSliderOsu["sliderCurveSmoothLines"].Field;

	obfuscatedType = activeModsField.GetTypeUnsafe();

	obfuscatedType["get_Value"].Method.Compile();
	obfuscatedGetValue = static_cast<fnObfuscatedGetValue>(obfuscatedType["get_Value"].Method.GetNativeStart());

	obfuscatedType["set_Value"].Method.Compile();
	obfuscatedSetValue = static_cast<fnObfuscatedSetValue>(obfuscatedType["set_Value"].Method.GetNativeStart());

	RawHitObjectManager["GetObject"].Method.Compile();
	getObject = static_cast<fnGetObject>(RawHitObjectManager["GetObject"].Method.GetNativeStart());

	RawHitObjectManager["SetBeatmap"].Method.Compile();
	setBeatmap = static_cast<fnSetBeatmap>(RawHitObjectManager["SetBeatmap"].Method.GetNativeStart());

	RawHitObjectManager["Load"].Method.Compile();
	load = static_cast<fnLoad>(RawHitObjectManager["Load"].Method.GetNativeStart());
}

void* HitObjectManager::Instance()
{
	return *static_cast<void**>(hitObjectManagerField.GetAddress(Player::Instance()));
}

int HitObjectManager::GetPreEmpt()
{
	return *static_cast<int*>(preEmptField.GetAddress(Instance()));
}

void HitObjectManager::SetPreEmpt(int preEmpt)
{
	*static_cast<int*>(preEmptField.GetAddress(Instance())) = preEmpt;
}

int HitObjectManager::GetPreEmptSliderComplete()
{
	return *static_cast<int*>(preEmptSliderCompleteField.GetAddress(Instance()));
}

void HitObjectManager::SetPreEmptSliderComplete(int preEmptSliderComplete)
{
	*static_cast<int*>(preEmptSliderCompleteField.GetAddress(Instance())) = preEmptSliderComplete;
}

Mods HitObjectManager::GetActiveMods()
{
	void* activeModsInstance = *static_cast<void**>(activeModsField.GetAddress(Instance()));
	
	return obfuscatedGetValue(activeModsInstance);
}

void HitObjectManager::SetActiveMods(Mods mods)
{
	void* activeModsInstance = *static_cast<void**>(activeModsField.GetAddress(Instance()));

	obfuscatedSetValue(activeModsInstance, mods);
}

int HitObjectManager::GetHitWindow300()
{
	return *static_cast<int*>(hitWindow300Field.GetAddress(Instance()));
}

int HitObjectManager::GetHitWindow100()
{
	return *static_cast<int*>(hitWindow100Field.GetAddress(Instance()));
}

int HitObjectManager::GetHitWindow50()
{
	return *static_cast<int*>(hitWindow50Field.GetAddress(Instance()));
}

float HitObjectManager::GetSpriteDisplaySize()
{
	return *static_cast<float*>(spriteDisplaySizeField.GetAddress(Instance()));
}

void HitObjectManager::SetSpriteDisplaySize(float size)
{
	*static_cast<float*>(spriteDisplaySizeField.GetAddress(Instance())) = size;
}

float HitObjectManager::GetHitObjectRadius()
{
	return *static_cast<float*>(hitObjectRadiusField.GetAddress(Instance()));
}

void HitObjectManager::SetHitObjectRadius(float radius)
{
	*static_cast<float*>(hitObjectRadiusField.GetAddress(Instance())) = radius;
}

float HitObjectManager::GetSpriteRatio()
{
	return *static_cast<float*>(spriteRatioField.GetAddress(Instance()));
}

void HitObjectManager::SetSpriteRatio(float ratio)
{
	*static_cast<float*>(spriteRatioField.GetAddress(Instance())) = ratio;
}

float HitObjectManager::GetGamefieldSpriteRatio()
{
	void* spriteManagerInstance = *static_cast<void**>(spriteManagerField.GetAddress(Instance()));
	if (spriteManagerInstance != nullptr)
		return *static_cast<float*>(gamefieldSpriteRatioField.GetAddress(spriteManagerInstance));

	return 0.f;
}

void HitObjectManager::SetGamefieldSpriteRatio(float ratio)
{
	void* spriteManagerInstance = *static_cast<void**>(spriteManagerField.GetAddress(Instance()));
	if (spriteManagerInstance != nullptr)
		*static_cast<float*>(gamefieldSpriteRatioField.GetAddress(spriteManagerInstance)) = ratio;
}

float HitObjectManager::GetStackOffset()
{
	return *static_cast<float*>(stackOffsetField.GetAddress(Instance()));
}

void HitObjectManager::SetStackOffset(float offset)
{
	*static_cast<float*>(stackOffsetField.GetAddress(Instance())) = offset;
}

int HitObjectManager::GetCurrentHitObjectIndex()
{
	return *static_cast<int*>(currentHitObjectIndexField.GetAddress(Instance()));
}

int HitObjectManager::GetHitObjectsCount()
{
	return *static_cast<int*>(hitObjectsCountField.GetAddress(Instance()));
}

HitObject HitObjectManager::GetHitObject(int index)
{
	void* hitObjectInstance = getObject(Instance(), index);

	const HitObjectType type   = *reinterpret_cast<HitObjectType*>(hitObjectTypeField.GetAddress(hitObjectInstance));
	const int startTime		   = *reinterpret_cast<int*>(hitObjectStartTimeField.GetAddress(hitObjectInstance));
	const int endTime		   = *reinterpret_cast<int*>(hitObjectEndTimeField.GetAddress(hitObjectInstance));
	const Vector2 position	   = *reinterpret_cast<Vector2*>(hitObjectPositionField.GetAddress(hitObjectInstance));
	const int segmentCount	   = *reinterpret_cast<int*>(hitObjectSegmentCountField.GetAddress(hitObjectInstance));
	const double spatialLength = *reinterpret_cast<double*>(hitObjectSpatialLengthField.GetAddress(hitObjectInstance));

	if ((type & HitObjectType::Slider) > HitObjectType::None)
	{
		const Vector2 endPosition = *reinterpret_cast<Vector2*>(hitObjectEndPositionField.GetAddress(hitObjectInstance));

		std::vector<Vector2> sliderCurvePoints;
		std::vector<std::pair<Vector2, Vector2>> sliderCurveSmoothLines;
		std::vector<double> cumulativeLengths;

		const uintptr_t sliderCurvePointsPointer = *reinterpret_cast<uintptr_t*>(hitObjectSliderCurvePointsField.GetAddress(hitObjectInstance));
		const uintptr_t sliderCurvePointsItems   = *reinterpret_cast<uintptr_t*>(sliderCurvePointsPointer + 0x04);
		const int sliderCurvePointsCount		 = *reinterpret_cast<int*>(sliderCurvePointsPointer + 0x0C);

		for (int i = 0; i < sliderCurvePointsCount; i++)
		{
			Vector2 point = *reinterpret_cast<Vector2*>(sliderCurvePointsItems + 0x08 + 0x08 * i);

			sliderCurvePoints.emplace_back(point);
		}

		const uintptr_t sliderCurveSmoothLinesPointer = *reinterpret_cast<uintptr_t*>(hitObjectSliderCurveSmoothLinesField.GetAddress(hitObjectInstance));
		const uintptr_t sliderCurveSmoothLinesItems   = *reinterpret_cast<uintptr_t*>(sliderCurveSmoothLinesPointer + 0x04);
		const int sliderCurveSmoothLinesCount		  = *reinterpret_cast<int*>(sliderCurveSmoothLinesPointer + 0x0C);

		for (int i = 0; i < sliderCurveSmoothLinesCount; i++)
		{
			const uintptr_t item = *reinterpret_cast<uintptr_t*>(sliderCurveSmoothLinesItems + 0x08 + 0x04 * i);
			
			Vector2 point1 = *reinterpret_cast<Vector2*>(item + 0x08);
			Vector2 point2 = *reinterpret_cast<Vector2*>(item + 0x10);

			sliderCurveSmoothLines.emplace_back(point1, point2);
		}

		const uintptr_t cumulativeLengthsPointer = *reinterpret_cast<uintptr_t*>(hitObjectCumulativeLengthsField.GetAddress(hitObjectInstance));
		const uintptr_t cumulativeLengthsItems   = *reinterpret_cast<uintptr_t*>(cumulativeLengthsPointer + 0x4);
		const int cumulativeLengthsCount		 = *reinterpret_cast<int*>(cumulativeLengthsPointer + 0xC);

		for (int i = 0; i < cumulativeLengthsCount; i++)
			cumulativeLengths.emplace_back(*reinterpret_cast<double*>(cumulativeLengthsItems + 0x8 + 0x8 * i));

		return HitObject(type, startTime, endTime, position, endPosition, segmentCount, spatialLength, sliderCurvePoints, sliderCurveSmoothLines, cumulativeLengths);
	}

	return HitObject(type, startTime, endTime, position, position, segmentCount, spatialLength);
}

std::vector<HitObject> HitObjectManager::GetAllHitObjects()
{
	std::vector<HitObject> toReturn;
	for (int i = 0; i < GetHitObjectsCount(); i++)
		toReturn.push_back(GetHitObject(i));
	return toReturn;
}

void HitObjectManager::SetBeatmap(void* beatmap)
{
	setBeatmap(Instance(), beatmap, GetActiveMods());
}

bool HitObjectManager::Load(bool processHeaders)
{
	return load(Instance(), processHeaders);
}

double HitObjectManager::MapDifficultyRange(double difficulty, double min, double mid, double max, bool adjustToMods)
{
	if (adjustToMods)
		difficulty = ModManager::IsModEnabled(Mods::Easy) ? std::max(0.0, difficulty / 2.0) : ModManager::IsModEnabled(Mods::HardRock) ? std::min(10.0, difficulty * 1.4) : difficulty;

	if (difficulty > 5.)
		return mid + (max - mid) * (difficulty - 5.) / 5.;
	if (difficulty < 5.)
		return mid - (mid - min) * (5. - difficulty) / 5.;
	
	return mid;
}