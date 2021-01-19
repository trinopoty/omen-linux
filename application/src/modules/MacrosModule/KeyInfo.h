#ifndef OMENLINUX_KEYINFO_H
#define OMENLINUX_KEYINFO_H

#include <map>
#include <linux/input-event-codes.h>

/* AT Set 1 */

const uint32_t PrintScreenMake = 0xE02AE037;
const uint32_t PrintScreenBreak = 0xE0B7E0AA;

typedef struct _KeyInfo {
    uint32_t key;
    uint32_t scancode;
    const char* label;
} KeyInfo;

static const std::map<uint32_t, KeyInfo> keys({
    { KEY_0, { .key = KEY_0, .scancode = 0x0B, .label = "D0" } },
    { KEY_1, { .key = KEY_1, .scancode = 0x02, .label = "D1" } },
    { KEY_2, { .key = KEY_2, .scancode = 0x03, .label = "D2" } },
    { KEY_3, { .key = KEY_3, .scancode = 0x04, .label = "D3" } },
    { KEY_4, { .key = KEY_4, .scancode = 0x05, .label = "D4" } },
    { KEY_5, { .key = KEY_5, .scancode = 0x06, .label = "D5" } },
    { KEY_6, { .key = KEY_6, .scancode = 0x07, .label = "D6" } },
    { KEY_7, { .key = KEY_7, .scancode = 0x08, .label = "D7" } },
    { KEY_8, { .key = KEY_8, .scancode = 0x09, .label = "D8" } },
    { KEY_9, { .key = KEY_9, .scancode = 0x0A, .label = "D9" } },

    { KEY_NUMLOCK, { .key = KEY_NUMLOCK, .scancode = 0x45, .label = "NumLock" } },
    { KEY_KP0, { .key = KEY_KP0, .scancode = 0x52, .label = "Num 0" } },
    { KEY_KP1, { .key = KEY_KP1, .scancode = 0x4F, .label = "Num 1" } },
    { KEY_KP2, { .key = KEY_KP2, .scancode = 0x50, .label = "Num 2" } },
    { KEY_KP3, { .key = KEY_KP3, .scancode = 0x51, .label = "Num 3" } },
    { KEY_KP4, { .key = KEY_KP4, .scancode = 0x4B, .label = "Num 4" } },
    { KEY_KP5, { .key = KEY_KP5, .scancode = 0x4C, .label = "Num 5" } },
    { KEY_KP6, { .key = KEY_KP6, .scancode = 0x4D, .label = "Num 6" } },
    { KEY_KP7, { .key = KEY_KP7, .scancode = 0x47, .label = "Num 7" } },
    { KEY_KP8, { .key = KEY_KP8, .scancode = 0x48, .label = "Num 8" } },
    { KEY_KP9, { .key = KEY_KP9, .scancode = 0x49, .label = "Num 9" } },
    { KEY_KPDOT, { .key = KEY_KPDOT, .scancode = 0x53, .label = "Num Dot" } },
    { KEY_KPMINUS, { .key = KEY_KPMINUS, .scancode = 0x4A, .label = "Num -" } },
    { KEY_KPPLUS, { .key = KEY_KPPLUS, .scancode = 0x4E, .label = "Num +" } },
    { KEY_KPSLASH, { .key = KEY_KPSLASH, .scancode = 0xE035, .label = "Num /" } },
    { KEY_KPASTERISK, { .key = KEY_KPASTERISK, .scancode = 0x37, .label = "Num *" } },
    { KEY_KPENTER, { .key = KEY_KPENTER, .scancode = 0xE01C, .label = "Num Enter" } },

    { KEY_A, { .key = KEY_A, .scancode = 0x1E, .label = "A" } },
    { KEY_B, { .key = KEY_B, .scancode = 0x30, .label = "B" } },
    { KEY_C, { .key = KEY_C, .scancode = 0x2E, .label = "C" } },
    { KEY_D, { .key = KEY_D, .scancode = 0x20, .label = "D" } },
    { KEY_E, { .key = KEY_E, .scancode = 0x12, .label = "E" } },
    { KEY_F, { .key = KEY_F, .scancode = 0x21, .label = "F" } },
    { KEY_G, { .key = KEY_G, .scancode = 0x22, .label = "G" } },
    { KEY_H, { .key = KEY_H, .scancode = 0x23, .label = "H" } },
    { KEY_I, { .key = KEY_I, .scancode = 0x17, .label = "I" } },
    { KEY_J, { .key = KEY_J, .scancode = 0x24, .label = "J" } },
    { KEY_K, { .key = KEY_K, .scancode = 0x25, .label = "K" } },
    { KEY_L, { .key = KEY_L, .scancode = 0x26, .label = "L" } },
    { KEY_M, { .key = KEY_M, .scancode = 0x32, .label = "M" } },
    { KEY_N, { .key = KEY_N, .scancode = 0x31, .label = "N" } },
    { KEY_O, { .key = KEY_O, .scancode = 0x18, .label = "O" } },
    { KEY_P, { .key = KEY_P, .scancode = 0x19, .label = "P" } },
    { KEY_Q, { .key = KEY_Q, .scancode = 0x10, .label = "Q" } },
    { KEY_R, { .key = KEY_R, .scancode = 0x13, .label = "R" } },
    { KEY_S, { .key = KEY_S, .scancode = 0x1F, .label = "S" } },
    { KEY_T, { .key = KEY_T, .scancode = 0x14, .label = "T" } },
    { KEY_U, { .key = KEY_U, .scancode = 0x16, .label = "U" } },
    { KEY_V, { .key = KEY_V, .scancode = 0x2F, .label = "V" } },
    { KEY_W, { .key = KEY_W, .scancode = 0x11, .label = "W" } },
    { KEY_X, { .key = KEY_X, .scancode = 0x2D, .label = "X" } },
    { KEY_Y, { .key = KEY_Y, .scancode = 0x15, .label = "Y" } },
    { KEY_Z, { .key = KEY_Z, .scancode = 0x2C, .label = "Z" } },

    { KEY_GRAVE, { .key = KEY_GRAVE, .scancode = 0x29, .label = "`" } },
    { KEY_MINUS, { .key = KEY_MINUS, .scancode = 0x0C, .label = "-" } },
    { KEY_EQUAL, { .key = KEY_EQUAL, .scancode = 0x0D, .label = "=" } },
    { KEY_BACKSLASH, { .key = KEY_BACKSLASH, .scancode = 0x2B, .label = "\\" } },
    { KEY_LEFTBRACE, { .key = KEY_LEFTBRACE, .scancode = 0x1A, .label = "[" } },
    { KEY_RIGHTBRACE, { .key = KEY_RIGHTBRACE, .scancode = 0x1B, .label = "]" } },
    { KEY_SEMICOLON, { .key = KEY_SEMICOLON, .scancode = 0x27, .label = ";" } },
    { KEY_APOSTROPHE, { .key = KEY_APOSTROPHE, .scancode = 0x28, .label = "'" } },
    { KEY_COMMA, { .key = KEY_COMMA, .scancode = 0x33, .label = "," } },
    { KEY_DOT, { .key = KEY_DOT, .scancode = 0x34, .label = "." } },
    { KEY_SLASH, { .key = KEY_SLASH, .scancode = 0x35, .label = "/" } },

    { KEY_BACKSPACE, { .key = KEY_BACKSPACE, .scancode = 0x0E, .label = "Backspace" } },
    { KEY_SPACE, { .key = KEY_SPACE, .scancode = 0x39, .label = "Space" } },
    { KEY_TAB, { .key = KEY_TAB, .scancode = 0x0F, .label = "Tab" } },
    { KEY_CAPSLOCK, { .key = KEY_CAPSLOCK, .scancode = 0x3A, .label = "Capslock" } },

    { KEY_LEFTSHIFT, { .key = KEY_LEFTSHIFT, .scancode = 0x2A, .label = "Left Shift" } },
    { KEY_LEFTCTRL, { .key = KEY_LEFTCTRL, .scancode = 0x1D, .label = "Left Ctrl" } },
    { KEY_LEFTMETA, { .key = KEY_LEFTMETA, .scancode = 0xE05B, .label = "Left Win" } },
    { KEY_LEFTALT, { .key = KEY_LEFTALT, .scancode = 0x38, .label = "Left Alt" } },
    { KEY_RIGHTSHIFT, { .key = KEY_RIGHTSHIFT, .scancode = 0x36, .label = "Right Shift" } },
    { KEY_RIGHTCTRL, { .key = KEY_RIGHTCTRL, .scancode = 0xE01D, .label = "Right Ctrl" } },
    { KEY_RIGHTMETA, { .key = KEY_RIGHTMETA, .scancode = 0xE05C, .label = "Right Win" } },
    { KEY_RIGHTALT, { .key = KEY_RIGHTALT, .scancode = 0xE038, .label = "Right Alt" } },
    { KEY_MENU, { .key = KEY_MENU, .scancode = 0xE05D, .label = "Menu" } },

    { KEY_INSERT, { .key = KEY_INSERT, .scancode = 0xE052, .label = "Insert" } },
    { KEY_DELETE, { .key = KEY_DELETE, .scancode = 0xE053, .label = "Delete" } },
    { KEY_HOME, { .key = KEY_HOME, .scancode = 0xE047, .label = "Home" } },
    { KEY_END, { .key = KEY_END, .scancode = 0xE04F, .label = "End" } },
    { KEY_PAGEUP, { .key = KEY_PAGEUP, .scancode = 0xE049, .label = "Page Up" } },
    { KEY_PAGEDOWN, { .key = KEY_PAGEDOWN, .scancode = 0xE051, .label = "Page Down" } },
    { KEY_SCROLLLOCK, { .key = KEY_SCROLLLOCK, .scancode = 0x46, .label = "Scroll Lock" } },
    { KEY_SYSRQ, { .key = KEY_SYSRQ, .scancode = 0x00, .label = "Print Screen" } },             // This has special scancodes

    { KEY_UP, { .key = KEY_UP, .scancode = 0xE048, .label = "Up Arrow" } },
    { KEY_DOWN, { .key = KEY_DOWN, .scancode = 0xE050, .label = "Down Arrow" } },
    { KEY_LEFT, { .key = KEY_LEFT, .scancode = 0xE04B, .label = "Left Arrow" } },
    { KEY_RIGHT, { .key = KEY_RIGHT, .scancode = 0xE04D, .label = "Right Arrow" } },

    { KEY_ESC, { .key = KEY_ESC, .scancode = 0x01, .label = "Escape" } },
    { KEY_F1, { .key = KEY_F1, .scancode = 0x3B, .label = "F1" } },
    { KEY_F2, { .key = KEY_F2, .scancode = 0x3C, .label = "F2" } },
    { KEY_F3, { .key = KEY_F3, .scancode = 0x3D, .label = "F3" } },
    { KEY_F4, { .key = KEY_F4, .scancode = 0x3E, .label = "F4" } },
    { KEY_F5, { .key = KEY_F5, .scancode = 0x3F, .label = "F5" } },
    { KEY_F6, { .key = KEY_F6, .scancode = 0x40, .label = "F6" } },
    { KEY_F7, { .key = KEY_F7, .scancode = 0x41, .label = "F7" } },
    { KEY_F8, { .key = KEY_F8, .scancode = 0x42, .label = "F8" } },
    { KEY_F9, { .key = KEY_F9, .scancode = 0x43, .label = "F9" } },
    { KEY_F10, { .key = KEY_F10, .scancode = 0x44, .label = "F10" } },
    { KEY_F11, { .key = KEY_F11, .scancode = 0x57, .label = "F11" } },
    { KEY_F12, { .key = KEY_F12, .scancode = 0x58, .label = "F12" } },
});

#endif //OMENLINUX_KEYINFO_H
