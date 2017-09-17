#pragma once

using ColorRGB=colors::RGB;
using ColorRGBA=colors::RGBA;
using Color=ColorRGBA;

namespace Pixel
{
	enum class Format: uint32
	{
		Unknown=SDL_PIXELFORMAT_UNKNOWN,
		Index1LSB=SDL_PIXELFORMAT_INDEX1LSB,
		Index1MSB=SDL_PIXELFORMAT_INDEX1MSB,
		Index4LSB=SDL_PIXELFORMAT_INDEX4LSB,
		Index4MSB=SDL_PIXELFORMAT_INDEX4MSB,
		Index8=SDL_PIXELFORMAT_INDEX8,
		RGB332=SDL_PIXELFORMAT_RGB332,
		RGB444=SDL_PIXELFORMAT_RGB444,
		RGB555=SDL_PIXELFORMAT_RGB555,
		BGR555=SDL_PIXELFORMAT_BGR555,
		ARGB4444=SDL_PIXELFORMAT_ARGB4444,
		RGBA4444=SDL_PIXELFORMAT_RGBA4444,
		ABGR4444=SDL_PIXELFORMAT_ABGR4444,
		BGRA4444=SDL_PIXELFORMAT_BGRA4444,
		ARGB1555=SDL_PIXELFORMAT_ARGB1555,
		RGBA5551=SDL_PIXELFORMAT_RGBA5551,
		ABGR1555=SDL_PIXELFORMAT_ABGR1555,
		BGRA5551=SDL_PIXELFORMAT_BGRA5551,
		RGB565=SDL_PIXELFORMAT_RGB565,
		BGR565=SDL_PIXELFORMAT_BGR565,
		RGB24=SDL_PIXELFORMAT_RGB24,
		BGR24=SDL_PIXELFORMAT_BGR24,
		RGB888=SDL_PIXELFORMAT_RGB888,
		RGBX8888=SDL_PIXELFORMAT_RGBX8888,
		BGR888=SDL_PIXELFORMAT_BGR888,
		BGRX8888=SDL_PIXELFORMAT_BGRX8888,
		ARGB8888=SDL_PIXELFORMAT_ARGB8888,
		RGBA8888=SDL_PIXELFORMAT_RGBA8888,
		ABGR8888=SDL_PIXELFORMAT_ABGR8888,
		BGRA8888=SDL_PIXELFORMAT_BGRA8888,
		ARGB2101010=SDL_PIXELFORMAT_ARGB2101010,
		YV12=SDL_PIXELFORMAT_YV12,
		IYUV=SDL_PIXELFORMAT_IYUV,
		YUY2=SDL_PIXELFORMAT_YUY2,
		UYVY=SDL_PIXELFORMAT_UYVY,
		YVYU=SDL_PIXELFORMAT_YVYU
	};
	enum class Type: uint32
	{
		Unknown=SDL_PIXELTYPE_UNKNOWN,
		Index1=SDL_PIXELTYPE_INDEX1,
		Index4=SDL_PIXELTYPE_INDEX4,
		Index8=SDL_PIXELTYPE_INDEX8,
		Packed8=SDL_PIXELTYPE_PACKED8,
		Packed16=SDL_PIXELTYPE_PACKED16,
		Packed32=SDL_PIXELTYPE_PACKED32,
		ArrayU8=SDL_PIXELTYPE_ARRAYU8,
		ArrayU16=SDL_PIXELTYPE_ARRAYU16,
		ArrayU32=SDL_PIXELTYPE_ARRAYU32,
		ArrayF16=SDL_PIXELTYPE_ARRAYF16,
		ArrayF32=SDL_PIXELTYPE_ARRAYF32
	};
	enum class Order: uint32
	{
		BitmapNone=SDL_BITMAPORDER_NONE,
		Bitmap4321=SDL_BITMAPORDER_4321,
		Bitmap1234=SDL_BITMAPORDER_1234,
		PackedNone=SDL_PACKEDORDER_NONE,
		PackedXRBG=SDL_PACKEDORDER_XRGB,
		PackedRGBX=SDL_PACKEDORDER_RGBX,
		PackedARGB=SDL_PACKEDORDER_ARGB,
		PackedRGBA=SDL_PACKEDORDER_RGBA,
		PackedXBGR=SDL_PACKEDORDER_XBGR,
		PackedBGRX=SDL_PACKEDORDER_BGRX,
		PackedABGR=SDL_PACKEDORDER_ABGR,
		PackedBGRA=SDL_PACKEDORDER_BGRA,
		ArrayNone=SDL_ARRAYORDER_NONE,
		ArrayRGB=SDL_ARRAYORDER_RGB,
		ArrayRGBA=SDL_ARRAYORDER_RGBA,
		ArrayARGB=SDL_ARRAYORDER_ARGB,
		ArrayBGR=SDL_ARRAYORDER_BGR,
		ArrayBGRA=SDL_ARRAYORDER_BGRA,
		ArrayABGR=SDL_ARRAYORDER_ABGR
	};
	enum class Layout: uint32
	{
		None=SDL_PACKEDLAYOUT_NONE,
		Packed332=SDL_PACKEDLAYOUT_332,
		Packed4444=SDL_PACKEDLAYOUT_4444,
		Packed1555=SDL_PACKEDLAYOUT_1555,
		Packed5551=SDL_PACKEDLAYOUT_5551,
		Packed565=SDL_PACKEDLAYOUT_565,
		Packed8888=SDL_PACKEDLAYOUT_8888,
		Packed2101010=SDL_PACKEDLAYOUT_2101010,
		Packed1010102=SDL_PACKEDLAYOUT_1010102
	};
	Type TypeOf(Format fmt)
	{
		return Type(SDL_PIXELTYPE(uint32(fmt)));
	}
	Order OrderOf(Format fmt)
	{
		return Order(SDL_PIXELORDER(uint32(fmt)));
	}
	Layout LayoutOf(Format fmt)
	{
		return Layout(SDL_PIXELLAYOUT(uint32(fmt)));
	}
	uint8 BitSize(Format fmt)
	{
		return SDL_BITSPERPIXEL(uint32(fmt));
	}
	uint8 ByteSize(Format fmt)
	{
		return SDL_BYTESPERPIXEL(uint32(fmt));
	}
	bool IsIndexed(Format fmt)
	{
		return SDL_ISPIXELFORMAT_INDEXED(uint32(fmt));
	}
	bool HasAlphaChannel(Format fmt)
	{
		return SDL_ISPIXELFORMAT_ALPHA(uint32(fmt));
	}
	bool IsFourCC(Format fmt)
	{
		return SDL_ISPIXELFORMAT_FOURCC(uint32(fmt));
	}
}