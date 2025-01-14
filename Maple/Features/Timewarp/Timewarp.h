#pragma once

#include <COM/COMString.h>

class Timewarp
{
	typedef double(__fastcall* fnGetCurrentPlaybackRate)();
	typedef void(__fastcall* fnSetCurrentPlaybackRate)(double rate);
	
	static inline double tickrate = 1000.0 / 60.0;

	static inline void* getCurrentPlaybackRateReturnAddress = nullptr;
	static double __fastcall getCurrentPlaybackRateStub();
public:
	static void Initialize();
	static void UpdateCatcherSpeed();
	static double GetRate();
	static double GetRateMultiplier();

	static inline fnSetCurrentPlaybackRate oSetCurrentPlaybackRate;
	static void __fastcall SetCurrentPlaybackRateHook(double rate);

	static inline fnGetCurrentPlaybackRate oGetCurrentPlaybackRate;
	static double __fastcall GetCurrentPlaybackRateHook();
};
