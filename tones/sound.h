#pragma once

template<typename T>
class Sound
{
private:
	std::vector<T> data;
public:
	Sound()=default;
	Sound(const std::vector<T>& data):data(data) {}
	Sound(std::vector<T>&& data):data(data) {}
	Sound(size_t size):data(size) {}

	T& operator[](size_t i)
	{
		return data[i];
	}
	size_t Size()const
	{
		return data.size();
	}
	void SetSize(size_t size)
	{
		data.resize(size);
	}
	size_t Write(T* stream, size_t streamsize, size_t pos)const
	{
		for(size_t i=0;i<streamsize;++i)
		{
			stream[i]=data[(pos+i)%data.size()];
		}
		return (pos+streamsize)%data.size();
	}
};