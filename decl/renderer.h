#pragma once

///Object Renderer
class Renderer: public NonCopyable
{
private:
	SDL_Renderer* renderer=nullptr;
	///Set Draw Color of Renderer
	void SetDrawColor(const Color& col)
	{
		Error::IfNegative(SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a));
	}
public:
	//Types----------------------------------------------------------
	enum class Flip
	{
		None=SDL_FLIP_NONE,
		Horizontal=SDL_FLIP_HORIZONTAL,
		Vertical=SDL_FLIP_VERTICAL
	};
	enum class Type : uint32
	{
		None=0x0,
		Software=SDL_RENDERER_SOFTWARE,
		Accelerated=SDL_RENDERER_ACCELERATED,
		PresentVSync=SDL_RENDERER_PRESENTVSYNC,
		TargetTexture=SDL_RENDERER_TARGETTEXTURE
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
	friend Texture;

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

	Renderer(const Window& window, Type flags=Type::None, int index=-1)
		:renderer(SDL_CreateRenderer(window.window, index, uint32(flags)))
	{
		Error::IfZero(renderer);
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
	//If was Renderer destroyed, this function create them again
	//If not, function destroy the renderer and create them again
	void Create(const Window& window, Type flags=Type::None, int index=-1);

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
		SDL_Rect rect=rectangle;
		Error::IfNegative(SDL_RenderDrawRect(renderer, &rect));
	}
	void Draw(const Rect& rectangle, const Color& col)
	{
		SetDrawColor(col);
		SDL_Rect rect=rectangle;
		Error::IfNegative(SDL_RenderFillRect(renderer, &rect));
	}
	void DrawBorder(const Circle& circle, const Color& color)
	{
		Point pos=circle.center;
		float angle=0;
		float angle_stepsize=0.001;
		while(angle<2*pi)
		{
			pos.x=circle.center.x+circle.radius*SDL_cos(angle);
			pos.y=circle.center.y+circle.radius*SDL_sin(angle);
			Draw(pos, color);
			angle+=angle_stepsize;
		}
	}
	void Repaint(const Color& col)
	{
		SetDrawColor(col);
		Error::IfNegative(SDL_RenderClear(renderer));
	}
	///Draw image to Renderer
	void Draw(Texture& texture);
	void Draw(Texture& texture, std::nullptr_t, const Rect& destination);
	void Draw(Texture& texture, const Rect& source, std::nullptr_t);
	void Draw(Texture& texture, const Rect& source, const Rect& destination);

	void Draw(Surface& surface);
	void Draw(Surface& surface, std::nullptr_t, const Rect& destination);
	void Draw(Surface& surface, const Rect& source, std::nullptr_t);
	void Draw(Surface& surface, const Rect& source, const Rect& destination);


	void Draw(Texture& texture, const Rect* source, const Rect* destination, double angle, Point center, Flip flip);
	void Draw(Surface& surface, const Rect* source, const Rect* destination, double angle, Point center, Flip flip);

	void Draw(Texture& texture, const Rect* source, const Rect* destination, double angle, Flip flip);
	void Draw(Surface& surface, const Rect* source, const Rect* destination, double angle, Flip flip);

	//Text drawing---------------------------------------------------
	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
	{
		Surface textimage=font.Render(u8text, textcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
	{
		Surface textimage=font.Render(u16text, textcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void Draw(Font& font, char16_t character, const Color& textcolor, Point dst)
	{
		Surface textimage=font.Render(character, textcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst, const Color& backgroundcolor)
	{
		Surface textimage=font.Render(u8text, textcolor, backgroundcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst, const Color& backgroundcolor)
	{
		Surface textimage=font.Render(u16text, textcolor, backgroundcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void Draw(Font& font, char16_t character, const Color& textcolor, Point dst, const Color& backgroundcolor)
	{
		Surface textimage=font.Render(character, textcolor, backgroundcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
	{
		Surface textimage=font.RenderFast(u8text, textcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
	{
		Surface textimage=font.RenderFast(u16text, textcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	void DrawFast(Font& font, char16_t character, const Color& textcolor, Point dst)
	{
		Surface textimage=font.RenderFast(character, textcolor);
		Rect destination(dst, textimage.Size());
		Draw(textimage, nullptr, destination);
	}
	///Centred text-----------------------------------------------------------------------------------------------
	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Rect dst)
	{
		Draw(font, u8text, textcolor, dst.Center()-font.TextSize(u8text)/2);
	}
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst)
	{
		Draw(font, u16text, textcolor, dst.Center()-font.TextSize(u16text)/2);
	}
	void Draw(Font& font, char16_t character, const Color& textcolor, Rect dst)
	{
		Draw(font, character, textcolor, dst.Center()-font.TextSize(character)/2);
	}
	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Rect dst, const Color& backgroundcolor)
	{
		Draw(font, u8text, textcolor, dst.Center()-font.TextSize(u8text)/2, backgroundcolor);
	}
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst, const Color& backgroundcolor)
	{
		Draw(font, u16text, textcolor, dst.Center()-font.TextSize(u16text)/2, backgroundcolor);
	}
	void Draw(Font& font, char16_t character, const Color& textcolor, Rect dst, const Color& backgroundcolor)
	{
		Draw(font, character, textcolor, dst.Center()-font.TextSize(character)/2, backgroundcolor);
	}
	void DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Rect dst)
	{
		Draw(font, u8text, textcolor, dst.Center()-font.TextSize(u8text)/2);
	}
	void DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst)
	{
		Draw(font, u16text, textcolor, dst.Center()-font.TextSize(u16text)/2);
	}
	void DrawFast(Font& font, char16_t character, const Color& textcolor, Rect dst)
	{
		Draw(font, character, textcolor, dst.Center()-font.TextSize(character)/2);
	}
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
		SDL_Rect rect=rectangle;
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
		return Rect(result);
	}
	void SetClipRect(const Rect& cliprect)
	{
		SDL_Rect rect=cliprect;
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
		return Rect(result);
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
	Point GetOutputSize()
	{
		Point result;
		Error::IfNegative(SDL_GetRendererOutputSize(renderer, &result.x, &result.y));
		return result;
	}
	static uint32 CountOfDrivers()
	{
		int x=SDL_GetNumRenderDrivers();
		Error::IfNegative(x);
		return x;
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
	void ReadPixels(Surface& out, Point from=Point(0,0))
	{
		SDL_Rect limit{from.x,from.y, int(out.Width()), int(out.Height())};
        Error::IfNegative(SDL_RenderReadPixels(renderer, &limit, uint32(out.GetFormat()), out.surface->pixels, out.BytesPerLine()));
	}
};
//Bitwise operators for Renderer enums---------------------
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
