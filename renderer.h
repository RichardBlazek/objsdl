#pragma once

void Renderer::Create(const Window& window, Type flags, int index)
{
	Destroy();
	renderer=SDL_CreateRenderer(window.window, index, uint32(flags));
	Error::IfZero(renderer);
}

void Renderer::Draw(Texture& texture)
{
	Error::Condition(SDL_RenderCopy(renderer, texture.texture, nullptr, nullptr)!=0);
}
void Renderer::Draw(Texture& texture, std::nullptr_t, const Rect& destination)
{
	SDL_Rect r=destination;
	Error::Condition(SDL_RenderCopy(renderer, texture.texture, nullptr, &r)!=0);
}
void Renderer::Draw(Texture& texture, const Rect& source, std::nullptr_t)
{
	SDL_Rect r=source;
	Error::Condition(SDL_RenderCopy(renderer, texture.texture, &r, nullptr)!=0);
}
void Renderer::Draw(Texture& texture, const Rect& source, const Rect& destination)
{
	SDL_Rect r1=source, r2=destination;
	Error::Condition(SDL_RenderCopy(renderer, texture.texture, &r1, &r2)!=0);
}

void Renderer::Draw(Surface& surface)
{
	Texture texture(*this, surface);
	Draw(texture);
}
void Renderer::Draw(Surface& surface, std::nullptr_t, const Rect& destination)
{
	Texture texture(*this, surface);
	Draw(texture, nullptr, destination);
}
void Renderer::Draw(Surface& surface, const Rect& source, std::nullptr_t)
{
	Texture texture(*this, surface);
	Draw(texture, source, nullptr);
}
void Renderer::Draw(Surface& surface, const Rect& source, const Rect& destination)
{
	Texture texture(*this, surface);
	Draw(texture, source, destination);
}


void Renderer::Draw(Texture& texture, const Rect* source, const Rect* destination, double angle, Point center, Flip flip)
{
	SDL_Rect r1=source?*source:Rect(), r2=destination?*destination:Rect();
	SDL_Point tmp{center.x, center.y};
    Error::Condition(SDL_RenderCopyEx(renderer, texture.texture, source?&r1:nullptr, destination?&r2:nullptr, angle, &tmp, SDL_RendererFlip(flip))!=0);
}
void Renderer::Draw(Surface& surface, const Rect* source, const Rect* destination, double angle, Point center, Flip flip)
{
	Texture texture(*this, surface);
	Draw(texture, source, destination, angle, center, flip);
}
void Renderer::Draw(Texture& texture, const Rect* source, const Rect* destination, double angle, Flip flip)
{
	SDL_Rect r1=source?*source:Rect(), r2=destination?*destination:Rect();
    Error::Condition(SDL_RenderCopyEx(renderer, texture.texture, source?&r1:nullptr,destination?&r2:nullptr, angle, nullptr, SDL_RendererFlip(flip))!=0);
}
void Renderer::Draw(Surface& surface, const Rect* source, const Rect* destination, double angle, Flip flip)
{
	Texture texture(*this, surface);
	Draw(texture, source, destination, angle, flip);
}
void Renderer::SetTarget(Texture& texture)
{
	Error::IfNegative(SDL_SetRenderTarget(renderer, texture.texture));
}