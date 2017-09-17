#pragma once

class Font: public NonCopyable
{
private:
    TTF_Font* font=nullptr;
    void ErrorIfNotOpened()
    {
		if(!font)
		{
			throw Error("Font is not opened");
		}
    }
public:
	enum class Style
	{
        Normal=TTF_STYLE_NORMAL,
		Bold=TTF_STYLE_BOLD,
		Italic=TTF_STYLE_ITALIC,
		Underline=TTF_STYLE_UNDERLINE,
		StrikeThrough=TTF_STYLE_STRIKETHROUGH
	};
	enum class Hinting
	{
		Normal=TTF_HINTING_NORMAL,
		Light=TTF_HINTING_LIGHT,
		Mono=TTF_HINTING_MONO,
		None=TTF_HINTING_NONE
	};
	void Close()
	{
        if(font)
		{
			TTF_CloseFont(font);
			font=nullptr;
		}
	}
	void Open(const std::string& filename, uint32 size)
	{
		Close();
        font=TTF_OpenFont(filename.c_str(), size);
        Error::IfZero(font);
	}
	void Open(const std::string& filename, uint32 size, uint32 index)
	{
        Close();
        font=TTF_OpenFontIndex(filename.c_str(), size, index);
        Error::IfZero(font);
	}
	bool IsOpened()const
	{
		return font;
	}
	Font()=default;
	Font(const std::string& filename, uint32 size)
	{
        Open(filename, size);
	}
	Font(const std::string& filename, uint32 size, uint32 index)
	{
        Open(filename, size, index);
	}
	Font(Font&& init):font(init.font)
	{
        init.font=nullptr;
	}
	Font& operator=(Font&& init)
	{
        font=init.font;
        init.font=nullptr;
        return *this;
	}
	Surface Render(const std::string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderUTF8_Blended(font, text.empty()?" ":text.c_str(), Surface::ColorSDL(textcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface Render(const std::u16string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderUNICODE_Blended(font, reinterpret_cast<const uint16*>(text.empty()?u" ":text.c_str()), Surface::ColorSDL(textcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface Render(char16_t character, Color textcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderGlyph_Blended(font, character, Surface::ColorSDL(textcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface Render(const std::string& text, Color textcolor, Color backgroundcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderUTF8_Shaded(font, text.empty()?" ":text.c_str(), Surface::ColorSDL(textcolor), Surface::ColorSDL(backgroundcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface Render(const std::u16string& text, Color textcolor, Color backgroundcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderUNICODE_Shaded(font, reinterpret_cast<const uint16*>(text.empty()?u" ":text.c_str()), Surface::ColorSDL(textcolor), Surface::ColorSDL(backgroundcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface Render(char16_t character, Color textcolor, Color backgroundcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderGlyph_Shaded(font, character, Surface::ColorSDL(textcolor), Surface::ColorSDL(backgroundcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface RenderFast(const std::string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderUTF8_Solid(font, text.empty()?" ":text.c_str(), Surface::ColorSDL(textcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface RenderFast(const std::u16string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderUNICODE_Solid(font, reinterpret_cast<const uint16*>(text.empty()?u" ":text.c_str()), Surface::ColorSDL(textcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Surface RenderFast(char16_t character, Color textcolor)
	{
		ErrorIfNotOpened();
		Surface result(TTF_RenderGlyph_Solid(font, character, Surface::ColorSDL(textcolor)));
        Error::IfZero(result.surface);
        return result;
	}
	Style GetStyle()
	{
		ErrorIfNotOpened();
        return Style(TTF_GetFontStyle(font));
	}
	void SetStyle(Style fontstyle)
	{
		ErrorIfNotOpened();
		TTF_SetFontStyle(font, int(fontstyle));
	}
	int32 GetOutline()
	{
		ErrorIfNotOpened();
		return TTF_GetFontOutline(font);
	}
	void SetOutline(int32 outline)
	{
		ErrorIfNotOpened();
		TTF_SetFontOutline(font, outline);
	}
	Hinting GetHinting()
	{
		ErrorIfNotOpened();
		return Hinting(TTF_GetFontHinting(font));
	}
	void SetHinting(Hinting hint)
	{
		ErrorIfNotOpened();
		TTF_SetFontHinting(font, int(hint));
	}
	bool IsKerningEnabled()
	{
		ErrorIfNotOpened();
		return bool(TTF_GetFontKerning(font));
	}
	void EnableKerning()
	{
		ErrorIfNotOpened();
		TTF_SetFontKerning(font, true);
	}
	void DisableKerning()
	{
		ErrorIfNotOpened();
		TTF_SetFontKerning(font, false);
	}
	uint32 GetMaxHeight()
	{
		ErrorIfNotOpened();
        return TTF_FontHeight(font);
	}
	uint32 GetAscent()
	{
		ErrorIfNotOpened();
		return TTF_FontAscent(font);
	}
	uint32 GetDescent()
	{
		ErrorIfNotOpened();
		return TTF_FontDescent(font);
	}
    uint32 GetLineSkip()
    {
		ErrorIfNotOpened();
        return TTF_FontLineSkip(font);
    }
    uint32 GetNumFaces()
    {
		ErrorIfNotOpened();
    	return TTF_FontFaces(font);
    }
    bool HasFixedWidth()
    {
		ErrorIfNotOpened();
    	return TTF_FontFaceIsFixedWidth(font);
    }
    bool IsFamilyNameAvailable()
    {
		ErrorIfNotOpened();
    	return TTF_FontFaceFamilyName(font);
    }
    std::string GetFamilyName()
    {
		ErrorIfNotOpened();
    	const char* x=TTF_FontFaceFamilyName(font);
    	return x?x:"";
	}
    bool IsStyleNameAvailable()
    {
		ErrorIfNotOpened();
    	return TTF_FontFaceStyleName(font);
    }
    std::string GetStyleName()
    {
		ErrorIfNotOpened();
    	const char* x=TTF_FontFaceStyleName(font);
    	return x?x:"";
	}
	uint32 GlyphIndex(char16_t character)
	{
		ErrorIfNotOpened();
        return TTF_GlyphIsProvided(font, character);
	}
    uint32 GlyphMinX(char16_t character)
    {
		ErrorIfNotOpened();
        int result;
        Error::IfNegative(TTF_GlyphMetrics(font, character, &result, nullptr, nullptr, nullptr, nullptr));
        return result;
    }
    uint32 GlyphMinY(char16_t character)
    {
		ErrorIfNotOpened();
        int result;
        Error::IfNegative(TTF_GlyphMetrics(font, character, nullptr, nullptr, &result, nullptr, nullptr));
        return result;
    }
    uint32 GlyphMaxX(char16_t character)
    {
		ErrorIfNotOpened();
        int result;
        Error::IfNegative(TTF_GlyphMetrics(font, character, nullptr, &result, nullptr, nullptr, nullptr));
        return result;
    }
    uint32 GlyphMaxY(char16_t character)
    {
		ErrorIfNotOpened();
        int result;
        Error::IfNegative(TTF_GlyphMetrics(font, character, nullptr, nullptr, nullptr, &result, nullptr));
        return result;
    }
    uint32 GlyphAdvance(char16_t character)
    {
		ErrorIfNotOpened();
        int result;
        Error::IfNegative(TTF_GlyphMetrics(font, character, nullptr, nullptr, nullptr, nullptr, &result));
        return result;
    }
    uint32 GlyphWidth(char16_t character)
    {
		ErrorIfNotOpened();
        return GlyphMaxX(character)-GlyphMinX(character);
    }
    uint32 GlyphHeight(char16_t character)
    {
		ErrorIfNotOpened();
        return GlyphMaxY(character)-GlyphMinY(character);
    }
    Point TextSize(const std::string& text)
    {
		ErrorIfNotOpened();
        Point result;
        Error::IfNegative(TTF_SizeUTF8(font, text.c_str(), &result.x, &result.y));
        return result;
    }
    Point TextSize(const std::u16string& text)
    {
		ErrorIfNotOpened();
        Point result;
        Error::IfNegative(TTF_SizeUNICODE(font, reinterpret_cast<const uint16*>(text.c_str()), &result.x, &result.y));
        return result;
    }
    Point TextSize(char16_t character)
    {
		ErrorIfNotOpened();
    	return Point(GlyphWidth(character), GlyphHeight(character));
    }
};
Font::Style operator|(Font::Style first, Font::Style second)noexcept
{
	return Font::Style(uint32(first)|uint32(second));
}
Font::Style operator&(Font::Style first, Font::Style second)noexcept
{
	return Font::Style(uint32(first)&uint32(second));
}
Font::Style operator^(Font::Style first, Font::Style second)noexcept
{
	return Font::Style(uint32(first)^uint32(second));
}
Font::Style operator|=(Font::Style& first, Font::Style second)noexcept
{
	return first=(first|second);
}
Font::Style operator&=(Font::Style& first, Font::Style second)noexcept
{
	return first=(first&second);
}
Font::Style operator^=(Font::Style& first, Font::Style second)noexcept
{
	return first=(first^second);
}
Font::Style operator~(Font::Style param)noexcept
{
	return Font::Style(~uint32(param));
}