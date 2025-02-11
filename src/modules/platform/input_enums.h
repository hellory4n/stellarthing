#pragma once

/// keyboard keys
typedef enum {
    /// this key isn't in any keyboard ever
    ST_KEY_UNKNOWN         = 0,
    /// '
    ST_KEY_APOSTROPHE      = 39,
    /// ,
    ST_KEY_COMMA           = 44,
    /// -
    ST_KEY_MINUS           = 45,
    /// .
    ST_KEY_PERIOD          = 46,
    /// /
    ST_KEY_SLASH           = 47,
    ST_KEY_NUM0            = 48,
    ST_KEY_NUM1            = 49,
    ST_KEY_NUM2            = 50,
    ST_KEY_NUM3            = 51,
    ST_KEY_NUM4            = 52,
    ST_KEY_NUM5            = 53,
    ST_KEY_NUM6            = 54,
    ST_KEY_NUM7            = 55,
    ST_KEY_NUM8            = 56,
    ST_KEY_NUM9            = 57,
    /// ;
    ST_KEY_SEMICOLON       = 59,
    /// =
    ST_KEY_EQUAL           = 61,
    ST_KEY_A               = 65,
    ST_KEY_B               = 66,
    ST_KEY_C               = 67,
    ST_KEY_D               = 68,
    ST_KEY_E               = 69,
    ST_KEY_F               = 70,
    ST_KEY_G               = 71,
    ST_KEY_H               = 72,
    ST_KEY_I               = 73,
    ST_KEY_J               = 74,
    ST_KEY_K               = 75,
    ST_KEY_L               = 76,
    ST_KEY_M               = 77,
    ST_KEY_N               = 78,
    ST_KEY_O               = 79,
    ST_KEY_P               = 80,
    ST_KEY_Q               = 81,
    ST_KEY_R               = 82,
    ST_KEY_S               = 83,
    ST_KEY_T               = 84,
    ST_KEY_U               = 85,
    ST_KEY_V               = 86,
    ST_KEY_W               = 87,
    ST_KEY_X               = 88,
    ST_KEY_Y               = 89,
    ST_KEY_Z               = 90,
    /// [
    ST_KEY_LEFT_BRACKET    = 91,
    /// / but back
    ST_KEY_BACKSLASH       = 92,
    /// ]
    ST_KEY_RIGHT_BRACKET   = 93,
    /// `
    ST_KEY_GRAVE           = 96,
    ///  
    ST_KEY_SPACE           = 32,
    ST_KEY_ESCAPE          = 256,
    ST_KEY_ENTER           = 257,
    ST_KEY_TAB             = 258,
    ST_KEY_BACKSPACE       = 259,
    ST_KEY_INSERT          = 260,
    ST_KEY_DELETE          = 261,
    ST_KEY_RIGHT           = 262,
    ST_KEY_LEFT            = 263,
    ST_KEY_DOWN            = 264,
    ST_KEY_UP              = 265,
    ST_KEY_PAGE_UP         = 266,
    ST_KEY_PAGE_DOWN       = 267,
    ST_KEY_HOME            = 268,
    ST_KEY_END             = 269,
    ST_KEY_CAPS_LOCK       = 280,
    ST_KEY_SCROLL_LOCK     = 281,
    ST_KEY_NUM_LOCK        = 282,
    ST_KEY_PRINT_SCREEN    = 283,
    ST_KEY_PAUSE           = 284,
    ST_KEY_F1              = 290,
    ST_KEY_F2              = 291,
    ST_KEY_F3              = 292,
    ST_KEY_F4              = 293,
    ST_KEY_F5              = 294,
    ST_KEY_F6              = 295,
    ST_KEY_F7              = 296,
    ST_KEY_F8              = 297,
    ST_KEY_F9              = 298,
    ST_KEY_F10             = 299,
    ST_KEY_F11             = 300,
    ST_KEY_F12             = 301,
    ST_KEY_LEFT_SHIFT      = 340,
    ST_KEY_LEFT_CONTROL    = 341,
    ST_KEY_LEFT_ALT        = 342,
    ST_KEY_LEFT_SUPER      = 343,
    ST_KEY_RIGHT_SHIFT     = 344,
    ST_KEY_RIGHT_CONTROL   = 345,
    ST_KEY_RIGHT_ALT       = 346,
    ST_KEY_RIGHT_SUPER     = 347,
    ST_KEY_KB_MENU         = 348,
    ST_KEY_KP_0            = 320,
    ST_KEY_KP_1            = 321,
    ST_KEY_KP_2            = 322,
    ST_KEY_KP_3            = 323,
    ST_KEY_KP_4            = 324,
    ST_KEY_KP_5            = 325,
    ST_KEY_KP_6            = 326,
    ST_KEY_KP_7            = 327,
    ST_KEY_KP_8            = 328,
    ST_KEY_KP_9            = 329,
    ST_KEY_KP_DECIMAL      = 330,
    ST_KEY_KP_DIVIDE       = 331,
    ST_KEY_KP_MULTIPLY     = 332,
    ST_KEY_KP_SUBTRACT     = 333,
    ST_KEY_KP_ADD          = 334,
    ST_KEY_KP_ENTER        = 335,
    ST_KEY_KP_EQUAL        = 336,
    ST_KEY_BACK            = 4,
    ST_KEY_MENU            = 82,
    ST_KEY_VOLUME_UP       = 24,
    ST_KEY_VOLUME_DOWN     = 25
} StKey;

/// bouse mutton
typedef enum {
    /// left
    ST_MOUSE_BUTTON_LEFT    = 0,
    /// right
    ST_MOUSE_BUTTON_RIGHT   = 1,
    /// pressed wheel
    ST_MOUSE_BUTTON_MIDDLE  = 2,
    /// only on fancy mouses
    ST_MOUSE_BUTTON_SIDE    = 3,
    /// only on fancy mouses
    ST_MOUSE_BUTTON_EXTRA   = 4,
    /// only on fancy mouses
    ST_MOUSE_BUTTON_FORWARD = 5,
    /// only on fancy mouses
    ST_MOUSE_BUTTON_BACK    = 6,
} StMouseButton;