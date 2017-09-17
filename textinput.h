#pragma once

namespace TextInput
{
	void Start()
	{
		SDL_StartTextInput();
	}
	void Stop()
	{
        SDL_StopTextInput();
	}
	bool IsActive()
	{
        return SDL_IsTextInputActive();
	}
	void SetCandidateListArea(const Rect& area)
	{
		SDL_Rect rect=SDL_Rect(area);
		SDL_SetTextInputRect(&rect);
	}
}