#pragma once

namespace events
{
struct MouseWheel
{
	uint32 WindowID;
	bool IsMouse;
	Point Move;
};
struct MouseMotion
{
	uint32 WindowID;
	bool IsMouse;
	MouseButtonMask Buttons;
	Point Absolute;
	Point Relative;
};
struct MouseButton
{
	uint32 WindowID;
	bool IsMouse;
	SDL::MouseButton Button;
	Point Position;
	uint8 Clicks;
};
struct Keyboard
{
	uint32 WindowID;
	bool Repeat;
	Scancode Code;
	Keycode Key;
	Keymod Mod;
};
struct User
{
	uint32 WindowID;
	int32 Code;
	void* Data1, *Data2;
};
struct WindowShown
{
	uint32 WindowID;
};
struct WindowHidden
{
	uint32 WindowID;
};
struct WindowExposed
{
	uint32 WindowID;
};
struct WindowMoved
{
	uint32 WindowID;
	Point Position;
};
struct WindowResized
{
	uint32 WindowID;
	Point Size;
};
struct WindowSizeChanged
{
	uint32 WindowID;
	Point Size;
};
struct WindowMinimized
{
	uint32 WindowID;
};
struct WindowMaximized
{
	uint32 WindowID;
};
struct WindowRestored
{
	uint32 WindowID;
};
struct WindowEnter
{
	uint32 WindowID;
};
struct WindowLeave
{
	uint32 WindowID;
};
struct WindowFocusGained
{
	uint32 WindowID;
};
struct WindowFocusLost
{
	uint32 WindowID;
};
struct WindowClose
{
	uint32 WindowID;
};
struct WindowTakeFocus
{
	uint32 WindowID;
};
struct WindowHitTest
{
	uint32 WindowID;
};
struct JoystickAxis
{
	uint32 JoystickID;
	uint8 AxisIndex;
	int16 Value;
};
struct JoystickBall
{
	uint32 JoystickID;
	uint8 BallIndex;
	Point Motion;
};
struct JoystickButton
{
	uint32 JoystickID;
	uint8 ButtonIndex;
};
struct JoystickHat
{
	uint32 JoystickID;
	uint8 HatIndex;
	uint8 Value;
};
struct JoystickDeviceAdded
{
	int32 DeviceIndex;
};
struct JoystickDeviceRemoved
{
	uint32 JoystickID;
};
struct ControllerAxis
{
	uint32 JoystickID;
	GameController::Axis AxisIndex;
	int16 Value;
};
struct ControllerButton
{
	uint32 JoystickID;
	GameController::Button ButtonIndex;
};
struct ControllerDeviceAdded
{
	int32 DeviceIndex;
};
struct ControllerDeviceRemoved
{
	uint32 JoystickID;
};
struct ControllerDeviceRemapped
{
	uint32 JoystickID;
};
struct Drop
{
	uint32 WindowID;
	std::string FileName;
};
struct TouchFinger
{
	int64 TouchID;
	int64 FingerID;
	float x, y;
	float DistanceX;
	float DistanceY;
	float Pressure;
};
struct MultiGesture
{
	int64 TouchID;
	float Rotation;
	float Pinching;
	float x, y;
	uint16 NumberOfFingers;
};
struct DollarGesture
{
	int64 TouchID;
	int64 GestureID;
	uint32 NumberOfFingers;
	float Error, x, y;
};
struct DollarRecord
{
	int64 TouchID;
	int64 GestureID;
};
struct AudioDeviceAdded
{
	uint32 AudioDeviceIndex;
	bool IsCapture;
};
struct AudioDeviceRemoved
{
	uint32 AudioDeviceID;
	bool IsCapture;
};
struct TextEditing
{
	uint32 WindowID;
	std::string Text;
	int32 Start;
	int32 Lenght;
};
struct TextInput
{
	uint32 WindowID;
	std::string Text;
};
struct WindowManagement
{
	SDL::WindowManagement::Message Message;
};
}