#pragma once

//Formát zvukových dat
enum class Format:uint16
{
	S8=AUDIO_S8,U8=AUDIO_U8,
	S16=AUDIO_S16SYS,S16LE=AUDIO_S16LSB,S16BE=AUDIO_S16MSB,
	U16=AUDIO_U16SYS,U16LE=AUDIO_U16LSB,U16BE=AUDIO_U16MSB,
	S32=AUDIO_S32SYS,S32LE=AUDIO_S32LSB,S32BE=AUDIO_S32MSB,
	F32=AUDIO_F32SYS,F32LE=AUDIO_F32LSB,F32BE=AUDIO_F32MSB
};
static bool IsFloat(Format fmt)
{
	return bool(SDL_AUDIO_ISFLOAT(uint16(fmt)));
}
static bool IsSigned(Format fmt)
{
	return bool(SDL_AUDIO_ISSIGNED(uint16(fmt)));
}
static uint8 BitSize(Format fmt)
{
	return SDL_AUDIO_BITSIZE(uint16(fmt));
}
static bool IsBigEndian(Format fmt)
{
	return bool(SDL_AUDIO_ISBIGENDIAN(uint16(fmt)));
}