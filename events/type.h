namespace events
{
enum class Type:uint32
{
	First=SDL_FIRSTEVENT,//Unused

	//Application events
	Quit=SDL_QUIT,//User-requested quit

	//These application events have special meaning on iOS, see README-ios.txt for details
	AppTerminating=SDL_APP_TERMINATING,	/* The application is being terminated by the OS
										Called on iOS in applicationWillTerminate()
										Called on Android in onDestroy()
	*/
	AppLowmemory=SDL_APP_LOWMEMORY,		/* The application is low on memory, free memory if possible.
										Called on iOS in applicationDidReceiveMemoryWarning()
										Called on Android in onLowMemory()
	*/
	AppWillEnterBackground,				/*The application is about to enter the background
										 Called on iOS in applicationWillResignActive()
										 Called on Android in onPause()
	*/
	AppDidEnterBackground,				/*The application did enter the background and may not get CPU for some time
										 Called on iOS in applicationDidEnterBackground()
										 Called on Android in onPause()
	*/
	AppWillEnterForeground,				/*The application is about to enter the foreground
										 Called on iOS in applicationWillEnterForeground()
										 Called on Android in onResume()
	*/
	AppDidEnterForeground,				/*The application is now interactive
										 Called on iOS in applicationDidBecomeActive()
										 Called on Android in onResume()
	*/

	//Window events
	SysWmEvent=SDL_SYSWMEVENT,		//System specific event
    WindowShown,
	WindowHidden,
	WindowExposed,
	WindowMoved,
	WindowResized,
	WindowSizeChanged,
	WindowMinimized,
	WindowMaximized,
	WindowRestored,
	WindowEnter,
	WindowLeave,
	WindowFocusGained,
	WindowFocusLost,
	WindowClose,
	WindowTakeFocus,
	WindowHitTest,

	//Keyboard events
	Keydown=SDL_KEYDOWN,			//Key pressed
	Keyup,					//Key released
	TextEditing,			//Keyboard text editing (composition)
	TextInput,		        //Keyboard text input
	KeyMapChanged=SDL_KEYMAPCHANGED,

	//Mouse events
	MouseMotion=SDL_MOUSEMOTION,		//Mouse moved
	MouseButtonDown,		//Mouse button pressed
	MouseButtonUp,			//Mouse button released
	MouseWheel,				//Mouse wheel motion

	//Joystick events
	JoyAxisMotion=SDL_JOYAXISMOTION,	//Joystick axis motion
	JoyBallMotion,			//Joystick trackball motion
	JoyHatMotion,			//Joystick hat position change
	JoyButtonDown,			//Joystick button pressed
	JoyButtonUp,			//Joystick button released
	JoyDeviceAdded,			//A new joystick has been inserted into the system
	JoyDeviceRemoved,		//An opened joystick has been removed

	//Game controller events
	ControllerAxisMotion=SDL_CONTROLLERAXISMOTION,		//Game controller axis motion
	ControllesButtonDown,			//Game controller button pressed
	ControllerButtonUp,				//Game controller button released
	ControllerDeviceAdded,			//A new Game controller has been inserted into the system
	ControllerDeviceRemoved,		//An opened Game controller has been removed
	ControllerDeviceRemapped,		//The controller mapping was updated

	//Touch events
	FingerDown=SDL_FINGERDOWN,
	FingerUp,
	FingerMotion,

	//Gesture events
	DollarGesture=SDL_DOLLARGESTURE,
	DollarRecord,
	MultiGesture,

	//Clipboard events
	ClipboardUpdate=SDL_CLIPBOARDUPDATE,		//The clipboard changed

	//Drag and drop events
	DropFile=SDL_DROPFILE,			//The system requests a file open
	DropText=SDL_DROPTEXT,
	DropBegin=SDL_DROPBEGIN,
	DropComplete=SDL_DROPCOMPLETE,

	//Audio device events
	AudioDeviceAdded=SDL_AUDIODEVICEADDED,
	AudioDeviceRemoved=SDL_AUDIODEVICEREMOVED,

	//Render events
	RenderTargetsReset=SDL_RENDER_TARGETS_RESET,	//The render targets have been reset
	RenderDeviceReset=SDL_RENDER_DEVICE_RESET,

	//Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use, and should be allocated with SDL_RegisterEvents()
	User=SDL_USEREVENT,

	///This last event is only for bounding internal arrays
	Last=SDL_LASTEVENT
};
}