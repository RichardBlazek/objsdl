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
	enum class Flags
	{
		Normal=TTF_STYLE_NORMAL,
		Bold=TTF_STYLE_BOLD,
		Italic=TTF_STYLE_ITALIC,
		Underline=TTF_STYLE_UNDERLINE,
		Strikethrough=TTF_STYLE_STRIKETHROUGH
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
		font=Error::IfZero(TTF_OpenFont(filename.c_str(), size));
	}
	void Open(const std::string& filename, uint32 size, uint32 index)
	{
		Close();
		font=Error::IfZero(TTF_OpenFontIndex(filename.c_str(), size, index));
	}
	bool IsOpened()const
	{
		return font;
	}
	Font()=default;
	~Font()
	{
		Close();
	}
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
		return (Surface&&)Surface(Error::IfZero(TTF_RenderUTF8_Blended(font, text.empty()?" ":text.c_str(), Surface::ColorSDL(textcolor))));
	}
	Surface Render(const std::u16string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderUNICODE_Blended(font, reinterpret_cast<const uint16*>(text.empty()?u" ":text.c_str()), Surface::ColorSDL(textcolor))));
	}
	Surface Render(char16_t character, Color textcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderGlyph_Blended(font, character, Surface::ColorSDL(textcolor))));
	}
	Surface Render(const std::string& text, Color textcolor, Color backgroundcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderUTF8_Shaded(font, text.empty()?" ":text.c_str(), Surface::ColorSDL(textcolor), Surface::ColorSDL(backgroundcolor))));
	}
	Surface Render(const std::u16string& text, Color textcolor, Color backgroundcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderUNICODE_Shaded(font, reinterpret_cast<const uint16*>(text.empty()?u" ":text.c_str()), Surface::ColorSDL(textcolor), Surface::ColorSDL(backgroundcolor))));
	}
	Surface Render(char16_t character, Color textcolor, Color backgroundcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderGlyph_Shaded(font, character, Surface::ColorSDL(textcolor), Surface::ColorSDL(backgroundcolor))));
	}
	Surface RenderFast(const std::string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderUTF8_Solid(font, text.empty()?" ":text.c_str(), Surface::ColorSDL(textcolor))));
	}
	Surface RenderFast(const std::u16string& text, Color textcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderUNICODE_Solid(font, reinterpret_cast<const uint16*>(text.empty()?u" ":text.c_str()), Surface::ColorSDL(textcolor))));
	}
	Surface RenderFast(char16_t character, Color textcolor)
	{
		ErrorIfNotOpened();
		return (Surface&&)Surface(Error::IfZero(TTF_RenderGlyph_Solid(font, character, Surface::ColorSDL(textcolor))));
	}
	Flags Style()
	{
		ErrorIfNotOpened();
		return Flags(TTF_GetFontStyle(font));
	}
	void SetStyle(Flags style)
	{
		ErrorIfNotOpened();
		TTF_SetFontStyle(font, int(style));
	}
	int32 Outline()
	{
		ErrorIfNotOpened();
		return TTF_GetFontOutline(font);
	}
	void SetOutline(int32 outline)
	{
		ErrorIfNotOpened();
		TTF_SetFontOutline(font, outline);
	}
	Hinting HintingType()
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
	uint32 MaxHeight()
	{
		ErrorIfNotOpened();
		return TTF_FontHeight(font);
	}
	uint32 Ascent()
	{
		ErrorIfNotOpened();
		return TTF_FontAscent(font);
	}
	uint32 Descent()
	{
		ErrorIfNotOpened();
		return TTF_FontDescent(font);
	}
	uint32 LineSkip()
	{
		ErrorIfNotOpened();
		return TTF_FontLineSkip(font);
	}
	uint32 CountOfFaces()
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
	std::string FamilyName()
	{
		ErrorIfNotOpened();
		auto x=TTF_FontFaceFamilyName(font);
		return x?x:"";
	}
	bool IsStyleNameAvailable()
	{
		ErrorIfNotOpened();
		return TTF_FontFaceStyleName(font);
	}
	std::string StyleName()
	{
		ErrorIfNotOpened();
		auto x=TTF_FontFaceStyleName(font);
		return x?x:"";
	}
	uint32 GlyphIndex(char16_t character)
	{
		ErrorIfNotOpened();
		return TTF_GlyphIsProvided(font, character);
	}
	Point GlyphMin(char16_t character)
	{
		ErrorIfNotOpened();
		Point result;
		Error::IfNegative(TTF_GlyphMetrics(font, character, &result.x, nullptr, &result.y, nullptr, nullptr));
		return result;
	}
	Point GlyphMax(char16_t character)
	{
		ErrorIfNotOpened();
		Point result;
		Error::IfNegative(TTF_GlyphMetrics(font, character, nullptr, &result.x, nullptr, &result.y, nullptr));
		return result;
	}
	uint32 GlyphAdvance(char16_t character)
	{
		ErrorIfNotOpened();
		int result;
		Error::IfNegative(TTF_GlyphMetrics(font, character, nullptr, nullptr, nullptr, nullptr, &result));
		return result;
	}
	Point TextSize(char16_t character)
	{
		return GlyphMax(character)-GlyphMin(character);
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
};
Font::Flags operator|(Font::Flags first, Font::Flags second)noexcept
{
	return Font::Flags(uint32(first)|uint32(second));
}
Font::Flags operator&(Font::Flags first, Font::Flags second)noexcept
{
	return Font::Flags(uint32(first)&uint32(second));
}
Font::Flags operator^(Font::Flags first, Font::Flags second)noexcept
{
	return Font::Flags(uint32(first)^uint32(second));
}
Font::Flags& operator|=(Font::Flags& first, Font::Flags second)noexcept
{
	return first=(first|second);
}
Font::Flags& operator&=(Font::Flags& first, Font::Flags second)noexcept
{
	return first=(first&second);
}
Font::Flags& operator^=(Font::Flags& first, Font::Flags second)noexcept
{
	return first=(first^second);
}
Font::Flags operator~(Font::Flags param)noexcept
{
	return Font::Flags(~uint32(param));
}
