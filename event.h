#pragma once

#include "events/type.h"
#include "events/structures.h"

namespace events
{
class Event
{
private:
	SDL_Event event;
	Event(const SDL_Event& evt):event(evt){}
public:
	friend class Iterator;
	enum class Action: uint8
	{
		Add=SDL_ADDEVENT,
		Peek=SDL_PEEKEVENT,
		Get=SDL_GETEVENT
	};
	Event()noexcept=default;
	events::MouseWheel MouseWheel()const
	{
		return events::MouseWheel{event.wheel.windowID, event.wheel.which!=SDL_TOUCH_MOUSEID, Point(event.wheel.x, event.wheel.y)* (event.wheel.direction==SDL_MOUSEWHEEL_FLIPPED?-1:1)};
	}
	events::MouseMotion MouseMotion()const
	{
		return events::MouseMotion{event.motion.windowID, event.motion.which!=SDL_TOUCH_MOUSEID, MouseButtonMask(event.motion.state), Point(event.motion.x, event.motion.y), Point(event.motion.xrel, event.motion.yrel)};
	}
	events::MouseButton MouseButton()const
	{
		return events::MouseButton{event.button.windowID, event.button.which!=SDL_TOUCH_MOUSEID, SDL::MouseButton(event.button.button), Point(event.button.x, event.button.y), event.button.clicks};
	}
	events::Keyboard Keyboard()const
	{
		return events::Keyboard{event.key.windowID, event.key.repeat, Scancode(event.key.keysym.scancode), Keycode(event.key.keysym.sym), Keymod(event.key.keysym.mod)};
	}
	events::User User()const
	{
		return events::User{event.user.windowID, event.user.code, event.user.data1, event.user.data2};
	}
	events::WindowShown WindowShown()const
	{
		return events::WindowShown{event.window.windowID};
	}
	events::WindowHidden WindowHidden()const
	{
		return events::WindowHidden{event.window.windowID};
	}
	events::WindowExposed WindowExposed()const
	{
		return events::WindowExposed{event.window.windowID};
	}
	events::WindowMoved WindowMoved()const
	{
		return events::WindowMoved{event.window.windowID, Point(event.window.data1, event.window.data2)};
	}
	events::WindowResized WindowResized()const
	{
		return events::WindowResized{event.window.windowID, Point(event.window.data1, event.window.data2)};
	}
	events::WindowSizeChanged WindowSizeChanged()const
	{
		return events::WindowSizeChanged{event.window.windowID, Point(event.window.data1, event.window.data2)};
	}
	events::WindowMinimized WindowMinimized()const
	{
		return events::WindowMinimized{event.window.windowID};
	}
	events::WindowMaximized WindowMaximized()const
	{
		return events::WindowMaximized{event.window.windowID};
	}
	events::WindowRestored WindowRestored()const
	{
		return events::WindowRestored{event.window.windowID};
	}
	events::WindowEnter WindowEnter()const
	{
		return events::WindowEnter{event.window.windowID};
	}
	events::WindowLeave WindowLeave()const
	{
		return events::WindowLeave{event.window.windowID};
	}
	events::WindowFocusGained WindowFocusGained()const
	{
		return events::WindowFocusGained{event.window.windowID};
	}
	events::WindowFocusLost WindowFocusLost()const
	{
		return events::WindowFocusLost{event.window.windowID};
	}
	events::WindowClose WindowClose()const
	{
		return events::WindowClose{event.window.windowID};
	}
	events::WindowTakeFocus WindowTakeFocus()const
	{
		return events::WindowTakeFocus{event.window.windowID};
	}
	events::WindowHitTest WindowHitTest()const
	{
		return events::WindowHitTest{event.window.windowID};
	}
	events::JoystickAxis JoystickAxis()const
	{
		return events::JoystickAxis{uint32(event.jaxis.which), event.jaxis.axis, event.jaxis.value};
	}
	events::JoystickBall JoystickBall()const
	{
		return events::JoystickBall{uint32(event.jball.which), event.jball.ball, Point(event.jball.xrel, event.jball.yrel)};
	}
	events::JoystickButton JoystickButton()const
	{
		return events::JoystickButton{uint32(event.jbutton.which), event.jbutton.button};
	}
	events::JoystickHat JoystickHat()const
	{
		return events::JoystickHat{uint32(event.jhat.which), event.jhat.hat, event.jhat.value};
	}
	events::JoystickDeviceAdded JoystickDeviceAdded()const
	{
		return events::JoystickDeviceAdded{event.jdevice.which};
	}
	events::JoystickDeviceRemoved JoystickDeviceRemoved()const
	{
		return events::JoystickDeviceRemoved{uint32(event.jdevice.which)};
	}
	events::ControllerAxis ControllerAxis()const
	{
		return events::ControllerAxis{uint32(event.caxis.which), GameController::Axis(event.caxis.axis), event.caxis.value};
	}
	events::ControllerButton ControllerButton()const
	{
		return events::ControllerButton{uint32(event.cbutton.which), GameController::Button(event.cbutton.button)};
	}
	events::ControllerDeviceAdded ControllerDeviceAdded()const
	{
		return events::ControllerDeviceAdded{event.cdevice.which};
	}
	events::ControllerDeviceRemoved ControllerDeviceRemoved()const
	{
		return events::ControllerDeviceRemoved{uint32(event.cdevice.which)};
	}
	events::ControllerDeviceRemapped ControllerDeviceRemapped()const
	{
		return events::ControllerDeviceRemapped{uint32(event.cdevice.which)};
	}
	events::Drop Drop()const
	{
		events::Drop result{event.drop.windowID, event.drop.file};
		SDL_free(event.drop.file);
		return result;
	}
	events::TouchFinger TouchFinger()const
	{
		return events::TouchFinger{event.tfinger.touchId, event.tfinger.fingerId, event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy, event.tfinger.pressure};
	}
	events::MultiGesture MultiGesture()const
	{
		return events::MultiGesture{event.mgesture.touchId, event.mgesture.dTheta, event.mgesture.dDist, event.mgesture.x, event.mgesture.y, event.mgesture.numFingers};
	}
	events::DollarGesture DollarGesture()const
	{
		return events::DollarGesture{event.dgesture.touchId, event.dgesture.gestureId, event.dgesture.numFingers, event.dgesture.error, event.dgesture.x, event.dgesture.y};
	}
	events::DollarRecord DollarRecord()const
	{
		return events::DollarRecord{event.dgesture.touchId, event.dgesture.gestureId};
	}
	events::AudioDeviceAdded AudioDeviceAdded()const
	{
		return events::AudioDeviceAdded{event.adevice.which, event.adevice.iscapture};
	}
	events::AudioDeviceRemoved AudioDeviceRemoved()const
	{
		return events::AudioDeviceRemoved{event.adevice.which, event.adevice.iscapture};
	}
	events::TextEditing TextEditing()const
	{
		return events::TextEditing{event.edit.windowID, event.edit.text, event.edit.start, event.edit.length};
	}
	events::TextInput TextInput()const
	{
		return events::TextInput{event.text.windowID, event.text.text};
	}
	events::WindowManagement WindowManagement()const
	{
		return events::WindowManagement{*event.syswm.msg};
	}
	bool Push()
	{
		return bool(Error::IfNegative(SDL_PushEvent(&event)));
	}
	events::Type Type()const noexcept
	{
		auto tmp=event.type;
		tmp=(tmp>=(uint32)SDL_USEREVENT)?(uint32)SDL_USEREVENT:tmp;
		return events::Type(tmp==SDL_WINDOWEVENT?0x201+event.window.event:tmp);
	}
	uint32 Timestamp()const noexcept
	{
		return event.common.timestamp;
	}
	static Event Wait()
	{
		SDL_Event event;
		Error::IfZero(SDL_WaitEvent(&event));
		return Event(event);
	}
	static Event Wait(uint32 time)
	{
		SDL_Event event;
		Error::IfZero(SDL_WaitEventTimeout(&event, time));
		return Event(event);
	}
};
}
#include "events/iterator.h"
namespace events
{
void Pump()noexcept
{
	SDL_PumpEvents();
}
bool Quit()noexcept
{
	return bool(SDL_QuitRequested());
}
bool Has(Type typ)noexcept
{
	return SDL_HasEvent(uint32(typ));
}
bool Has(Type first, Type last)noexcept
{
	return SDL_HasEvents(uint32(first), uint32(last));
}
void Flush(Type type)noexcept
{
	SDL_FlushEvent(uint32(type));
}
void Flush(Type first, Type last)noexcept
{
	SDL_FlushEvents(uint32(first), uint32(last));
}
}