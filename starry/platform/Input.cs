using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Silk.NET.GLFW;
namespace starry;

public static class Input {
    enum PressedState {
        INACTIVE,
        JUST_PRESSED,
        HOLDING,
        JUST_RELEASED,
    }

    // i hope you dont have a keyboard with 512 keys
    const int MAX_KEYS = 512;
    // or a mouse with 20 buttons
    const int MAX_MOUSE_BUTTONS = 8;
    static PressedState[] keys = new PressedState[MAX_KEYS];
    static PressedState[] mouse = new PressedState[MAX_MOUSE_BUTTONS];
    static vec2 mousepos = (0, 0);
    public static vec2 mousePosition => mousePosition;

    internal static void update()
    {
        for (int i = 0; i < MAX_KEYS; i++) {
            if (keys[i] == PressedState.JUST_PRESSED) keys[i] = PressedState.HOLDING;
            else if (keys[i] == PressedState.JUST_RELEASED) keys[i] = PressedState.INACTIVE;
        }

        for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
            if (mouse[i] == PressedState.JUST_PRESSED) mouse[i] = PressedState.HOLDING;
            else if (mouse[i] == PressedState.JUST_RELEASED) mouse[i] = PressedState.INACTIVE;
        }
    }

    internal static void keyCallback(Keys key, InputAction action)
    {
        if (key >= 0 && (int)key < MAX_KEYS) {
            if (action != InputAction.Release) {
                if (keys[(int)key] == PressedState.INACTIVE || keys[(int)key] == PressedState.JUST_RELEASED) {
                    keys[(int)key] = PressedState.JUST_PRESSED;
                }
                else {
                    keys[(int)key] = PressedState.HOLDING;
                }
            }
            else {
                if (keys[(int)key] == PressedState.HOLDING || keys[(int)key] == PressedState.JUST_PRESSED) {
                    keys[(int)key] = PressedState.JUST_RELEASED;
                }
                else {
                    keys[(int)key] = PressedState.INACTIVE;
                }
            }
        }
    }

    internal static void mouseButtonCallback(MouseButton btn, InputAction action)
    {
        if (btn >= 0 && (int)btn < MAX_MOUSE_BUTTONS) {
            if (action != InputAction.Release) {
                if (mouse[(int)btn] == PressedState.INACTIVE || mouse[(int)btn] == PressedState.JUST_RELEASED) {
                    mouse[(int)btn] = PressedState.JUST_PRESSED;
                }
                else {
                    mouse[(int)btn] = PressedState.HOLDING;
                }
            }
            else {
                if (mouse[(int)btn] == PressedState.HOLDING || mouse[(int)btn] == PressedState.JUST_PRESSED) {
                    mouse[(int)btn] = PressedState.JUST_RELEASED;
                }
                else {
                    mouse[(int)btn] = PressedState.INACTIVE;
                }
            }
        }
    }

    internal static void mouseCursorCallback(double x, double y)
    {
        // mate
        /*mousepos = (
            (x * Graphics.scale) - Graphics.offset.x,
            (y * Graphics.scale) - Graphics.offset.y
        );*/
        mousepos = (x, y);
    }

    // the fucking api
    /// <summary>
    /// if true, the key isn't pressed
    /// </summary>
    public static bool isKeyNotPressed(Key key) => keys[(int)key] == PressedState.INACTIVE;

    /// <summary>
    /// if true, the key was just pressed
    /// </summary>
    public static bool isKeyJustPressed(Key key) => keys[(int)key] == PressedState.JUST_PRESSED;

    /// <summary>
    /// if true, the key is being held
    /// </summary>
    public static bool isKeyHeld(Key key) => keys[(int)key] != PressedState.INACTIVE;

    /// <summary>
    /// if true, the key was just released
    /// </summary>
    public static bool isKeyJustReleased(Key key) => keys[(int)key] == PressedState.JUST_RELEASED;

    /// <summary>
    /// if true, the mouse button isn't pressed
    /// </summary>
    public static bool isMouseButtonNotPressed(MouseButton btn) => mouse[(int)btn] == PressedState.INACTIVE;

    /// <summary>
    /// if true, the mouse button was just pressed
    /// </summary>
    public static bool isMouseButtonJustPressed(MouseButton btn) => mouse[(int)btn] == PressedState.JUST_PRESSED;

    /// <summary>
    /// if true, the mouse button is being held
    /// </summary>
    public static bool isMouseButtonHeld(MouseButton btn) => mouse[(int)btn] == PressedState.HOLDING;

    /// <summary>
    /// if true, the mouse button was just released
    /// </summary>
    public static bool isMouseButtonJustReleased(MouseButton btn) => mouse[(int)btn] == PressedState.JUST_RELEASED;

    /// <summary>
    /// if true, the keymap isn't pressed
    /// </summary>
    public static bool isKeymapNotPressed(string keymap) => Starry.settings.keymap[keymap].Any(x => keys[(int)x] == PressedState.INACTIVE);

    /// <summary>
    /// if true, the keymap was just pressed
    /// </summary>
    public static bool isKeymapJustPressed(string keymap) => Starry.settings.keymap[keymap].Any(x => keys[(int)x] == PressedState.JUST_PRESSED);

    /// <summary>
    /// if true, the keymap is being held
    /// </summary>
    public static bool isKeymapHeld(string keymap) => Starry.settings.keymap[keymap].Any(x => keys[(int)x] != PressedState.INACTIVE);

    /// <summary>
    /// if true, the keymap was just released
    /// </summary>
    public static bool isKeymapJustReleased(string keymap) => Starry.settings.keymap[keymap].Any(x => keys[(int)x] == PressedState.JUST_RELEASED);
}