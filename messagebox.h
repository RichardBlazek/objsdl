#pragma once

void MessageBox::Show(const std::string& title, const std::string& message, Flags flag, SDL::Window* window)
{
	Error::Condition(SDL_ShowSimpleMessageBox(uint32(flag), title.c_str(), message.c_str(), window?window->window:nullptr)<0);
}

size_t MessageBox::Dialog(const std::string& title, const std::string& message, const std::vector<std::string>& buttons, size_t DefaultReturnkey, size_t DefaultEscapekey, Flags flag, ColorScheme* color, Window* window)
{
	std::vector<SDL_MessageBoxButtonData> buttonData(buttons.size());
	for(size_t i=0; i<buttons.size(); ++i)
	{
		buttonData[i].flags=0;
		if(DefaultReturnkey==i)
		{
			buttonData[i].flags|=SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
		}
		if(DefaultEscapekey==i)
		{
			buttonData[i].flags|=SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
		}
		buttonData[i].buttonid=i;
		buttonData[i].text=buttons[i].c_str();
	}
	int index=0;
	auto data=new SDL_MessageBoxData{uint32(flag),window?window->window:nullptr, title.c_str(), message.c_str(), int(buttonData.size()), buttonData.data(), color};
	if(SDL_ShowMessageBox(data, &index)<0)
	{
		delete data;
		throw SDL::Error();
	}
	delete data;
	return index;
}