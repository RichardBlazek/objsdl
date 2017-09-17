#pragma once

enum class Keymod:uint16
{
	None=0,
	LShift=KMOD_LSHIFT,
	RShift=KMOD_RSHIFT,
	Shift=KMOD_SHIFT,
	LCtrl=KMOD_LCTRL,
	RCtrl=KMOD_RCTRL,
	Ctrl=KMOD_CTRL,
	LAlt=KMOD_LALT,
	RAlt=KMOD_RALT,
	Alt=KMOD_ALT,
	LGUI=KMOD_LGUI,
	RGUI=KMOD_RGUI,
	GUI=KMOD_GUI,
	NumLock=KMOD_NUM,
	CapsLock=KMOD_CAPS,
	Mode=KMOD_MODE,
	Reserved=KMOD_RESERVED,
};

Keymod operator|(Keymod first, Keymod second)noexcept
{
	return Keymod(uint32(first)|uint32(second));
}
Keymod operator&(Keymod first, Keymod second)noexcept
{
	return Keymod(uint32(first)&uint32(second));
}
Keymod operator^(Keymod first, Keymod second)noexcept
{
	return Keymod(uint32(first)^uint32(second));
}
Keymod operator|=(Keymod& first, Keymod second)noexcept
{
	return first=(first|second);
}
Keymod operator&=(Keymod& first, Keymod second)noexcept
{
	return first=(first&second);
}
Keymod operator^=(Keymod& first, Keymod second)noexcept
{
	return first=(first^second);
}
Keymod operator~(Keymod param)noexcept
{
	return Keymod(~uint32(param));
}