#pragma once

class Tone
{
private:
	constexpr static double Ratio=pow(2, 1.0/12);
    uint32 freq=1;
public:
	constexpr Tone()=default;
	constexpr Tone(uint32 frequency):freq(frequency) {}

	constexpr uint32 Frequency()const
	{
		return freq;
	}
	constexpr void SetFrequency(uint32 f)
	{
		freq=f;
	}

	constexpr Tone Interval(int32 x)const
	{
		return Tone(uint32(freq*pow(Ratio, x)));
	}
	template<typename T>
	SineWave<T> AsSineWave(const Audio& format)const noexcept
	{
        return SineWave<T>(format.GetFrequency()/freq);
	}
};