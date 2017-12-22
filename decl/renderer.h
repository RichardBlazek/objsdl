#pragma once

///Object Renderer
class Renderer: public NonCopyable, public DrawBase
{
public:
	enum class Type : uint32
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

	void Create(const Window& window, Type flags, int index);
public:
	friend Texture;
	friend Window;
	//Types----------------------------------------------------------
	enum class Flip
	{
		None=SDL_FLIP_NONE,
		Horizontal=SDL_FLIP_HORIZONTAL,
		Vertical=SDL_FLIP_VERTICAL
	};
	struct Info
	{
		std::string Name;
		Type Flags;
		Pixel::Format TextureFormats[16];
		uint32 NumberOfTextureFormats;
		int32 MaxTextureWidth, MaxTextureHeight;
		Info()=default;
		Info(const std::string& name, Type flags, Pixel::Format* textureformats, uint32 num_textureformats, int32 max_texturewidth, int32 max_textureheight)
			:Name(name), Flags(flags), NumberOfTextureFormats(num_textureformats),
				MaxTextureWidth(max_texturewidth), MaxTextureHeight(max_textureheight)
		{
			for(uint32 i=0;i<num_textureformats;++i)
			{
                TextureFormats[i]=Pixel::Format(textureformats[i]);
			}
		}
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
	void SetBlendMode(BlendMode mode)
	{
		Error::Condition(SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode(mode))<0);
	}
	BlendMode GetBlendMode()
	{
		SDL_BlendMode mode;
		Error::IfNegative(SDL_GetRenderDrawBlendMode(renderer, &mode));
		return BlendMode(mode);
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
	Rect GetViewport()noexcept
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
	Rect GetClipRect()noexcept
	{
		SDL_Rect result;
		SDL_RenderGetClipRect(renderer, &result);
		return Surface::RectSDL(result);
	}
	void SetLogicalSize(Point newsize)
	{
		Error::IfNegative(SDL_RenderSetLogicalSize(renderer, newsize.x, newsize.y));
	}
	Point GetLogicalSize()noexcept
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
	geometry::Point<float> GetScale()
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
	Info GetInfo()
	{
		SDL_RendererInfo renderinfo;
		Error::IfNegative(SDL_GetRendererInfo(renderer, &renderinfo));
		return Info(renderinfo.name, Type(renderinfo.flags), reinterpret_cast<Pixel::Format*>(renderinfo.texture_formats), renderinfo.num_texture_formats, renderinfo.max_texture_width, renderinfo.max_texture_height);
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

Renderer::Type operator|(Renderer::Type a, Renderer::Type b)
{
	return Renderer::Type(uint32(a)|uint32(b));
}
Renderer::Type operator&(Renderer::Type a, Renderer::Type b)
{
	return Renderer::Type(uint32(a)&uint32(b));
}
Renderer::Type operator^(Renderer::Type a, Renderer::Type b)
{
	return Renderer::Type(uint32(a)^uint32(b));
}
Renderer::Type operator~(Renderer::Type a)
{
	return Renderer::Type(~uint32(a));
}
Renderer::Type operator|=(Renderer::Type& a, Renderer::Type b)
{
	return a=a|b;
}
Renderer::Type operator&=(Renderer::Type& a, Renderer::Type b)
{
	return a=a&b;
}
Renderer::Type operator^=(Renderer::Type& a, Renderer::Type b)
{
	return a=a^b;
}
