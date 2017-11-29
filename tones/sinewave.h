#pragma once

template<typename T>
class SineWave
{
private:
	constexpr static double SinCycle=2*M_PI;
	uint32 lenght;
public:
	SineWave()=default;
	SineWave(uint32 len):lenght(len) {}

	uint32 WaveLenght()const
	{
		return lenght;
	}
	void SetLenght(uint32 len)
	{
		lenght=len;
	}

    Sound<T> Build(T volume)const
    {
    	Sound<T> result(lenght);
    	for(size_t i=0;i<result.Size();++i)
		{
			result[i]=sin(i*SinCycle/lenght)*volume;
		}
		return func::Move(result);
    }
};