#pragma once

class AudioStream: public NonCopyable
{
private:
	SDL_AudioStream* stream=nullptr;
public:
	AudioStream()=default;
	AudioStream(Audio::Format src_format, uint8 src_channels, int src_freq, Audio::Format dst_format, uint8 dst_channels, int dst_freq)
		:stream(Error::IfZero(SDL_NewAudioStream(src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate))) {}
	AudioStrear(AudioStream&& init):stream(init.stream)
	{
		init.stream=nullptr;
	}
	AudioStream& operator=(AudioStream&& init)
	{
		SDL_FreeAudioStream(stream);
		stream=init.stream;
		init.stream=nullptr;
	}
	void Put(const Buffer& data)
	{
		Error::IfNegative(SDL_AudioStreamPut(stream, data.data(), data.size()));
	}
	void Flush()
	{
		Error::IfNegative(SDL_AudioStreamFlush(stream));
	}
	size_t Available()
	{
		return Error::IfNegative(SDL_AudioStreamAvailable(stream, buf, max_len));
	}
	Buffer Get()
	{
		Buffer buf(Available());
		buf.resize(func::Min(Error::IfNegative(SDL_AudioStreamGet(stream, buf.data(), buf.size())), buf.size()));
		return func::Move(buf);
	}
	void Clear()
	{
		SDL_AudioStreamClear(stream);
	}
};