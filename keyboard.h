#pragma once

class KeyboardState
{
private:
	const uint8* keys;
	int size;
public:
	KeyboardState()noexcept
		:keys(SDL_GetKeyboardState(&size)) {}
	bool IsPressed(Scancode value)const
	{
		if(int(value)>size)
		{
			throw Error("Invalid argument KeyboardState::IsPressed requests argument of maximal size: KeyboardState::Size");
		}
		return bool(keys[int(value)]);
	}
	template<typename...T>
	bool IsPressed(Scancode value, T... args)const
	{
        return IsPressed(value)&&IsPressed(args...);
	}
	bool IsAnyPressed()const
	{
        for(int i=0;i<size;++i)
		{
			if(keys[i])
			{
				return true;
			}
		}
		return false;
	}
	size_t Size()const noexcept
	{
		return size;
	}
};
class KeymodState
{
private:
	Keymod mod_state;
public:
	KeymodState()noexcept
		:mod_state(Keymod(SDL_GetModState())) {}
	void Refresh()noexcept
	{
		mod_state=Keymod(SDL_GetModState());
	}
	bool IsPressed(Keymod modifier)noexcept
	{
		return bool(int(mod_state)&int(modifier));
	}
};
