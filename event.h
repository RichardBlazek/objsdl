#pragma once

#include "keycode.h"

enum class MouseButton: uint8
{
	Left=SDL_BUTTON_LEFT,
	Right=SDL_BUTTON_RIGHT,
	Middle=SDL_BUTTON_MIDDLE,
	X1=SDL_BUTTON_X1,
	X2=SDL_BUTTON_X2
};
enum class MouseButtonMask: uint8
{
	None=0,
	Left=SDL_BUTTON_LMASK,
	Right=SDL_BUTTON_RMASK,
	Middle=SDL_BUTTON_MMASK,
	X1=SDL_BUTTON_X1MASK,
	X2=SDL_BUTTON_X2MASK
};
MouseButtonMask operator|(MouseButtonMask first, MouseButtonMask second)noexcept
{
	return MouseButtonMask(uint32(first)|uint32(second));
}
MouseButtonMask operator&(MouseButtonMask first, MouseButtonMask second)noexcept
{
	return MouseButtonMask(uint32(first)&uint32(second));
}
MouseButtonMask operator^(MouseButtonMask first, MouseButtonMask second)noexcept
{
	return MouseButtonMask(uint32(first)^uint32(second));
}
MouseButtonMask operator|=(MouseButtonMask& first, MouseButtonMask second)noexcept
{
	return first=(first|second);
}
MouseButtonMask operator&=(MouseButtonMask& first, MouseButtonMask second)noexcept
{
	return first=(first&second);
}
MouseButtonMask operator^=(MouseButtonMask& first, MouseButtonMask second)noexcept
{
	return first=(first^second);
}
MouseButtonMask operator~(MouseButtonMask param)noexcept
{
	return MouseButtonMask(~uint32(param));
}

