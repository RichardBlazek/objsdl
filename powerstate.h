#pragma once

enum class PowerState
{
	Unknown,
	OnBattery,
	NoBattery,
	Charging,
	Charged
};

struct PowerInfo
{
	PowerState powerstate;
	int percents;
	int seconds;
	static PowerInfo Actual()
	{
		PowerInfo powerinfo;
		powerinfo.powerstate=PowerState(SDL_GetPowerInfo(&powerinfo.seconds, &powerinfo.percents));
		return powerinfo;
	}
};
