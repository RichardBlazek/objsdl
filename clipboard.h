#pragma once

namespace Clipboard
{
    void SetText(const std::string& text)
    {
    	Error::IfNegative(SDL_SetClipboardText(text.c_str()));
    }
    std::string GetText()
    {
		return Error::IfZero(SDL_GetClipboardText());
    }
    bool HasText()
    {
    	return bool(SDL_HasClipboardText());
    }
}
