#pragma once

class Audio
{
private:
	using CallbackType=void(*)(void*, uint8*, int);
	SDL_AudioSpec data;
public:
#include "audio\format.h"
	friend class AudioDevice;

	Audio(int frequency=48000, Format fmt=Format::U8, uint8 channels=1, uint16 samples=4096, CallbackType callback=nullptr, void* userdata=nullptr)noexcept
	{
		data.freq=frequency;
		data.format=SDL_AudioFormat(fmt);
		data.channels=channels;
		data.samples=samples;
		data.callback=callback;
		data.userdata=userdata;
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
	void SetCallback(CallbackType callback)noexcept
	{
		data.callback=callback;
	}
	template<typename T>
	void SetUserdata(T* userdata)noexcept
	{
		data.userdata=userdata;
	}
	template<typename T>
	const T* GetUserdata()const noexcept
	{
		return (T*)data.userdata;
	}
	CallbackType GetCallback()const noexcept
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
	std::tuple<Audio, std::vector<uint8>> LoadWAV(const std::string& file)const;
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
std::tuple<Audio, std::vector<uint8>> Audio::LoadWAV(const std::string& file)const
{
	uint8* tmp_buf;
	uint32 tmp_len;
	Audio result(*this);
	result.data=*Error::IfZero(SDL_LoadWAV(file.c_str(), &result.data, &tmp_buf, &tmp_len));
	result.data.userdata=data.userdata;
	result.data.callback=data.callback;
	std::vector<uint8> buffer(tmp_buf, tmp_buf+tmp_len);
	SDL_FreeWAV(tmp_buf);
	return std::make_tuple(func::Move(result), buffer);
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