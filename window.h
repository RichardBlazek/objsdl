#pragma once

Window::Window(const std::string& title, Point pos, Point size, Flags flags)
{
	Open(title, pos, size, flags);
}
void Window::Close()noexcept
{
	if(window)
	{
		SDL_DestroyWindow(window);
		window=nullptr;
	}
}
Window::Window(Window&& init)noexcept:window(init.window)
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
///If was Window destroyed, this function open them again
///If not, function destroy the window and open them again
void Window::Open(std::string title, Point pos, Point size, Flags flags)
{
    Close();
    window=SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, uint32(flags));
    Error::IfZero(window);
}
void Window::SetIcon(Surface& image)noexcept
{
	SDL_SetWindowIcon(window, image.surface);
}