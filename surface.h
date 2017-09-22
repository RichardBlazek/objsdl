#pragma once

Surface::Surface(Point size, const std::vector<Color>& colors, uint8 depth)
{
	Create(size, colors, depth);
}
Surface::Surface(Point size, const std::vector<Color>& colors, Pixel::Format format)
{
	Create(size, colors, format);
}
Surface::Surface(Point size, uint8 depth, Masks masks)
{
	Create(size, depth, masks);
}
Surface::Surface(Point size, Pixel::Format format)
{
	Create(size, format);
}

void Surface::Create(Point size, const std::vector<Color>& colors, uint8 depth)
{
    Destroy();
    surface=SDL_CreateRGBSurface(0,size.x,size.y,depth, 0, 0, 0, 0);
	Error::IfZero(surface);
	SetPalette(colors);
}
void Surface::Create(Point size, const std::vector<Color>& colors, Pixel::Format format)
{
	Destroy();
    surface=SDL_CreateRGBSurfaceWithFormat(0,size.x,size.y, Pixel::BitSize(format), uint32(format));
	Error::IfZero(surface);
	SetPalette(colors);
}
void Surface::Create(Point size, uint8 depth, Masks masks)
{
    Destroy();
    surface=SDL_CreateRGBSurface(0,size.x,size.y,depth, BE_ToNative(masks.r), BE_ToNative(masks.g), BE_ToNative(masks.b), BE_ToNative(masks.a));
	Error::IfZero(surface);
}
void Surface::Create(Point size, Pixel::Format format)
{
    Destroy();
    surface=SDL_CreateRGBSurfaceWithFormat(0,size.x,size.y, Pixel::BitSize(format), uint32(format));
	Error::IfZero(surface);
}
void Surface::Blit(Surface& second, const Rect* source, const Rect* destination)
{
	SDL_Rect src=source?*source:Rect(), dst=destination?*destination:Rect();
    Error::Condition(SDL_BlitSurface(second.surface, source?&src:nullptr, surface, destination?&dst:nullptr)<0);
}
void Surface::Draw(Surface& second, const Rect* source, const Rect* destination)
{
	SDL_Rect src=source?*source:Rect(), dst=destination?*destination:Rect();
    Error::Condition(SDL_BlitScaled(second.surface, source?&src:nullptr, surface, destination?&dst:nullptr)<0);
}
void Surface::EnableColorKey(const Color& col)
{
	Error::Condition(SDL_SetColorKey(surface, true, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a))<0);
}
void Surface::DisableColorKey(const Color& col)
{
	Error::Condition(SDL_SetColorKey(surface, false, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a))<0);
}
void Surface::SetRGBMod(const ColorRGB& col)
{
	Error::Condition(SDL_SetSurfaceColorMod(surface, col.r, col.g, col.b)<0);
}
void Surface::SetAlphaMod(uint8 alpha)
{
	Error::Condition(SDL_SetSurfaceAlphaMod(surface, alpha)<0);
}
void Surface::SetRGBAMod(const Color& col)
{
	SetRGBMod(col);
	SetAlphaMod(col.a);
}
bool Surface::MustLock()const noexcept
{
	return SDL_MUSTLOCK(surface);
}

void Surface::Lock()
{
	Error::IfNegative(SDL_LockSurface(surface));
}
void Surface::Unlock()noexcept
{
	SDL_UnlockSurface(surface);
}
void Surface::EnableRLE()
{
    Error::IfNegative(SDL_SetSurfaceRLE(surface, true));
}
void Surface::DisableRLE()
{
    Error::IfNegative(SDL_SetSurfaceRLE(surface, false));
}
void Surface::SetBlendMode(BlendMode mode)
{
    Error::IfNegative(SDL_SetSurfaceBlendMode(surface, SDL_BlendMode(mode)));
}
void Surface::Repaint(const Color& col)
{
	Error::IfNegative(SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}
void Surface::Draw(const Line& line, const Color& col)
{
	auto TransformTo45=[](Point pos, uint8 convf)->Point
	{
		return	convf==1?pos:
				convf==2?Point(pos.y, pos.x):
				convf==3?Point(pos.y, -pos.x):
				convf==4?Point(-pos.x, pos.y):
				convf==5?Point(-pos.x, -pos.y):
				convf==6?Point(-pos.y, -pos.x):
				convf==7?Point(-pos.y, pos.x):
						Point(pos.x, -pos.y);
	};
	auto TransformFrom45=[](Point pos, uint8 convf)->Point
	{
		return	convf==1?pos:
				convf==2?Point(pos.y, pos.x):
				convf==7?Point(pos.y, -pos.x):
				convf==4?Point(-pos.x, pos.y):
				convf==5?Point(-pos.x, -pos.y):
				convf==6?Point(-pos.y, -pos.x):
				convf==3?Point(-pos.y, pos.x):
						Point(pos.x, -pos.y);
	};
	Point d(line.end.x-line.begin.x, line.end.y-line.begin.y);
	uint8 convf=0;
	if(d.x>0&&d.y>0&&d.x>=d.y)
		convf=1;
	else if(d.x>0&&d.y>0&&d.x<d.y)
		convf=2;
	else if(d.x<=0&&d.y>0&& -d.x<d.y)
		convf=3;
	else if(d.x<=0&&d.y>0&& -d.x>=d.y)
		convf=4;
	else if(d.x<=0&&d.y<=0&& -d.x>= -d.y)
		convf=5;
	else if(d.x<=0&&d.y<=0&& -d.x< -d.y)
		convf=6;
	else if(d.x>0&&d.y<=0&&d.x< -d.y)
		convf=7;
	else
		convf=8;
	const Line transformed(TransformTo45(line.begin, convf), TransformTo45(line.end, convf));
	const Point diff(transformed.end-transformed.begin);
	const Point d2=diff*2;
	int predictor=d2.y-diff.x;
	for(Point point=transformed.begin;point.x<=transformed.end.x;++point.x)
	{
		Draw(TransformFrom45(point, convf), col);
		if(predictor>=0)
		{
			++point.y;
			predictor+=d2.y-d2.x;
		}
		else
		{
			predictor+=d2.y;
		}
	}
}
void Surface::DrawBorder(const Rect& rect, const Color& col)
{
	for(int i=rect.x, limit=rect.x+rect.w; i<limit;++i)
	{
		Draw(Point(i,rect.y), col);
	}
	for(int i=rect.x, limit=rect.x+rect.w; i<limit;++i)
	{
		Draw(Point(i,rect.y+rect.h), col);
	}
	for(int i=rect.y, limit=rect.y+rect.h; i<limit;++i)
	{
		Draw(Point(rect.x, i), col);
	}
	for(int i=rect.y, limit=rect.y+rect.h; i<limit;++i)
	{
		Draw(Point(rect.x+rect.w, i), col);
	}
}
void Surface::Draw(const Rect& rect, const Color& col)
{
	SDL_Rect r=rect;
	Error::IfNegative(SDL_FillRect(surface, &r, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}
void Surface::Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(u8text, textcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(u16text, textcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::Draw(Font& font, char16_t character, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(character, textcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(u8text, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(u16text, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::Draw(Font& font, char16_t character, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(character, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(u8text, textcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(u16text, textcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}
void Surface::DrawFast(Font& font, char16_t character, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(character, textcolor);
	Rect destination(dst, textimage.Size());
	Blit(textimage, nullptr, &destination);
}