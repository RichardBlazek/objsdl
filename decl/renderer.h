#pragma once

///Object Renderer
class Renderer: public NonCopyable, public DrawBase
{
public:
	enum class Flags: uint32
	{
		None=0x0,
		Software=SDL_RENDERER_SOFTWARE,
		Accelerated=SDL_RENDERER_ACCELERATED,
		PresentVSync=SDL_RENDERER_PRESENTVSYNC,
		TargetTexture=SDL_RENDERER_TARGETTEXTURE
	};
private:
	SDL_Renderer* renderer=nullptr;

	void SetDrawColor(const Color& col)
	{
		Error::IfNegative(SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a));
	}

	void Create(const Window& window, Flags flags, int index);
public:
	using DrawBase::Draw;
	using DrawBase::DrawBorder;
	friend Texture;
	friend Window;
	//Types----------------------------------------------------------
	enum class Flip
	{
		None=SDL_FLIP_NONE,
		Horizontal=SDL_FLIP_HORIZONTAL,
		Vertical=SDL_FLIP_VERTICAL
	};
	Renderer()=default;
	Renderer(Renderer&& init):renderer(init.renderer)
	{
		init.renderer=nullptr;
	}
	Renderer& operator=(Renderer&& init)
	{
		renderer=init.renderer;
		init.renderer=nullptr;
		return *this;
	}

	Renderer(Surface& surf)
		:renderer(SDL_CreateSoftwareRenderer(surf.surface))
	{
		Error::IfZero(renderer);
	}

	void Destroy()noexcept
	{
		if(renderer)
		{
			SDL_DestroyRenderer(renderer);
			renderer=nullptr;
		}
	}

	~Renderer()noexcept
	{
		Destroy();
	}

	//Drawing--------------------------------------------------------
	void Draw(const Point& point, const Color& col)
	{
		SetDrawColor(col);
		Error::IfNegative(SDL_RenderDrawPoint(renderer, point.x, point.y));
	}
	void Draw(const Line& line, const Color& col)
	{
		SetDrawColor(col);
		Error::IfNegative(SDL_RenderDrawLine(renderer, line.begin.x,line.begin.y, line.end.x,line.end.y));
	}
	void DrawBorder(const Rect& rectangle, const Color& col)
	{
		SetDrawColor(col);
		SDL_Rect rect=Surface::RectSDL(rectangle);
		Error::IfNegative(SDL_RenderDrawRect(renderer, &rect));
	}
	void Draw(const Rect& rectangle, const Color& col)
	{
		SetDrawColor(col);
		SDL_Rect rect=Surface::RectSDL(rectangle);
		Error::IfNegative(SDL_RenderFillRect(renderer, &rect));
	}
	void Repaint(const Color& col)
	{
		SetDrawColor(col);
		Error::IfNegative(SDL_RenderClear(renderer));
	}
	///Draw image to Renderer
	void Draw(Texture& texture, Rect source, Rect destination);
	void Draw(Surface& surface, Rect source, Rect destination);


	void Draw(Texture& texture, Rect source, Rect destination, double angle, Point center, Flip flip);
	void Draw(Surface& surface, Rect source, Rect destination, double angle, Point center, Flip flip);

	void Draw(Texture& texture, Rect source, Rect destination, double angle, Flip flip);
	void Draw(Surface& surface, Rect source, Rect destination, double angle, Flip flip);

	//Other----------------------------------------------------------
	void Show()noexcept
	{
		SDL_RenderPresent(renderer);
	}
	void SetTarget(Texture& texture);
	void SetBlendMode(SDL::BlendMode mode)
	{
		Error::Condition(SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode(mode))<0);
	}
	SDL::BlendMode BlendMode()
	{
		SDL_BlendMode mode;
		Error::IfNegative(SDL_GetRenderDrawBlendMode(renderer, &mode));
		return SDL::BlendMode(mode);
	}
	void SetViewport(const Rect& rectangle)
	{
		SDL_Rect rect=Surface::RectSDL(rectangle);
		Error::IfNegative(SDL_RenderSetViewport(renderer, &rect));
	}
	void SetViewportToDefault()
	{
		Error::IfNegative(SDL_RenderSetViewport(renderer, nullptr));
	}
	Rect Viewport()noexcept
	{
		SDL_Rect result;
		SDL_RenderGetViewport(renderer, &result);
		return Surface::RectSDL(result);
	}
	void SetClipRect(const Rect& cliprect)
	{
		SDL_Rect rect=Surface::RectSDL(cliprect);
		Error::IfNegative(SDL_RenderSetClipRect(renderer, &rect));
	}
	void DisableClipping()
	{
		Error::IfNegative(SDL_RenderSetClipRect(renderer, nullptr));
	}
	bool IsClipEnabled()
	{
		return bool(SDL_RenderIsClipEnabled(renderer));
	}
	Rect ClipRect()noexcept
	{
		SDL_Rect result;
		SDL_RenderGetClipRect(renderer, &result);
		return Surface::RectSDL(result);
	}
	void SetLogicalSize(Point newsize)
	{
		Error::IfNegative(SDL_RenderSetLogicalSize(renderer, newsize.x, newsize.y));
	}
	Point LogicalSize()noexcept
	{
		Point result;
		SDL_RenderGetLogicalSize(renderer, &result.x, &result.y);
		return result;
	}
	void EnableIntegerScale()
	{
		Error::IfNegative(SDL_RenderSetIntegerScale(renderer, SDL_TRUE));
	}
	void DisableIntegerScale()
	{
		Error::IfNegative(SDL_RenderSetIntegerScale(renderer, SDL_FALSE));
	}
	void SetScale(geometry::Point<float> xy)
	{
		Error::IfNegative(SDL_RenderSetScale(renderer, xy.x, xy.y));
	}
	geometry::Point<float> Scale()
	{
		geometry::Point<float> result;
		SDL_RenderGetScale(renderer, &result.x, &result.y);
		return result;
	}
	Point Size()
	{
		Point result;
		Error::IfNegative(SDL_GetRendererOutputSize(renderer, &result.x, &result.y));
		return result;
	}
	static uint32 CountOfDrivers()
	{
		return Error::IfNegative(SDL_GetNumRenderDrivers());
	}
	std::vector<Pixel::Format> TextureFormats()
	{
		SDL_RendererInfo info;
		Error::IfNegative(SDL_GetRendererInfo(renderer, &info));
		std::vector<Pixel::Format> result;
		for(uint32 i=0;i<info.num_texture_formats;++i)
		{
			result.push_back(Pixel::Format(info.texture_formats[i]));
		}
		return func::Move(result);
	}
	Flags Type()
	{
		SDL_RendererInfo info;
		Error::IfNegative(SDL_GetRendererInfo(renderer, &info));
        return Flags(info.flags);
	}
	Point MaxTextureSize()
	{
		SDL_RendererInfo info;
		Error::IfNegative(SDL_GetRendererInfo(renderer, &info));
		return Point(info.max_texture_width, info.max_texture_height);
	}
    std::string Name()
    {
		SDL_RendererInfo info;
		Error::IfNegative(SDL_GetRendererInfo(renderer, &info));
		return std::string(info.name);
    }
	bool TargetSupported()
	{
        return bool(SDL_RenderTargetSupported(renderer));
	}
	Surface ReadPixels(Rect from, Pixel::Format format)
	{
		Surface out(from.Size(), format);
		SDL_Rect limit=Surface::RectSDL(from);
        Error::IfNegative(SDL_RenderReadPixels(renderer, &limit, uint32(format), out.surface->pixels, out.BytesPerLine()));
        return (Surface&&)out;
	}
};

Renderer::Flags operator|(Renderer::Flags a, Renderer::Flags b)
{
	return Renderer::Flags(uint32(a)|uint32(b));
}
Renderer::Flags operator&(Renderer::Flags a, Renderer::Flags b)
{
	return Renderer::Flags(uint32(a)&uint32(b));
}
Renderer::Flags operator^(Renderer::Flags a, Renderer::Flags b)
{
	return Renderer::Flags(uint32(a)^uint32(b));
}
Renderer::Flags operator~(Renderer::Flags a)
{
	return Renderer::Flags(~uint32(a));
}
Renderer::Flags operator|=(Renderer::Flags& a, Renderer::Flags b)
{
	return a=a|b;
}
Renderer::Flags operator&=(Renderer::Flags& a, Renderer::Flags b)
{
	return a=a&b;
}
Renderer::Flags operator^=(Renderer::Flags& a, Renderer::Flags b)
{
	return a=a^b;
}
