#pragma once

Surface::Surface(Point size, const std::vector<Color>& colors, uint8 depth)
{
    surface=Error::IfZero(SDL_CreateRGBSurface(0,size.x,size.y,depth, 0, 0, 0, 0));
	SetPalette(colors);
}
Surface::Surface(Point size, const std::vector<Color>& colors, Pixel::Format format)
{
    surface=Error::IfZero(SDL_CreateRGBSurfaceWithFormat(0,size.x,size.y, format.BitsPexPixel(), uint32(format)));
	SetPalette(colors);
}
Surface::Surface(Point size, uint8 depth, ColorMasks masks)
{
    surface=Error::IfZero(SDL_CreateRGBSurface(0,size.x,size.y,depth, BE_ToNative(masks.r), BE_ToNative(masks.g), BE_ToNative(masks.b), BE_ToNative(masks.a)));
}
Surface::Surface(Point size, Pixel::Format format)
{
	if(format.IsIndexed())
	{
		throw Error("Surface::Create>No palette given, but format needs palette");
	}
    surface=Error::IfZero(SDL_CreateRGBSurfaceWithFormat(0,size.x,size.y, format.BitsPexPixel(), uint32(format)));
}
void Surface::Blit(Surface& second, Rect source, Rect destination)
{
	SDL_Rect src=Surface::RectSDL(source), dst=Surface::RectSDL(destination);
    Error::IfNegative(SDL_BlitSurface(second.surface, &src, surface, &dst));
}
void Surface::Draw(Surface& second, Rect source, Rect destination)
{
	SDL_Rect src=Surface::RectSDL(source), dst=Surface::RectSDL(destination);
    Error::IfNegative(SDL_BlitScaled(second.surface, &src, surface, &dst));
}
void Surface::EnableColorKey(const Color& col)
{
	Error::IfNegative(SDL_SetColorKey(surface, true, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}
void Surface::DisableColorKey(const Color& col)
{
	Error::IfNegative(SDL_SetColorKey(surface, false, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}
void Surface::SetRGBMod(const ColorRGB& col)
{
	Error::IfNegative(SDL_SetSurfaceColorMod(surface, col.r, col.g, col.b));
}
void Surface::SetAlphaMod(uint8 alpha)
{
	Error::IfNegative(SDL_SetSurfaceAlphaMod(surface, alpha));
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
	auto TransformTo45=[](Point pos, uint8 conf)->Point
	{
		return	conf==1?pos:
				conf==2?Point(pos.y, pos.x):
				conf==3?Point(pos.y, -pos.x):
				conf==4?Point(-pos.x, pos.y):
				conf==5?Point(-pos.x, -pos.y):
				conf==6?Point(-pos.y, -pos.x):
				conf==7?Point(-pos.y, pos.x):
						Point(pos.x, -pos.y);
	};
	auto TransformFrom45=[](Point pos, uint8 conf)->Point
	{
		return	conf==1?pos:
				conf==2?Point(pos.y, pos.x):
				conf==7?Point(pos.y, -pos.x):
				conf==4?Point(-pos.x, pos.y):
				conf==5?Point(-pos.x, -pos.y):
				conf==6?Point(-pos.y, -pos.x):
				conf==3?Point(-pos.y, pos.x):
						Point(pos.x, -pos.y);
	};
	Point d(line.end.x-line.begin.x, line.end.y-line.begin.y);
	uint8 conf=0;
	if(d.x>0&&d.y>0&&d.x>=d.y)
		conf=1;
	else if(d.x>0&&d.y>0&&d.x<d.y)
		conf=2;
	else if(d.x<=0&&d.y>0&& -d.x<d.y)
		conf=3;
	else if(d.x<=0&&d.y>0&& -d.x>=d.y)
		conf=4;
	else if(d.x<=0&&d.y<=0&& -d.x>= -d.y)
		conf=5;
	else if(d.x<=0&&d.y<=0&& -d.x< -d.y)
		conf=6;
	else if(d.x>0&&d.y<=0&&d.x< -d.y)
		conf=7;
	else
		conf=8;
	const Line transformed(TransformTo45(line.begin, conf), TransformTo45(line.end, conf));
	const Point diff(transformed.end-transformed.begin);
	const Point d2=diff*2;
	int predictor=d2.y-diff.x;
	for(Point point=transformed.begin; point.x<=transformed.end.x; ++point.x)
	{
		Draw(TransformFrom45(point, conf), col);
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
	Draw(SDL::Rect(rect.x, rect.y, 1, rect.h), col);
	Draw(SDL::Rect(rect.Right(), rect.y, 1, rect.h), col);
	Draw(SDL::Rect(rect.x, rect.y, rect.w, 1), col);
	Draw(SDL::Rect(rect.x, rect.Down(), rect.w, 1), col);
}
void Surface::Draw(const Rect& rect, const Color& col)
{
	SDL_Rect r=Surface::RectSDL(rect);
	Error::IfNegative(SDL_FillRect(surface, &r, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}