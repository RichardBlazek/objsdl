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
	int tmp=SDL_JoystickInstanceID(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::CountOfAxes()
{
	int tmp=SDL_JoystickNumAxes(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::CountOfBalls()
{
	int tmp=SDL_JoystickNumBalls(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::CountOfButtons()
{
	int tmp=SDL_JoystickNumButtons(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::CountOfHats()
{
	int tmp=SDL_JoystickNumHats(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
void Joystick::Update()
{
	SDL_JoystickUpdate();
}
uint32 Joystick::Count()
{
	int tmp=SDL_NumJoysticks();
	Error::Condition(tmp<0);
	return tmp;
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
	Error::Condition(SDL_JoystickGetBall(joystick, ball, &dot.x, &dot.y)<0);
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
	Error::Condition(SDL_JoystickEventState(1)<0);
}
void Joystick::DisableEventPolling()
{
	Error::Condition(SDL_JoystickEventState(0)<0);
}
bool Joystick::IsEnabledEventPolling()
{
	return Error::IfNegative(SDL_JoystickEventState(-1));
}
bool Joystick::IsAttached()
{
	return SDL_JoystickGetAttached(joystick);
}
auto Joystick::UniqueId()->GUID
{
	GUID tmp=SDL_JoystickGetGUID(joystick);
	bool zero=true;
	for(auto& element:tmp.data)
	{
		if(element)
		{
			zero=false;
		}
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
