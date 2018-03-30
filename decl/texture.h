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
	friend Renderer;
    Texture()=default;
    ~Texture()noexcept
	{
		Close();
	}
    Texture(Texture&& src)noexcept
		:texture(src.texture)
	{
		src.texture=nullptr;
	}
    Texture& operator=(Texture&& src)noexcept
    {
    	Close();
    	texture=src.texture;
    	src.texture=nullptr;
		return *this;
	}
    void Close()noexcept
	{
		if(texture)
		{
			SDL_DestroyTexture(texture);
			texture=nullptr;
		}
	}

	bool IsOpened()const noexcept
	{
		return bool(texture);
	}

	Point Size()const
	{
		Point result;
		Error::IfNegative(SDL_QueryTexture(texture, nullptr, nullptr, &result.x, &result.y));
		return result;
	}
	Access GetAccess()const
	{
		int result;
		Error::IfNegative(SDL_QueryTexture(texture, nullptr, &result, nullptr, nullptr));
		return Access(result);
	}
    Pixel::Format Format()const
	{
		uint32 result;
		Error::IfNegative(SDL_QueryTexture(texture, &result, nullptr, nullptr, nullptr));
		return Pixel::Format(result);
	}
    void Update(const Surface& pixels, Rect area)
	{
		area=(area*Rect(pixels.Size())).ValueOr(Rect());
		SDL_Rect rectangle{area.x, area.y, int(area.w), int(area.h)};
		Error::IfNegative(SDL_UpdateTexture(texture, &rectangle, pixels.Index(area.Position()), pixels.BytesPerLine()));
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
	class LockWriter: public NonCopyable
	{
	private:
		friend Texture;
		Pixel::Format format;
        uint8* pixels;
        Point size;
        void SetPixelRawValue(Point pos, uint32 value)
        {
			auto dst=pixels+(pos.x+pos.y*size.x)*format.BytesPerPixel();
			switch(format.BytesPerPixel())
			{
				case 1:
					*dst=uint8(value);
					break;
				case 2:
					*(uint16*)dst=uint16(value);
					break;
				case 3:
					if(IsBigEndian)
					{
						dst[0]=uint8(value>>16);
						dst[1]=uint8(value>>8);
						dst[2]=uint8(value);
					}
					else
					{
						dst[2]=uint8(value>>16);
						dst[1]=uint8(value>>8);
						dst[0]=uint8(value);
					}
					break;
				case 4:
					*(uint32*)dst=value;
					break;
			}
        }
		LockWriter(Pixel::Format format, uint8* pixels, Point size)
			:format(format), pixels(pixels), size(size) {}
	public:
		void SetPixel(Point pos, Color col)
		{
        	if(pos.x>=0&&pos.y>=0&&pos.x<size.x&&pos.y<size.y)
			{
				auto f=SDL_AllocFormat(format);
				SetPixelRawValue(pos, SDL_MapRGBA(f, col.r, col.g, col.b, col.a));
				SDL_FreeFormat(f);
			}
		}
	};
	template<typename F>
	void Lock(const Rect& limit, F write_func)
	{
        SDL_Rect rect=Surface::RectSDL(limit);
        void* pixels=nullptr;
        int bpl=0;

        Error::IfNegative(SDL_LockTexture(texture, &rect, &pixels, &bpl));

        write_func(LockWriter(Format(), (uint8*)pixels, Size()));
        SDL_UnlockTexture(texture);
	}
};
