#pragma once

void Window::Close()noexcept
{
	if(window)
	{
		SDL_DestroyWindow(window);
		window=nullptr;
	}
}
Window::Window(Window&& init)noexcept :window(init.window)
{
	init.window=nullptr;
}
Window& Window::operator=(Window&& init)noexcept
{
	Close();
	window=init.window;
	init.window=nullptr;
	return *this;
}

Window::Window(const std::string& title, Rect pos, Flags flags)
	:window(Error::IfZero(SDL_CreateWindow(title.c_str(), pos.x, pos.y, pos.w, pos.h, uint32(flags)))) {}

void Window::SetIcon(Surface& image)noexcept
{
	SDL_SetWindowIcon(window, image.surface);
}