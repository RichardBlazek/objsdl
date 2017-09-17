#pragma once

int GetSystemRAM()
{
	return SDL_GetSystemRAM();
}

namespace cpu
{
	int GetCacheLineSize()
	{
		return SDL_GetCPUCacheLineSize();
	}
	int Count()
	{
		return SDL_GetCPUCount();
	}
	bool Has3DNow()
	{
		return SDL_Has3DNow();
	}
	bool HasAVX()
	{
		return SDL_HasAVX();
	}
	bool HasAVX2()
	{
		return SDL_HasAVX2();
	}
	bool HasAltiVec()
	{
		return SDL_HasAltiVec();
	}
	bool HasMMX()
	{
		return SDL_HasMMX();
	}
	bool HasRDTSC()
	{
		return SDL_HasRDTSC();
	}
	bool HasSSE()
	{
		return HasSSE();
	}
	bool HasSSE2()
	{
		return HasSSE2();
	}
	bool HasSSE3()
	{
		return HasSSE3();
	}
	bool HasSSE41()
	{
		return HasSSE41();
	}
	bool HasSSE42()
	{
		return HasSSE42();
	}
}