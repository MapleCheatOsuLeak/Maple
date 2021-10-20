#include "HitObjectManager.h"

#include <Vanilla.h>

#include "Player.h"

void HitObjectManager::Initialize()
{
	RawHitObjectManager = Vanilla::Explorer["osu.GameplayElements.HitObjectManager"];

	hitObjectManagerField = Player::RawPlayer["hitObjectManager"].Field;
	preEmptField = RawHitObjectManager["PreEmpt"].Field;
	preEmptSliderCompleteField = RawHitObjectManager["PreEmpt"].Field;
	activeModsField = RawHitObjectManager["ActiveMods"].Field;

	obfuscatedType = activeModsField.GetTypeUnsafe();

	obfuscatedType["get_Value"].Method.Compile();
	obfuscatedGetValue = static_cast<fnObfuscatedGetValue>(obfuscatedType["get_Value"].Method.GetNativeStart());

	obfuscatedType["set_Value"].Method.Compile();
	obfuscatedSetValue = static_cast<fnObfuscatedSetValue>(obfuscatedType["set_Value"].Method.GetNativeStart());
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
