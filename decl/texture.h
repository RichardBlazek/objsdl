#pragma once

class Texture: public NonCopyable
{
private:
    SDL_Texture* texture=nullptr;
public:
	enum class Access
	{
        Static=SDL_TEXTUREACCESS_STATIC,
        Streaming=SDL_TEXTUREACCESS_STREAMING,
        Target=SDL_TEXTUREACCESS_TARGET
	};
	enum class Modulate: uint8
	{
		None=SDL_TEXTUREMODULATE_NONE,
		Color=SDL_TEXTUREMODULATE_COLOR,
		Alpha=SDL_TEXTUREMODULATE_ALPHA
	};
	struct LockedData
	{
        void* pixels;
        uint32 bytes_per_line;
	};
	friend Renderer;
    Texture()=default;
    ~Texture()noexcept
	{
		Destroy();
	}
    Texture(Texture&& src)noexcept
		:texture(src.texture)
	{
		src.texture=nullptr;
	}
    Texture& operator=(Texture&& src)noexcept
    {
		texture=src.texture;
		src.texture=nullptr;
		return *this;
	}
    void Destroy()noexcept
	{
		if(texture)
		{
			SDL_DestroyTexture(texture);
			texture=nullptr;
		}
	}
	Point Size()const
	{
		Point result;
		Error::IfNegative(SDL_QueryTexture(texture, nullptr, nullptr, &result.x, &result.y));
		return result;
	}
	Access GetAccess()const
	{
		Access result;
		Error::IfNegative(SDL_QueryTexture(texture, nullptr, (int*)&result, nullptr, nullptr));
		return result;
	}
    Pixel::Format GetPixelFormat()const
	{
		Pixel::Format result;
		Error::IfNegative(SDL_QueryTexture(texture, (uint32*)&result, nullptr, nullptr, nullptr));
		return result;
	}
    void Update(const Surface& pixels, Point pos=Point())
	{
		SDL_Rect rectangle{pos.x, pos.y, int(pixels.Width()), int(pixels.Height())};
		Error::IfNegative(SDL_UpdateTexture(texture, &rectangle, pixels.surface->pixels, pixels.BytesPerLine()));
	}
	void SetRGBMod(const Color& mod)
	{
		Error::IfNegative(SDL_SetTextureColorMod(texture, mod.r, mod.g, mod.b));
	}
	void SetAlphaMod(uint8 alpha)
	{
		Error::IfNegative(SDL_SetTextureAlphaMod(texture, alpha));
	}
	void SetRGBAMod(const Color& mod)
	{
		SetRGBMod(mod);
		SetAlphaMod(mod.a);
	}
	void SetBlendMode(BlendMode mode)
	{
		Error::IfNegative(SDL_SetTextureBlendMode(texture, SDL_BlendMode(mode)));
	}
	LockedData Lock(const Rect& limit)
	{
        LockedData result;
        SDL_Rect rect=Surface::RectSDL(limit);
        int bpl=result.bytes_per_line;
        Error::IfNegative(SDL_LockTexture(texture, &rect, &result.pixels, &bpl));
        result.bytes_per_line=bpl;
        return result;
	}
};
