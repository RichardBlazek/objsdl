#pragma once

namespace ScreenSaver
{
	void Enable()
	{
		SDL_EnableScreenSaver();
	}
	void Disable()
	{
		SDL_DisableScreenSaver();
	}
	bool IsEnabled()
	{
		return SDL_IsScreenSaverEnabled();
	}
}
