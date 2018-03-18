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
	class LockWriter
	{
	private:
		friend Texture;
		Pixel::Format format;
        uint8* pixels;
        uint32 w, h;
        void SetPixelRawValue(Point pos, uint32 value)
        {
        	auto ptr=pixels+pos.x*format.BytesPerPixel()+w*pos.y*format.BytesPerPixel();
        	switch(format.BytesPerPixel())
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
	public:
		LockWriter(Pixel::Format format, uint8* pixels, uint32 w, uint32 h)
			:format(format), pixels(pixels), w(w), h(h) {}
		void SetPixel(Point pos, Color col)
		{
			SDL_PixelFormat f;
			f.format=format;
            SetPixelRawValue(pos, SDL_MapRGBA(&f, col.r, col.g, col.b, col.a));
		}
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
		Access result;
		Error::IfNegative(SDL_QueryTexture(texture, nullptr, (int*)&result, nullptr, nullptr));
		return result;
	}
    Pixel::Format Format()const
	{
		Pixel::Format result;
		Error::IfNegative(SDL_QueryTexture(texture, (uint32*)&result, nullptr, nullptr, nullptr));
		return result;
	}
    void Update(Surface pixels, Point pos=Point())
	{
		auto surf=pixels.Convert(Format());
		SDL_Rect rectangle{pos.x, pos.y, surf.Size().x, surf.Size().y};
		Error::IfNegative(SDL_UpdateTexture(texture, &rectangle, surf.surface->pixels, surf.BytesPerLine()));
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
	LockWriter Lock(const Rect& limit)
	{
        Pixel::Format format=Format();
        Point size=Size();
        SDL_Rect rect=Surface::RectSDL(limit);
        void* pixels=nullptr;
        int bpl=0;

        Error::IfNegative(SDL_LockTexture(texture, &rect, &pixels, &bpl));

        return LockWriter(format, (uint8*)pixels, size.x, size.y);
	}
};
