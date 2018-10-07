#pragma once

class Audio: public NonCopyable
{
public:
	friend class AudioDevice;
#include "audio\format.h"
private:
	SDL_AudioSpec data;
public:
	using CallbackType=void(*)(void*, uint8*, int);
	using Buffer=std::vector<uint8>;

	Audio(int frequency, Format fmt, uint8 channels, uint16 samples, CallbackType callback=nullptr, void* userdata=nullptr)noexcept
	{
		data.freq=frequency;
		data.format=SDL_AudioFormat(fmt);
		data.channels=channels;
		data.samples=samples;
		data.callback=callback;
		data.userdata=userdata;
	}
	~Audio()
	{
		delete data.userdata;
	}
	void SetFrequency(int frequency)noexcept
	{
		data.freq=frequency;
	}
	void SetFormat(Format fmt)noexcept
	{
		data.format=SDL_AudioFormat(fmt);
	}
	void SetChannels(uint8 channels)noexcept
	{
		data.channels=channels;
	}
	void SetSamples(uint16 samples)noexcept
	{
		data.samples=samples;
	}
	void SetCallback(CallbackType callback)
	{
		data.callback=callback;
	}
	void SetBuffer(const Buffer& userdata)
	{
		data.userdata=new Buffer(userdata);
	}
	void SetBuffer(Buffer&& userdata)
	{
		data.userdata=new Buffer(func::Move(userdata));
	}
	Buffer& GetBuffer()const
	{
		return *(Buffer*)data.userdata;
	}
	CallbackType GetCallback()const
	{
		return data.callback;
	}
	int GetFrequency()const noexcept
	{
		return data.freq;
	}
	Format GetFormat()const noexcept
	{
		return Format(data.format);
	}
	uint8 GetChannels()const noexcept
	{
		return data.channels;
	}
	uint16 GetSamples()const noexcept
	{
		return data.samples;
	}
	enum class AllowedChanges
	{
		None=0, Frequency=SDL_AUDIO_ALLOW_FREQUENCY_CHANGE, Format=SDL_AUDIO_ALLOW_FORMAT_CHANGE,
		Channels=SDL_AUDIO_ALLOW_CHANNELS_CHANGE, Any=SDL_AUDIO_ALLOW_ANY_CHANGE
	};
	std::tuple<Audio, Buffer> LoadWAV(const std::string& file);
	static uint32 CountOfDrivers()
	{
		return SDL_GetNumAudioDrivers();
	}
	static std::string DriverName(uint32 index)
	{
		if(auto str=SDL_GetAudioDriver(index))
			return std::string(str);
		else
			throw Error("Audio::DriverName>invalid index");
	}
	static std::string CurrentDriverName()
	{
        if(auto str=SDL_GetCurrentAudioDriver())
			return std::string(str);
		else
			throw Error("Audio::CurrentDriverName>no driver initialized");
	}
	static void Mix(uint8* dst, const uint8* src, Format format, uint32 len, uint8 volume=128)
	{
		SDL_MixAudioFormat(dst, src, SDL_AudioFormat(format), len, volume);
	}
};
std::tuple<Audio, Audio::Buffer> Audio::LoadWAV(const std::string& file)
{
	Audio result(*this);
	uint8* tmp_buf;
	uint32 tmp_len;
	result.data=*Error::IfZero(SDL_LoadWAV(file.c_str(), &data, &tmp_buf, &tmp_len));
	result.userdata=new Buffer(tmp_buf, tmp_buf+tmp_len);
	SDL_FreeWAV(tmp_buf);
	return func::Move(result);
}
Audio::AllowedChanges operator~(Audio::AllowedChanges param)noexcept
{
	return Audio::AllowedChanges(~int(param));
}
Audio::AllowedChanges operator|(Audio::AllowedChanges first, Audio::AllowedChanges second)noexcept
{
	return Audio::AllowedChanges(int(first)|int(second));
}
Audio::AllowedChanges operator&(Audio::AllowedChanges first, Audio::AllowedChanges second)noexcept
{
	return Audio::AllowedChanges(int(first)&int(second));
}
Audio::AllowedChanges operator^(Audio::AllowedChanges first, Audio::AllowedChanges second)noexcept
{
	return Audio::AllowedChanges(int(first)^int(second));
}
Audio::AllowedChanges operator|=(Audio::AllowedChanges& first, Audio::AllowedChanges second)noexcept
{
	return first|=second;
}
Audio::AllowedChanges operator&=(Audio::AllowedChanges& first, Audio::AllowedChanges second)noexcept
{
	return first&=second;
}
Audio::AllowedChanges operator^=(Audio::AllowedChanges& first, Audio::AllowedChanges second)noexcept
{
	return first^=second;
}
#include "audio\device.h"
#include "audio\stream.h"