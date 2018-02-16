#pragma once

void Wait(uint32 miliseconds)noexcept
{
    SDL_Delay(miliseconds);
}
uint32 RunTimeMs()noexcept
{
    return SDL_GetTicks();
}
uint64 RunTimeTicks()noexcept
{
    return SDL_GetPerformanceCounter();
}
uint64 TicksPerSec()noexcept
{
    return SDL_GetPerformanceFrequency();
}

class Timer
{
private:
	SDL_TimerID id=0;
	static uint32 SDL_Callback(uint32 interval, void* param)
	{
		return (*(std::function<uint32(uint32)>*)param)(interval);
	}
public:
	Timer()=default;
	void Add(uint32 interval, std::function<uint32(uint32)> callback)
	{
		Remove();
		id=Error::IfZero(SDL_AddTimer(interval, SDL_Callback, (void*)&callback));
	}
	void Remove()
	{
		if(id!=0)
		{
			SDL_RemoveTimer(id);
			id=0;
		}
	}
	Timer(uint32 interval, std::function<uint32(uint32)> callback)
	{
		Add(interval, callback);
	}
	~Timer()
	{
		Remove();
	}
};