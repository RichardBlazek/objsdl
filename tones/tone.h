#pragma once

class Tone
{
private:
	constexpr static double Ratio=pow(2, 1.0/12);
    uint32 freq;
public:
	Tone()=default;
	Tone(uint32 len):lenght(len) {}

	uint32 Frequency()const
	{
		return lenght;
	}
	void SetFrequency(uint32 f)
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