#pragma once

class AudioStream: public NonCopyable
{
private:
	SDL_AudioStream* stream=nullptr;
public:
	AudioStream()=default;
	AudioStream(Audio::Format src_format, uint8 src_channels, int src_freq, Audio::Format dst_format, uint8 dst_channels, int dst_freq)
		:stream(Error::IfZero(SDL_NewAudioStream(SDL_AudioFormat(src_format), src_channels, src_freq, SDL_AudioFormat(dst_format), dst_channels, dst_freq))) {}
	AudioStream(AudioStream&& init):stream(init.stream)
	{
		init.stream=nullptr;
	}
	AudioStream& operator=(AudioStream&& init)
	{
		SDL_FreeAudioStream(stream);
		stream=init.stream;
		init.stream=nullptr;
		return *this;
	}
	void Flush()
	{
		Error::IfNegative(SDL_AudioStreamFlush(stream));
	}
	size_t Available()
	{
		return Error::IfNegative(SDL_AudioStreamAvailable(stream));
	}
	void operator<<(const std::vector<uint8>& data)
	{
		Error::IfNegative(SDL_AudioStreamPut(stream, data.data(), data.size()));
	}
	void operator>>(std::vector<uint8>& dest)
	{
		auto size=dest.size();
		dest.resize(size+Available());
		auto loaded=Error::IfNegative(SDL_AudioStreamGet(stream, dest.data()+size, dest.size()-size));
		dest.resize(size+loaded);
	}
	void Clear()
	{
		SDL_AudioStreamClear(stream);
	}
};