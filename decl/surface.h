#pragma once

enum class BlendMode
{
    None=SDL_BLENDMODE_NONE,
    Blend=SDL_BLENDMODE_BLEND,
    Add=SDL_BLENDMODE_ADD,
    Mod=SDL_BLENDMODE_MOD
};

class Surface: public DrawBase
{
private:
	friend DrawBase;
	friend Window;
	friend Texture;
	friend Renderer;
	friend Cursor;
	friend Font;
	friend void TextInput::SetCandidateListArea(const Rect& area);
    SDL_Surface* surface=nullptr;
    static inline uint32 BE_ToNative(uint32 num)
	{
		return SDL_SwapBE32(num);
	}
	Surface(SDL_Surface* sdl):surface(sdl){}
	static SDL_Color ColorSDL(const Color& col)
	{
		return SDL_Color{col.r, col.g, col.b, col.a};
	}
	static Color ColorSDL(const SDL_Color& col)
	{
		return Color(col.r, col.g, col.b, col.a);
	}
	static SDL_Rect RectSDL(const Rect& r)
	{
		return SDL_Rect{r.x, r.y, int32(r.w), int32(r.h)};
	}
	static Rect RectSDL(const SDL_Rect& r)
	{
		return Rect(r.x, r.y, r.w, r.h);
	}
public:
	struct ColorMasks
	{
		uint32 r, g, b, a;
	};
    Surface()=default;
    void Destroy()
	{
		if(surface)
		{
			SDL_FreeSurface(surface);
			surface=nullptr;
		}
	}
    ~Surface()noexcept
	{
		Destroy();
	}
    Surface(const Surface& init)
		:surface(Error::IfZero(SDL_ConvertSurface(init.surface, init.surface->format, 0))) {}
    Surface& operator=(const Surface& init)
	{
		Destroy();
		surface=Error::IfZero(SDL_ConvertSurface(init.surface, init.surface->format, 0));
		return *this;
	}
	Surface(Surface&& init)noexcept:surface(init.surface)
	{
		init.surface=nullptr;
	}
    Surface& operator=(Surface&& init)noexcept
	{
		Destroy();
		surface=init.surface;
		init.surface=nullptr;
		return *this;
	}
    Surface(Point size, const std::vector<Color>& colors, uint8 depth);
    Surface(Point size, const std::vector<Color>& colors, Pixel::Format format);
    Surface(Point size, uint8 depth, ColorMasks masks);
    Surface(Point size, Pixel::Format format);

