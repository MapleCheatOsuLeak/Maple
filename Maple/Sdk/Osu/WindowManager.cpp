#include "WindowManager.h"

#include <Vanilla.h>

#include "GameBase.h"
#include "../DataTypes/Structs/sRectangle.h"

void WindowManager::Initialize()
{
	RawWindowManager = Vanilla::Explorer["osu.WindowManager"];

	instanceAddress = GameBase::RawGameBase["WindowManager"].Field.GetAddress();
	isFullscreenAddress = GameBase::RawGameBase["IsFullscreen"].Field.GetAddress();

	widthField = RawWindowManager["Width"].Field;
	heightField = RawWindowManager["Height"].Field;
	clientBoundsField = GameBase::RawGameBase["ClientBounds"].Field;
}

void* WindowManager::Instance()
{
	return *static_cast<void**>(instanceAddress);
}

bool WindowManager::IsFullscreen()
{
	return *static_cast<bool*>(isFullscreenAddress);
}

int WindowManager::Width()
{
	return *static_cast<int*>(widthField.GetAddress(Instance()));
}

int WindowManager::Height()
{
	return *static_cast<int*>(heightField.GetAddress(Instance()));
}

Vector2 WindowManager::ViewportPosition()
{
	if (!IsFullscreen())
		return Vector2(0, 0);

	sRectangle* clientBounds = static_cast<sRectangle*>(clientBoundsField.GetAddress());

	return Vector2(clientBounds->X, clientBounds->Y);
}
