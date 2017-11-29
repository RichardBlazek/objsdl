#pragma once

class Audio
{
public:
	friend class AudioDevice;
#include "audio\format.h"
#include "audio\buffer.h"
private:
	SDL_AudioSpec data;
public:
	using CallbackType=void(*)(void*, uint8*, int);

	Audio(int frequency, Format fmt, uint8 channels, uint16 samples, CallbackType callback=nullptr, void* userdata=nullptr)noexcept
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
	void SetCallback(CallbackType callback)
	{
		data.callback=callback;
	}
	template<typename T>
	void SetUserdata(T* userdata)
	{
		data.userdata=(void*)userdata;
	}
	CallbackType GetCallback()const
	{
		return data.callback;
	}
	template<typename T=void>
	T* GetUserdata()const
	{
		return (T*)data.userdata;
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
	std::tuple<Audio, WAVBuffer> LoadWAV(const std::string& file);

	void Convert(int freq, Format fmt, uint8 channels, const uint8* src, uint8* dst, size_t len)const
	{
		SDL_AudioCVT cvt;
		SDL_BuildAudioCVT(&cvt, data.format, data.channels, data.freq, SDL_AudioFormat(fmt), channels, freq);
		cvt.len=len;
		cvt.buf=new uint8[cvt.len*cvt.len_mult];
		SDL_memcpy(cvt.buf, src, cvt.len);
		SDL_ConvertAudio(&cvt);
		SDL_memcpy(dst, cvt.buf, cvt.len_cvt);
		delete[] cvt.buf;
	}
	void Convert(int freq, Format fmt, uint8 channels, uint8* data, size_t len)const
	{
		Convert(freq, fmt, channels, data, data, len);
	}

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
std::tuple<Audio, Audio::WAVBuffer> Audio::LoadWAV(const std::string& file)
{
	Audio result(*this);
	uint8* tmp_buf;
	uint32 tmp_len;
	SDL_AudioSpec* tmp=SDL_LoadWAV(file.c_str(), &data, &tmp_buf, &tmp_len);
	Error::IfZero(tmp);
	result.data=*tmp;
	return std::make_tuple(result, WAVBuffer(tmp_buf,tmp_len));
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