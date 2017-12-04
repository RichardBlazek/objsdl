#pragma once

Window::Window(const std::string& title, Point pos, Point size, Flags flags, Renderer::Type render_flags, int index)
{
	Open(title, pos, size, flags, render_flags, index);
}
void Window::Close()noexcept
{
	if(window)
	{
		rend.Destroy();
		SDL_DestroyWindow(window);
		window=nullptr;
	}
}
Window::Window(Window&& init)noexcept
	:window(init.window), rend(func::Move(init.rend))
{
	init.window=nullptr;
}
Window& Window::operator=(Window&& init)noexcept
{
	Close();
	window=init.window;
	init.window=nullptr;
	rend=func::Move(init.rend);
	return *this;
}
///If was Window destroyed, this function open them again
///If not, function destroy the window and open them again
void Window::Open(const std::string& title, Point pos, Point size, Flags flags, Renderer::Type render_flags, int index)
{
    Close();
    window=SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, uint32(flags));
    Error::IfZero(window);
    rend.Create(*this, render_flags, index);
}
void Window::SetIcon(Surface& image)noexcept
{
	SDL_SetWindowIcon(window, image.surface);
}