class Event
{
private:
	SDL_Event* event;
public:
#include "eventtype.h"
	struct MouseWheel
	{
		uint32 WindowID;
        bool IsMouse;
        Point Move;
	};
    MouseWheel GetMouseWheel()const
    {
        return MouseWheel{event->wheel.windowID, event->wheel.which!=SDL_TOUCH_MOUSEID, Point(event->wheel.x, event->wheel.y)*(event->wheel.direction==SDL_MOUSEWHEEL_FLIPPED?-1:1)};
    }
	struct MouseMotion
	{
		uint32 WindowID;
        bool IsMouse;
        MouseButtonMask Buttons;
        Point Absolute;
		Point Relative;
	};
	MouseMotion GetMouseMotion()const
	{
		return MouseMotion{event->motion.windowID, event->motion.which!=SDL_TOUCH_MOUSEID, MouseButtonMask(event->motion.state), Point(event->motion.x, event->motion.y), Point(event->motion.x, event->motion.y)};
	}
	struct MouseButton
	{
		uint32 WindowID;
        bool IsMouse;
        SDL::MouseButton Button;
        Point Position;
        uint8 Clicks;
	};
	MouseButton GetMouseButton()const
	{
        return MouseButton{event->button.windowID, event->button.which!=SDL_TOUCH_MOUSEID, SDL::MouseButton(event->button.button), Point(event->button.x, event->button.y), event->button.clicks};
	}
	struct Keyboard
	{
		uint32 WindowID;
        bool Repeat;
        Scancode Code;
        Keycode Key;
        Keymod Mod;
	};
	Keyboard GetKeyboard()const
	{
        return Keyboard{event->key.windowID, event->key.repeat, Scancode(event->key.keysym.scancode), Keycode(event->key.keysym.sym), Keymod(event->key.keysym.mod)};
	}
	struct User
	{
		uint32 WindowID;
		int32 Code;
		void* Data1, *Data2;
	};
	User GetUser()const
	{
        return User{event->user.windowID, event->user.code, event->user.data1, event->user.data2};
	}
	struct WindowShown
	{
		uint32 WindowID;
	};
	WindowShown GetWindowShown()const
	{
        return WindowShown{event->window.windowID};
	}
	struct WindowHidden
	{
		uint32 WindowID;
	};
	WindowHidden GetWindowHidden()const
	{
        return WindowHidden{event->window.windowID};
	}
	struct WindowExposed
	{
		uint32 WindowID;
	};
	WindowExposed GetWindowExposed()const
	{
        return WindowExposed{event->window.windowID};
	}
	struct WindowMoved
	{
		uint32 WindowID;
		Point Position;
	};
	WindowMoved GetWindowMoved()const
	{
        return WindowMoved{event->window.windowID, Point(event->window.data1, event->window.data2)};
	}
	struct WindowResized
	{
		uint32 WindowID;
		Point Size;
	};
	WindowResized GetWindowResized()const
	{
        return WindowResized{event->window.windowID, Point(event->window.data1, event->window.data2)};
	}
	struct WindowSizeChanged
	{
		uint32 WindowID;
		Point Size;
	};
	WindowSizeChanged GetWindowSizeChanged()const
	{
        return WindowSizeChanged{event->window.windowID, Point(event->window.data1, event->window.data2)};
	}
	struct WindowMinimized
	{
		uint32 WindowID;
	};
	WindowMinimized GetWindowMinimized()const
	{
        return WindowMinimized{event->window.windowID};
	}
	struct WindowMaximized
	{
		uint32 WindowID;
	};
	WindowMaximized GetWindowMaximized()const
	{
        return WindowMaximized{event->window.windowID};
	}
	struct WindowRestored
	{
		uint32 WindowID;
	};
	WindowRestored GetWindowRestored()const
	{
        return WindowRestored{event->window.windowID};
	}
	struct WindowEnter
	{
		uint32 WindowID;
	};
	WindowEnter GetWindowEnter()const
	{
        return WindowEnter{event->window.windowID};
	}
	struct WindowLeave
	{
		uint32 WindowID;
	};
	WindowLeave GetWindowLeave()const
	{
        return WindowLeave{event->window.windowID};
	}
	struct WindowFocusGained
	{
		uint32 WindowID;
	};
	WindowFocusGained GetWindowFocusGained()const
	{
        return WindowFocusGained{event->window.windowID};
	}
	struct WindowFocusLost
	{
		uint32 WindowID;
	};
	WindowFocusLost GetWindowFocusLost()const
	{
        return WindowFocusLost{event->window.windowID};
	}
	struct WindowClose
	{
		uint32 WindowID;
	};
	WindowClose GetWindowClose()const
	{
        return WindowClose{event->window.windowID};
	}
	struct WindowTakeFocus
	{
		uint32 WindowID;
	};
	WindowTakeFocus GetWindowTakeFocus()const
	{
        return WindowTakeFocus{event->window.windowID};
	}
	struct WindowHitTest
	{
		uint32 WindowID;
	};
	WindowHitTest GetWindowHitTest()const
	{
        return WindowHitTest{event->window.windowID};
	}
	struct JoystickAxis
	{
        uint32 JoystickID;
        uint8 AxisIndex;
        int16 Value;
	};
	JoystickAxis GetJoystickAxis()const
	{
		return JoystickAxis{uint32(event->jaxis.which), event->jaxis.axis, event->jaxis.value};
	}
	struct JoystickBall
	{
        uint32 JoystickID;
        uint8 BallIndex;
        Point Motion;
	};
	JoystickBall GetJoystickBall()const
	{
        return JoystickBall{uint32(event->jball.which), event->jball.ball, Point(event->jball.xrel, event->jball.yrel)};
	}
	struct JoystickButton
	{
        uint32 JoystickID;
        uint8 ButtonIndex;
	};
	JoystickButton GetJoystickButton()const
	{
        return JoystickButton{uint32(event->jbutton.which), event->jbutton.button};
	}
	struct JoystickHat
	{
        uint32 JoystickID;
        uint8 HatIndex;
        uint8 Value;
	};
	JoystickHat GetJoystickHat()const
	{
        return JoystickHat{uint32(event->jhat.which), event->jhat.hat, event->jhat.value};
	}
	struct JoystickDeviceAdded
	{
        int32 DeviceIndex;
	};
	JoystickDeviceAdded GetJoystickDeviceAdded()const
	{
        return JoystickDeviceAdded{event->jdevice.which};
	}
	struct JoystickDeviceRemoved
	{
        uint32 JoystickID;
	};
	JoystickDeviceRemoved GetJoystickDeviceRemoved()const
	{
        return JoystickDeviceRemoved{uint32(event->jdevice.which)};
	}
	struct ControllerAxis
	{
        uint32 JoystickID;
        GameController::Axis AxisIndex;
        int16 Value;
	};
	ControllerAxis GetControllerAxis()const
	{
		return ControllerAxis{uint32(event->caxis.which), GameController::Axis(event->caxis.axis), event->caxis.value};
	}
	struct ControllerButton
	{
        uint32 JoystickID;
        GameController::Button ButtonIndex;
	};
	ControllerButton GetControllerButton()const
	{
		return ControllerButton{uint32(event->cbutton.which), GameController::Button(event->cbutton.button)};
	}
	struct ControllerDeviceAdded
	{
        int32 DeviceIndex;
	};
	ControllerDeviceAdded GetControllerDeviceAdded()const
	{
        return ControllerDeviceAdded{event->cdevice.which};
	}
	struct ControllerDeviceRemoved
	{
        uint32 JoystickID;
	};
	ControllerDeviceRemoved GetControllerDeviceRemoved()const
	{
        return ControllerDeviceRemoved{uint32(event->cdevice.which)};
	}
	struct ControllerDeviceRemapped
	{
        uint32 JoystickID;
	};
	ControllerDeviceRemapped GetControllerDeviceRemapped()const
	{
        return ControllerDeviceRemapped{uint32(event->cdevice.which)};
	}
    struct Drop
    {
        uint32 WindowID;
        std::string FileName;
    };
    Drop GetDrop()const
    {
        Drop result{event->drop.windowID, event->drop.file};
        SDL_free(event->drop.file);
    	return result;
    }
    struct TouchFinger
    {
    	int64 TouchID;
        int64 FingerID;
        float x, y;
        float DistanceX;
        float DistanceY;
        float Pressure;
    };
	TouchFinger GetTouchFinger()const
	{
        return TouchFinger{event->tfinger.touchId, event->tfinger.fingerId, event->tfinger.x, event->tfinger.y, event->tfinger.dx, event->tfinger.dy, event->tfinger.pressure};
	}
	struct MultiGesture
	{
        int64 TouchID;
        float Rotation;
        float Pinching;
        float x, y;
        uint16 NumberOfFingers;
	};
	MultiGesture GetMultiGesture()const
	{
        return MultiGesture{event->mgesture.touchId, event->mgesture.dTheta, event->mgesture.dDist, event->mgesture.x, event->mgesture.y, event->mgesture.numFingers};
	}
	struct DollarGesture
	{
        int64 TouchID;
        int64 GestureID;
        uint32 NumberOfFingers;
        float Error, x, y;
	};
	DollarGesture GetDollarGesture()const
	{
        return DollarGesture{event->dgesture.touchId, event->dgesture.gestureId, event->dgesture.numFingers, event->dgesture.error, event->dgesture.x, event->dgesture.y};
	}
	struct DollarRecord
	{
        int64 TouchID;
        int64 GestureID;
	};
	DollarRecord GetDollarRecord()const
	{
        return DollarRecord{event->dgesture.touchId, event->dgesture.gestureId};
	}
	struct AudioDeviceAdded
	{
		uint32 AudioDeviceIndex;
		bool IsCapture;
	};
	AudioDeviceAdded GetAudioDeviceAdded()const
	{
        return AudioDeviceAdded{event->adevice.which, event->adevice.iscapture};
	}
	struct AudioDeviceRemoved
	{
		uint32 AudioDeviceID;
		bool IsCapture;
	};
	AudioDeviceRemoved GetAudioDeviceRemoved()const
	{
        return AudioDeviceRemoved{event->adevice.which, event->adevice.iscapture};
	}
	struct TextEditing
	{
        uint32 WindowID;
        std::string Text;
        int32 Start;
        int32 Lenght;
	};
	TextEditing GetTextEditing()const
	{
        return TextEditing{event->edit.windowID, event->edit.text, event->edit.start, event->edit.length};
	}
	struct TextInput
	{
        uint32 WindowID;
        std::string Text;
	};
	TextInput GetTextInput()const
	{
        return TextInput{event->text.windowID, event->text.text};
	}
	struct WindowManagement
	{
		SDL::WindowManagement::Message Message;
	};
	WindowManagement GetWindowManagement()const
	{
        return WindowManagement{*event->syswm.msg};
	}
	enum class Action: uint8
	{
		Add=SDL_ADDEVENT,
		Peek=SDL_PEEKEVENT,
		Get=SDL_GETEVENT
	};
	Event()noexcept:event(new SDL_Event){}
	~Event()noexcept
	{
		delete event;
	}
	Event(const Event& action)noexcept:event(new SDL_Event(*action.event)){}
	Event(Event&& action)noexcept:event(action.event)
	{
		action.event=nullptr;
	}
	Event& operator=(const Event& action)noexcept
	{
		*event=*action.event;
		return *this;
	}
	static void Pump()noexcept
	{
		SDL_PumpEvents();
	}
	static bool QuitRequested()noexcept
	{
		return bool(SDL_QuitRequested());
	}
	static bool NotQuit()noexcept
	{
		return !QuitRequested();
	}
	static bool Has(Type typ)noexcept
	{
		return SDL_HasEvent(uint32(typ));
	}
	static bool Has(Type first, Type last)noexcept
	{
		return SDL_HasEvents(uint32(first), uint32(last));
	}
	static void Flush(Type type)noexcept
	{
		SDL_FlushEvent(uint32(type));
	}
	static void Flush(Type first, Type last)noexcept
	{
		SDL_FlushEvents(uint32(first), uint32(last));
	}
	void Wait()
	{
		Error::IfZero(SDL_WaitEvent(event));
	}
	void WaitTimeout(uint32 time)
	{
		Error::IfZero(SDL_WaitEventTimeout(event, time));
	}
	bool Push()
	{
		int result=SDL_PushEvent(event);
		Error::IfNegative(result);
		return bool(result);
	}
	bool Next()noexcept
	{
		return bool(SDL_PollEvent(event));
	}
	Type GetType()const noexcept
	{
		auto tmp=event->type;
		tmp=(tmp>=SDL_USEREVENT)?SDL_USEREVENT:tmp;
		return Type(tmp==SDL_WINDOWEVENT?0x201+event->window.event:tmp);
	}
	uint32 GetTimestamp()const noexcept
	{
		return event->common.timestamp;
	}
	template<typename EventCallback>
	void Call(EventCallback call)
	{
        while(Next())
		{
			call(*this);
		}
	}
};