    void Create(Point size, const std::vector<Color>& colors, uint8 depth);
    void Create(Point size, const std::vector<Color>& colors, Pixel::Format format);
	void Create(Point size, uint8 depth, ColorMasks masks);
	void Create(Point size, Pixel::Format format);
	static Surface LoadImg(const std::string& file)
	{
		return (Surface&&)Surface(Error::IfZero(IMG_Load(file.c_str())));
	}
	static Surface LoadXPM(char** xpm)
	{
		return (Surface&&)Surface(Error::IfZero(IMG_ReadXPMFromArray(xpm)));
	}
	void SaveAsBMP(const std::string& file)
	{
		Error::IfNegative(SDL_SaveBMP(surface, file.c_str()));
	}
    uint8 BytesPerPixel()const noexcept
	{
		return surface->format->BytesPerPixel;
	}
    uint8 BitsPerPixel()const noexcept
	{
		return surface->format->BitsPerPixel;
	}
    void SetPalette(const std::vector<Color>& colors)
	{
		if(surface->format->palette)
		{
			SDL_FreePalette(surface->format->palette);
		}
		surface->format->palette=Error::IfZero(SDL_AllocPalette(colors.size()));
		for(size_t i=0; i<size_t(surface->format->palette->ncolors); ++i)
		{
			surface->format->palette->colors[i]=ColorSDL(colors[i]);
		}
	}
    ColorMasks Masks()const noexcept
	{
		return ColorMasks{surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask};
	}
private:
	uint8* Index(const Point& xy)const noexcept
	{
		return ((uint8*)surface->pixels)+xy.y*BytesPerLine()+xy.x*BytesPerPixel();
	}
	uint32 PixelRawValue(const Point& xy)const
	{
		if(xy.x<0||xy.x>=surface->w||xy.y<0||xy.y>=surface->h)
			throw Error("Pixel index out of range");
		auto ptr=Index(xy);
		switch(BytesPerPixel())
		{
			case 1:
				return *ptr;
			case 2:
				return *(uint16*)ptr;
			case 3:
				return IsBigEndian?ptr[0]<<16|ptr[1]<<8|ptr[2]:ptr[2]<<16|ptr[1]<<8|ptr[0];
			case 4:
				return *(uint32*)ptr;
		}
		throw Error("Invalid value of Surface::BytesPerPixel()");
	}
	void SetPixelRawValue(const Point& xy, uint32 value)noexcept
	{
		if(xy.x<0||xy.x>surface->w||xy.y<0||xy.y>surface->h)return;
		auto ptr=Index(xy);
		switch(BytesPerPixel())
		{
			case 1:
				*ptr=uint8(value);
				break;
			case 2:
				*(uint16*)ptr=uint16(value);
				break;
			case 3:
				if(IsBigEndian)
				{
					ptr[0]=uint8(value>>16);
					ptr[1]=uint8(value>>8);
					ptr[2]=uint8(value);
				}
				else
				{
					ptr[2]=uint8(value>>16);
					ptr[1]=uint8(value>>8);
					ptr[0]=uint8(value);
				}
				break;
			case 4:
				*(uint32*)ptr=value;
				break;
		}
	}
	Color IndexPalette(size_t i)const noexcept
	{
		return ColorSDL(surface->format->palette->colors[i]);
	}
public:
	size_t PaletteSize()const noexcept
	{
		return surface->format->palette->ncolors;
	}
	uint8& Index8(const Point& xy)
	{
		if(BitsPerPixel()!=8)
		{
			throw Error("Surface::Index8>This surface is not 8-bit!");
		}
		return *Index(xy);
	}
	Color operator[](const Point& xy)const
	{
		Color result;
		SDL_GetRGBA(PixelRawValue(xy), surface->format, &result.r, &result.g, &result.b, &result.a);
		return result;
	}
	void Repaint(const Color& col);
	using DrawBase::Draw;
	using DrawBase::DrawBorder;
	void Draw(const Point& xy, const Color& col)
	{
		SetPixelRawValue(xy, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a));
	}
    void Draw(const Line& line, const Color& col);
    void DrawBorder(const Rect& rectangle, const Color& col);
    void Draw(const Rect& rectangle, const Color& col);
    uint32 BytesPerLine()const noexcept
	{
		return surface->pitch;
	}
    uint32 Width()const noexcept
	{
		return surface->w;
	}
    uint32 Height()const noexcept
	{
		return surface->h;
	}
	Point Size()const noexcept
	{
		return Point(Width(), Height());
	}
    bool SetClipRect(const Rect& rectangle)noexcept
	{
		SDL_Rect rect=RectSDL(rectangle);
		return SDL_SetClipRect(surface, &rect);
	}
    void ClipRect(const Rect& rectangle)noexcept
	{
		SDL_Rect rect=RectSDL(rectangle);
		return SDL_GetClipRect(surface, &rect);
	}
    void Blit(Surface&, Rect, Rect);
    void Draw(Surface&, Rect, Rect);
    void EnableColorKey(const Color& col);
    void DisableColorKey(const Color& col);
    void SetRGBMod(const ColorRGB& col);
    void SetAlphaMod(uint8 alpha);
    void SetRGBAMod(const Color& col);
    void SetBlendMode(BlendMode mode);
    bool MustLock()const noexcept;
    void Lock();
    void Unlock()noexcept;
    void EnableRLE();
    void DisableRLE();
    Pixel::Format Format()const noexcept
	{
        return Pixel::Format(surface->format->format);
	}
	Surface Convert(Pixel::Format desired)
	{
		return (Surface&&)Surface(SDL_ConvertSurfaceFormat(surface,uint32(desired),0));
	}
};