#pragma once

#include "events/type.h"
#include "events/structures.h"

namespace events
{
class Event
{
private:
    SDL_Event event;
public:
    friend class Iterator;
    enum class Action: uint8
    {
        Add=SDL_ADDEVENT,
        Peek=SDL_PEEKEVENT,
        Get=SDL_GETEVENT
    };
    Event()noexcept=default;
    MouseWheel MouseWheel()const
    {
        return MouseWheel{event.wheel.windowID, event.wheel.which!=SDL_TOUCH_MOUSEID, Point(event.wheel.x, event.wheel.y)* (event.wheel.direction==SDL_MOUSEWHEEL_FLIPPED?-1:1)};
    }
    MouseMotion MouseMotion()const
    {
        return MouseMotion{event.motion.windowID, event.motion.which!=SDL_TOUCH_MOUSEID, MouseButtonMask(event.motion.state), Point(event.motion.x, event.motion.y), Point(event.motion.xrel, event.motion.yrel)};
    }
    MouseButton MouseButton()const
    {
        return MouseButton{event.button.windowID, event.button.which!=SDL_TOUCH_MOUSEID, SDL::MouseButton(event.button.button), Point(event.button.x, event.button.y), event.button.clicks};
    }
    Keyboard Keyboard()const
    {
        return Keyboard{event.key.windowID, event.key.repeat, Scancode(event.key.keysym.scancode), Keycode(event.key.keysym.sym), Keymod(event.key.keysym.mod)};
    }
    User User()const
    {
        return User{event.user.windowID, event.user.code, event.user.data1, event.user.data2};
    }
    WindowShown WindowShown()const
    {
        return WindowShown{event.window.windowID};
    }
    WindowHidden WindowHidden()const
    {
        return WindowHidden{event.window.windowID};
    }
    WindowExposed WindowExposed()const
    {
        return WindowExposed{event.window.windowID};
    }
    WindowMoved WindowMoved()const
    {
        return WindowMoved{event.window.windowID, Point(event.window.data1, event.window.data2)};
    }
    WindowResized WindowResized()const
    {
        return WindowResized{event.window.windowID, Point(event.window.data1, event.window.data2)};
    }
    WindowSizeChanged WindowSizeChanged()const
    {
        return WindowSizeChanged{event.window.windowID, Point(event.window.data1, event.window.data2)};
    }
    WindowMinimized WindowMinimized()const
    {
        return WindowMinimized{event.window.windowID};
    }
    WindowMaximized WindowMaximized()const
    {
        return WindowMaximized{event.window.windowID};
    }
    WindowRestored WindowRestored()const
    {
        return WindowRestored{event.window.windowID};
    }
    WindowEnter WindowEnter()const
    {
        return WindowEnter{event.window.windowID};
    }
    WindowLeave WindowLeave()const
    {
        return WindowLeave{event.window.windowID};
    }
    WindowFocusGained WindowFocusGained()const
    {
        return WindowFocusGained{event.window.windowID};
    }
    WindowFocusLost WindowFocusLost()const
    {
        return WindowFocusLost{event.window.windowID};
    }
    WindowClose WindowClose()const
    {
        return WindowClose{event.window.windowID};
    }
    WindowTakeFocus WindowTakeFocus()const
    {
        return WindowTakeFocus{event.window.windowID};
    }
    WindowHitTest WindowHitTest()const
    {
        return WindowHitTest{event.window.windowID};
    }
    JoystickAxis JoystickAxis()const
    {
        return JoystickAxis{uint32(event.jaxis.which), event.jaxis.axis, event.jaxis.value};
    }
    JoystickBall JoystickBall()const
    {
        return JoystickBall{uint32(event.jball.which), event.jball.ball, Point(event.jball.xrel, event.jball.yrel)};
    }
    JoystickButton JoystickButton()const
    {
        return JoystickButton{uint32(event.jbutton.which), event.jbutton.button};
    }
    JoystickHat JoystickHat()const
    {
        return JoystickHat{uint32(event.jhat.which), event.jhat.hat, event.jhat.value};
    }
    JoystickDeviceAdded JoystickDeviceAdded()const
    {
        return JoystickDeviceAdded{event.jdevice.which};
    }
    JoystickDeviceRemoved JoystickDeviceRemoved()const
    {
        return JoystickDeviceRemoved{uint32(event.jdevice.which)};
    }
    ControllerAxis ControllerAxis()const
    {
        return ControllerAxis{uint32(event.caxis.which), GameController::Axis(event.caxis.axis), event.caxis.value};
    }
    ControllerButton ControllerButton()const
    {
        return ControllerButton{uint32(event.cbutton.which), GameController::Button(event.cbutton.button)};
    }
    ControllerDeviceAdded ControllerDeviceAdded()const
    {
        return ControllerDeviceAdded{event.cdevice.which};
    }
    ControllerDeviceRemoved ControllerDeviceRemoved()const
    {
        return ControllerDeviceRemoved{uint32(event.cdevice.which)};
    }
    ControllerDeviceRemapped ControllerDeviceRemapped()const
    {
        return ControllerDeviceRemapped{uint32(event.cdevice.which)};
    }
    Drop Drop()const
    {
        Drop result{event.drop.windowID, event.drop.file};
        SDL_free(event.drop.file);
        return result;
    }
    TouchFinger TouchFinger()const
    {
        return TouchFinger{event.tfinger.touchId, event.tfinger.fingerId, event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy, event.tfinger.pressure};
    }
    MultiGesture MultiGesture()const
    {
        return MultiGesture{event.mgesture.touchId, event.mgesture.dTheta, event.mgesture.dDist, event.mgesture.x, event.mgesture.y, event.mgesture.numFingers};
    }
    DollarGesture DollarGesture()const
    {
        return DollarGesture{event.dgesture.touchId, event.dgesture.gestureId, event.dgesture.numFingers, event.dgesture.error, event.dgesture.x, event.dgesture.y};
    }
    DollarRecord DollarRecord()const
    {
        return DollarRecord{event.dgesture.touchId, event.dgesture.gestureId};
    }
    AudioDeviceAdded AudioDeviceAdded()const
    {
        return AudioDeviceAdded{event.adevice.which, event.adevice.iscapture};
    }
    AudioDeviceRemoved AudioDeviceRemoved()const
    {
        return AudioDeviceRemoved{event.adevice.which, event.adevice.iscapture};
    }
    TextEditing TextEditing()const
    {
        return TextEditing{event.edit.windowID, event.edit.text, event.edit.start, event.edit.length};
    }
    TextInput TextInput()const
    {
        return TextInput{event.text.windowID, event.text.text};
    }
    WindowManagement WindowManagement()const
    {
        return WindowManagement{*event.syswm.msg};
    }
    bool Push()
    {
        return bool(Error::IfNegative(SDL_PushEvent(&event)));
    }
    events::Type Type()const noexcept
    {
        auto tmp=event.type;
        tmp=(tmp>=SDL_USEREVENT)?SDL_USEREVENT:tmp;
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