#pragma once

enum class Scancode : uint16
{
    Unknown=0,

    A=4,
    B=5,
    C=6,
    D=7,
    E=8,
    F=9,
    G=10,
    H=11,
    I=12,
    J=13,
    K=14,
    L=15,
    M=16,
    N=17,
    O=18,
    P=19,
    Q=20,
    R=21,
    S=22,
    T=23,
    U=24,
    V=25,
    W=26,
    X=27,
    Y=28,
    Z=29,

    n1=30,
    n2=31,
    n3=32,
    n4=33,
    n5=34,
    n6=35,
    n7=36,
    n8=37,
    n9=38,
    n0=39,

    Return=40,
    Escape=41,
    Backspace=42,
    Tab=43,
    Space=44,

    Minus=45,
    Equals=46,
    LeftBracket=47,
    RightBracket=48,
    Backslash=49, /* Located at the lower left of the return key on ISO keyboards and at the right end
								of the QWERTY row on ANSI keyboards. Produces REVERSE SOLIDUS (backslash) and
								VERTICAL LINE in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac
								layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN and POUND SIGN
								in a Swiss German layout, NUMBER SIGN and APOSTROPHE in a German layout, GRAVE
								ACCENT and POUND SIGN in a French Mac layout, and ASTERISK and MICRO SIGN in a
								French Windows layout.
	*/
    NonUsHash=50, /* ISO USB keyboards actually use this code
								instead of 49 for the same key, but all
								OSes I've seen treat the two codes
								identically. So, as an implementor, unless
								your keyboard generates both of those
								codes and your OS treats them differently,
								you should generate BACKSLASH
								instead of this code. As a user, you
								should not rely on this code because SDL
								will never generate it with most (all?)
								keyboards.
	*/
    Semicolon=51,
    Apostrophe=52,
    Grave=53,

    Comma=54,
    Period=55,
    Slash=56,

    CapsLock=57,

    F1=58,
    F2=59,
    F3=60,
    F4=61,
    F5=62,
    F6=63,
    F7=64,
    F8=65,
    F9=66,
    F10=67,
    F11=68,
    F12=69,

    PrintScreen=70,
    ScrollLock=71,
    Pause=72,
    Insert=73, //insert on PC, help on some Mac keyboards (but does send code 73, not 117)
    Home=74,
    PageUp=75,
    Delete=76,
    End=77,
    PageDown=78,
    Right=79,
    Left=80,
    Down=81,
    Up=82,

    NumLockOrClear=83, //num lock on PC, clear on Mac keyboards
	KpDivide=84,
    KpMultiply=85,
    KpMinus=86,
    KpPlus=87,
    KpEnter=88,
    Kp1=89,
    Kp2=90,
    Kp3=91,
    Kp4=92,
    Kp5=93,
    Kp6=94,
    Kp7=95,
    Kp8=96,
    Kp9=97,
    Kp0=98,
    KpPeriod=99,

    NonUsBackslash=100,

    Application=101, /// windows contextual menu, compose
    Power=102,

    KpEquals=103,
    F13=104,
    F14=105,
    F15=106,
    F16=107,
    F17=108,
    F18=109,
    F19=110,
    F20=111,
    F21=112,
    F22=113,
    F23=114,
    F24=115,
    Execute=116,
    Help=117,
    Menu=118,
    Select=119,
    Stop=120,
    Again=121,   /// redo
    Undo=122,
    Cut=123,
    Copy=124,
    Paste=125,
    Find=126,
    Mute=127,
    VolumeUp=128,
    VolumeDown=129,
	LockingCapsLock=130,
	LockingNumLock=131,
	LockingScrollLock=132,
    KpComma=133,
    KpEqualsAs400=134,

    International1=135, /// used on Asian keyboards, see footnotes in USB doc
    International2=136,
    International3=137, /// Yen
    International4=138,
    International5=139,
    International6=140,
    International7=141,
    International8=142,
    International9=143,
    Lang1=144, /// Hangul/English toggle
    Lang2=145, /// Hanja conversion
    Lang3=146, /// Katakana
    Lang4=147, /// Hiragana
    Lang5=148, /// Zenkaku/Hankaku
    Lang6=149, /// reserved
    Lang7=150, /// reserved
    Lang8=151, /// reserved
    Lang9=152, /// reserved

    AltErase=153, /// Erase-Eaze
    SysReq=154,
    Cancel=155,
    Clear=156,
    Prior=157,
    Return2=158,
    Separator=159,
    Out=160,
    Oper=161,
    ClearAgain=162,
    CrSel=163,
    ExSel=164,

    Kp00=176,
    Kp000=177,
    ThousandsSeparator=178,
    DecimalSeparator=179,
    CurrencyUnit=180,
    CurrencySubunit=181,
    KpLeftParen=182,
    KpRightParen=183,
    KpLeftBrace=184,
    KpRightBrace=185,
    KpTab=186,
    KpBackspace=187,
    KpA=188,
    KpB=189,
    KpC=190,
    KpD=191,
    KpE=192,
    KpF=193,
    KpXor=194,
    KpPower=195,
    KpPercent=196,
    KpLess=197,
    KpGreater=198,
    KpAmpersand=199,
    KpDblAmpersand=200,
    KpVerticalBar=201,
    KpDblVerticalBar=202,
    KpColon=203,
    KpHash=204,
    KpSpace=205,
    KpAt=206,
    KpExclam=207,
    KpMemStore=208,
    KpMemRecall=209,
    KpMemClear=210,
    KpMemAdd=211,
    KpMemSubstract=212,
    KpMemMultiply=213,
    KpMemDivide=214,
    KpPlusMinus=215,
    KpClear=216,
    KpClearEntry=217,
    KpBinary=218,
    KpOctal=219,
    KpDecimal=220,
    KpHexadecimal=221,

    LCtrl=224,
    LShift=225,
    LAlt=226, /// alt, option
    LGUI=227, /// windows, command (apple), meta
    RCtrl=228,
    RShift=229,
    RAlt=230, /// alt gr, option
    RGUI=231, /// windows, command (apple), meta

    Mode=257,

    AudioNext=258,
    AudioPrev=259,
    AudioStop=260,
    AudioPlay=261,
    AudioMute=262,
    MediaSelect=263,
    Www=264,
    Mail=265,
    Calculator=266,
    Computer=267,
    AcSearch=268,
    AcHome=269,
    AcBack=270,
    AcForward=271,
    AcStop=272,
    AcRefresh=273,
    AcBookmarks=274,

    BrightnessDown=275,
    BrightnessUp=276,
    DisplaySwitch=277, ///display mirroring/dual display switch, video mode switch
    KbDillumToggle=278,
    KbDillumDown=279,
    KbDillumUp=280,
    Eject=281,
    Sleep=282,

    App1=283,
    App2=284,

    // Add any other keys here.

    NumScancodes=512 ///not a key, just marks the number of scancodes for array bounds
};