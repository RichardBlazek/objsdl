#pragma once

Joystick::Joystick(Joystick&& joy):joystick(joy.joystick)
{
	joy.joystick=nullptr;
}
Joystick& Joystick::operator=(Joystick&& joy)
{
	joystick=joy.joystick;
	joy.joystick=nullptr;
	return *this;
}
void Joystick::Close()
{
	if(joystick)
	{
		SDL_JoystickClose(joystick);
		joystick=nullptr;
	}
}
Joystick::Joystick(int device_index)
	:joystick(Error::IfZero(SDL_JoystickOpen(device_index))) {}

Joystick::~Joystick()
{
	Close();
}
std::string Joystick::Name()
{
	return Error::IfZero(SDL_JoystickName(joystick));
}
std::string Joystick::NameOf(int device_index)
{
	return Error::IfZero(SDL_JoystickNameForIndex(device_index));
}
uint32 Joystick::Id()
{
	return Error::IfNegative(SDL_JoystickInstanceID(joystick));
}
uint32 Joystick::IdOf(int device_index)
{
	return Error::IfNegative(SDL_JoystickGetDeviceInstanceID(device_index));
}
uint32 Joystick::CountOfAxes()
{
	return Error::IfNegative(SDL_JoystickNumAxes(joystick));
}
uint32 Joystick::CountOfBalls()
{
	return Error::IfNegative(SDL_JoystickNumBalls(joystick));
}
uint32 Joystick::CountOfButtons()
{
	return Error::IfNegative(SDL_JoystickNumButtons(joystick));
}
uint32 Joystick::CountOfHats()
{
	return Error::IfNegative(SDL_JoystickNumHats(joystick));
}
void Joystick::Update()
{
	SDL_JoystickUpdate();
}
uint32 Joystick::Count()
{
	return Error::IfNegative(SDL_NumJoysticks());
}
int16 Joystick::Axis(uint32 axis)
{
	int16 value=SDL_JoystickGetAxis(joystick, axis);
	Error::Condition(value==0&&std::string(SDL_GetError())!="");
	return value;
}
Point Joystick::Ball(uint32 ball)
{
	Point dot;
	Error::IfNegative(SDL_JoystickGetBall(joystick, ball, &dot.x, &dot.y));
	return dot;
}
bool Joystick::IsPressed(uint32 button)
{
	return SDL_JoystickGetButton(joystick, button);
}
auto Joystick::HatPosition(uint32 hat)->Hat
{
	return Hat(SDL_JoystickGetHat(joystick, hat));
}
void Joystick::EnableEventPolling()
{
	Error::IfNegative(SDL_JoystickEventState(1));
}
void Joystick::DisableEventPolling()
{
	Error::IfNegative(SDL_JoystickEventState(0));
}
bool Joystick::IsEnabledEventPolling()
{
	return Error::IfNegative(SDL_JoystickEventState(-1));
}
void Joystick::Lock()
{
	SDL_LockJoysticks();
}
void Joystick::Unlock()
{
	SDL_UnlockJoysticks();
}
bool Joystick::IsAttached()
{
	return SDL_JoystickGetAttached(joystick);
}
auto Joystick::UniqueId()->GUID
{
	GUID tmp=SDL_JoystickGetGUID(joystick);
	bool zero=true;
	for(auto& x:tmp.data)
	{
		zero=zero&&(!x);
	}
	Error::Condition(zero);
	return tmp;
}
auto Joystick::UniqueIdOf(int device_index)->GUID
{
	GUID tmp=SDL_JoystickGetDeviceGUID(device_index);
	bool zero=true;
	for(auto& x:tmp.data)
	{
		zero=zero&&(!x);
	}
	Error::Condition(zero);
	return tmp;
}
std::string Joystick::StringFromGUID(GUID guid)
{
	char tmp[65]={0};
	SDL_JoystickGetGUIDString(guid, tmp, 64);
	return std::string(tmp);
}
auto Joystick::StringToGUID(std::string str)->GUID
{
	return SDL_JoystickGetGUIDFromString(str.c_str());
}
auto Joystick::PowerState()->Power
{
	return Power(SDL_JoystickCurrentPowerLevel(joystick));
}
uint16 Joystick::Vendor()
{
	return Error::IfZero(SDL_JoystickGetVendor(joystick));
}
uint16 Joystick::Product()
{
	return Error::IfZero(SDL_JoystickGetProduct(joystick));
}
uint16 Joystick::ProductVersion()
{
	return Error::IfZero(SDL_JoystickGetProductVersion(joystick));
}
auto Joystick::Kind()->Type
{
	return Type(SDL_JoystickGetType(joystick));
}
uint16 Joystick::VendorOf(int device_index)
{
	return Error::IfZero(SDL_JoystickGetDeviceVendor(device_index));
}
uint16 Joystick::ProductOf(int device_index)
{
	return Error::IfZero(SDL_JoystickGetDeviceProduct(device_index));
}
uint16 Joystick::ProductVersionOf(int device_index)
{
	return Error::IfZero(SDL_JoystickGetDeviceProductVersion(device_index));
}
auto Joystick::KindOf(int device_index)->Type
{
	return Type(SDL_JoystickGetDeviceType(device_index));
}