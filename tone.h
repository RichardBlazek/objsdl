#pragma once

struct Tone
{
	constexpr static double Ratio=pow(2, 1.0/12);
    uint32 freq;
	constexpr Tone Interval(int32 x)const
	{
		return Tone{uint32(freq*pow(Ratio, x))};
	}
	template<typename T>
	SineWave<T> AsSineWave(const Audio& format)const noexcept
	{
        return SineWave<T>{format.GetFrequency()/freq};
	}
};