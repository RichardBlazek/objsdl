#pragma once

void DrawBase::Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(u8text, textcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(u16text, textcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::Draw(Font& font, char16_t character, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(character, textcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::Draw(Font& font, const std::string& u8text, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(u8text, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(u16text, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::Draw(Font& font, char16_t character, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(character, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(u8text, textcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(u16text, textcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
void DrawBase::DrawFast(Font& font, char16_t character, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(character, textcolor);
	Rect destination(dst, textimage.Size());
	Draw(textimage, textimage.Size(), destination);
}
///Centred text-----------------------------------------------------------------------------------------------
void DrawBase::Draw(Font& font, const std::string& u8text, const Color& textcolor, Rect dst)
{
	Draw(font, u8text, textcolor, dst.Center()-font.TextSize(u8text)/2);
}
void DrawBase::Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst)
{
	Draw(font, u16text, textcolor, dst.Center()-font.TextSize(u16text)/2);
}
void DrawBase::Draw(Font& font, char16_t character, const Color& textcolor, Rect dst)
{
	Draw(font, character, textcolor, dst.Center()-font.TextSize(character)/2);
}
void DrawBase::Draw(Font& font, const std::string& u8text, const Color& textcolor, Rect dst, const Color& backgroundcolor)
{
	Draw(font, u8text, textcolor, dst.Center()-font.TextSize(u8text)/2, backgroundcolor);
}
void DrawBase::Draw(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst, const Color& backgroundcolor)
{
	Draw(font, u16text, textcolor, dst.Center()-font.TextSize(u16text)/2, backgroundcolor);
}
void DrawBase::Draw(Font& font, char16_t character, const Color& textcolor, Rect dst, const Color& backgroundcolor)
{
	Draw(font, character, textcolor, dst.Center()-font.TextSize(character)/2, backgroundcolor);
}
void DrawBase::DrawFast(Font& font, const std::string& u8text, const Color& textcolor, Rect dst)
{
	Draw(font, u8text, textcolor, dst.Center()-font.TextSize(u8text)/2);
}
void DrawBase::DrawFast(Font& font, const std::u16string& u16text, const Color& textcolor, Rect dst)
{
	Draw(font, u16text, textcolor, dst.Center()-font.TextSize(u16text)/2);
}
void DrawBase::DrawFast(Font& font, char16_t character, const Color& textcolor, Rect dst)
{
	Draw(font, character, textcolor, dst.Center()-font.TextSize(character)/2);
}