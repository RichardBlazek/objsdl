#pragma once

class AudioDevice: public NonCopyable
{
private:
	SDL_AudioDeviceID id=0;
public:
	enum class Status
	{
		Stopped=SDL_AUDIO_STOPPED, Playing=SDL_AUDIO_PLAYING, Paused=SDL_AUDIO_PAUSED
	};
	void Close()
	{
		if(id!=0)
		{
			SDL_CloseAudioDevice(id);
			id=0;
		}
	}
	void Open(const Audio& desired, std::string name=std::string(), bool recording=false)
	{
		Close();
		id=SDL_OpenAudioDevice(name.empty()?nullptr:name.c_str(), recording, &desired.data, nullptr, 0);
		Error::IfZero(id);
	}
	void Open(const Audio& desired, Audio& result_format, Audio::AllowedChanges allowed=Audio::AllowedChanges::Any, std::string name=std::string(), bool recording=false)
	{
		Close();
		id=SDL_OpenAudioDevice(name.empty()?nullptr:name.c_str(), recording, &desired.data, &result_format.data, int(allowed));
		result_format.data.userdata=nullptr;
		Error::IfZero(id);
	}
	AudioDevice()=default;
	AudioDevice(const Audio& desired, std::string name=std::string(), bool recording=false):id(0)
	{
		Open(desired, name, recording);
	}
	AudioDevice(const Audio& desired, Audio& result_format, Audio::AllowedChanges allowed=Audio::AllowedChanges::Any, std::string name=std::string(), bool recording=false):id(0)
	{
		Open(desired, result_format, allowed, name, recording);
	}
	~AudioDevice()
	{
		Close();
	}
	AudioDevice(AudioDevice&& device):id(device.id)
	{
		device.id=0;
	}
	AudioDevice& operator=(AudioDevice&& device)
	{
		Close();
		id=device.id;
		device.id=0;
		return *this;
	}
	Status GetStatus()
	{
		return Status(SDL_GetAudioDeviceStatus(id));
	}
	static uint32 Count(bool recording=false)
	{
		return SDL_GetNumAudioDevices(recording);
	}
	static std::string NameOf(uint32 index, bool recording=false)
	{
		return std::string(SDL_GetAudioDeviceName(index, recording));
	}
	void Play()
	{
		SDL_PauseAudioDevice(id, 0);
	}
	void Pause()
	{
		SDL_PauseAudioDevice(id, 1);
	}
	void Lock()
	{
		SDL_LockAudioDevice(id);
	}
	void Unlock()
	{
		SDL_UnlockAudioDevice(id);
	}
	void AddPlayData(void* data, uint32 len)
	{
        Error::IfNegative(SDL_QueueAudio(id, data, len));
	}
	void ClearPlayData()
	{
		SDL_ClearQueuedAudio(id);
	}
    uint32 PlayDataSize()
    {
        return SDL_GetQueuedAudioSize(id);
    }
    uint32 RetrievePlayData(void* data, uint32 len)
    {
		return SDL_DequeueAudio(id, data, len);
    }
};