#pragma once

enum class MouseButton: uint8
{
	Left=SDL_BUTTON_LEFT,
	Right=SDL_BUTTON_RIGHT,
	Middle=SDL_BUTTON_MIDDLE,
	X1=SDL_BUTTON_X1,
	X2=SDL_BUTTON_X2
};
enum class MouseButtonMask: uint8
{
	None=0,
	Left=SDL_BUTTON_LMASK,
	Right=SDL_BUTTON_RMASK,
	Middle=SDL_BUTTON_MMASK,
	X1=SDL_BUTTON_X1MASK,
	X2=SDL_BUTTON_X2MASK
};
MouseButtonMask operator|(MouseButtonMask first, MouseButtonMask second)noexcept
{
	return MouseButtonMask(uint32(first)|uint32(second));
}
MouseButtonMask operator&(MouseButtonMask first, MouseButtonMask second)noexcept
{
	return MouseButtonMask(uint32(first)&uint32(second));
}
MouseButtonMask operator^(MouseButtonMask first, MouseButtonMask second)noexcept
{
	return MouseButtonMask(uint32(first)^uint32(second));
}
MouseButtonMask operator|=(MouseButtonMask& first, MouseButtonMask second)noexcept
{
	return first=(first|second);
}
MouseButtonMask operator&=(MouseButtonMask& first, MouseButtonMask second)noexcept
{
	return first=(first&second);
}
MouseButtonMask operator^=(MouseButtonMask& first, MouseButtonMask second)noexcept
{
	return first=(first^second);
}
MouseButtonMask operator~(MouseButtonMask param)noexcept
{
	return MouseButtonMask(~uint32(param));
}