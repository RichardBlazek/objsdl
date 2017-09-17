#pragma once

template<typename T>
struct Sound
{
	std::vector<T> data;
	size_t Write(T* stream, size_t streamsize, size_t pos)const
	{
		for(size_t i=0;i<streamsize;++i)
		{
			stream[i]=data[(pos+i)%data.size()];
		}
		return (pos+streamsize)%data.size();
	}
};

template<typename T>
struct SineWave
{
	constexpr static double SinCycle=2*M_PI;
	uint32 lenght;
    Sound<T> Build(T volume)const
    {
    	Sound<T> result;
    	result.data.resize(lenght);
    	for(size_t i=0;i<result.data.size();++i)
		{
			result.data[i]=sin(i*SinCycle/lenght)*volume;
		}
		return func::Move(result);
    }
};