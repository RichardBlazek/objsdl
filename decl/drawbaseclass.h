#pragma once

class DrawBaseClass
{
public:
	virtual void Draw(Surface& surface, Rect source, Rect destination)=0;
	virtual void Draw(const Point& point, const Color& col)=0;
	//Draw Circle---------------------------------------------------------------
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
	//Draw text-----------------------------------------------------------------
	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst);
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst);
	void Draw(Font& font, char16_t character, const Color& textcolor, Point dst);

	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst, const Color& backgroundcolor);
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst, const Color& backgroundcolor);
	void Draw(Font& font, char16_t character, const Color& textcolor, Point dst, const Color& backgroundcolor);

	void DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Point dst);
	void DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst);
	void DrawFast(Font& font, char16_t character, const Color& textcolor, Point dst);

	///Centred text-----------------------------------------------------------------------------------------------
	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Rect dst);
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst);
	void Draw(Font& font, char16_t character, const Color& textcolor, Rect dst);

	void Draw(Font& font, const std::string& u8text, const Color& textcolor, Rect dst, const Color& backgroundcolor);
	void Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst, const Color& backgroundcolor);
	void Draw(Font& font, char16_t character, const Color& textcolor, Rect dst, const Color& backgroundcolor);

	void DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Rect dst);
	void DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst);
	void DrawFast(Font& font, char16_t character, const Color& textcolor, Rect dst);
};