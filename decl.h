#pragma once

//Forward declarations
class Animation;
class Cursor;
class Error;
class Event;
class Font;
class Joystick;
class Renderer;
class Rect;
class Surface;
class Texture;
class Display;
class Window;

#include "decl\rect.h"
#include "decl\messagebox.h"
#include "decl\window.h"
#include "decl\surface.h"
#include "decl\font.h"
#include "decl\renderer.h"
#include "decl\texture.h"
#include "decl\joystick.h"

void Error::Show()const
{
	MessageBox::Show("SDL-Error", message, MessageBox::Flags::Error);
}