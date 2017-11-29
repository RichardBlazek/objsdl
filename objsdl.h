#pragma once

#include <tuple>
#include <string>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>

#include "../mylibraries/func.h"
#include "../mylibraries/geometry.h"
#include "../mylibraries/colors.h"
#include "../mylibraries/types.h"
#include "../mylibraries/nocopy.h"

#include "oldsdl.h"

///Object wrapper for SDL
namespace SDL
{
#include "shapes.h"
#include "color.h"
#include "sdl_base.h"
#include "decl.h"
#include "wm.h"
#include "time.h"
#include "gamecontroller.h"
#include "event.h"
#include "keyboard.h"
#include "window.h"
#include "surface.h"
#include "renderer.h"
#include "cursor.h"
#include "audio.h"
#include "tones/sound.h"
#include "tones/sinewave.h"
#include "tones/tone.h"
#include "messagebox.h"
#include "joystick.h"
#include "powerstate.h"
#include "clipboard.h"
#include "cpu.h"
#include "screensaver.h"
#include "textinput.h"
#include "mainloop.h"
}