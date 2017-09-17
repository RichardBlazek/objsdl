#pragma once

namespace Clipboard
{
    void SetText(const std::string& text)
    {
    	Error::Condition(SDL_SetClipboardText(text.c_str())<0);
    }
    std::string GetText()
    {
    	const char* txt=SDL_GetClipboardText();
		Error::IfZero(txt);
		return txt;
    }
    bool HasText()
    {
    	return bool(SDL_HasClipboardText());
    }
}
