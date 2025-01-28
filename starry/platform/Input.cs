using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Silk.NET.GLFW;
namespace starry;

public static class Input {
    public static vec2 mousePosition { get; internal set; }
    // you should minimize this
    internal static Dictionary<Key, KeyInfo> keyinfo { get; set; } = new() {
        { Key.SPACE, new() },
        { Key.APOSTROPHE, new() },
        { Key.COMMA, new() },
        { Key.MINUS, new() },
        { Key.PERIOD, new() },
        { Key.SLASH, new() },
        { Key.NUM_0, new() },
        { Key.NUM_1, new() },
        { Key.NUM_2, new() },
        { Key.NUM_3, new() },
        { Key.NUM_4, new() },
        { Key.NUM_5, new() },
        { Key.NUM_6, new() },
        { Key.NUM_7, new() },
        { Key.NUM_8, new() },
        { Key.NUM_9, new() },
        { Key.SEMICOLON, new() },
        { Key.EQUAL, new() },
        { Key.A, new() },
        { Key.B, new() },
        { Key.C, new() },
        { Key.D, new() },
        { Key.E, new() },
        { Key.F, new() },
        { Key.G, new() },
        { Key.H, new() },
        { Key.I, new() },
        { Key.J, new() },
        { Key.K, new() },
        { Key.L, new() },
        { Key.M, new() },
        { Key.N, new() },
        { Key.O, new() },
        { Key.P, new() },
        { Key.Q, new() },
        { Key.R, new() },
        { Key.S, new() },
        { Key.T, new() },
        { Key.U, new() },
        { Key.V, new() },
        { Key.W, new() },
        { Key.X, new() },
        { Key.Y, new() },
        { Key.Z, new() },
        { Key.LEFT_BRACKET, new() },
        { Key.BACKSLASH, new() },
        { Key.RIGHT_BRACKET, new() },
        { Key.GRAVE_ACCENT, new() },
        { Key.INTERNATIONAL_1, new() },
        { Key.INTERNATIONAL_2, new() },
        { Key.ESCAPE, new() },
        { Key.ENTER, new() },
        { Key.TAB, new() },
        { Key.BACKSPACE, new() },
        { Key.INSERT, new() },
        { Key.DELETE, new() },
        { Key.RIGHT, new() },
        { Key.LEFT, new() },
        { Key.DOWN, new() },
        { Key.UP, new() },
        { Key.PAGE_UP, new() },
        { Key.PAGE_DOWN, new() },
        { Key.HOME, new() },
        { Key.END, new() },
        { Key.CAPS_LOCK, new() },
        { Key.SCROLL_LOCK, new() },
        { Key.NUM_LOCK, new() },
        { Key.PRINT_SCREEN, new() },
        { Key.PAUSE, new() },
        { Key.F1, new() },
        { Key.F2, new() },
        { Key.F3, new() },
        { Key.F4, new() },
        { Key.F5, new() },
        { Key.F6, new() },
        { Key.F7, new() },
        { Key.F8, new() },
        { Key.F9, new() },
        { Key.F10, new() },
        { Key.F11, new() },
        { Key.F12, new() },
        { Key.F13, new() },
        { Key.F14, new() },
        { Key.F15, new() },
        { Key.F16, new() },
        { Key.F17, new() },
        { Key.F18, new() },
        { Key.F19, new() },
        { Key.F20, new() },
        { Key.F21, new() },
        { Key.F22, new() },
        { Key.F23, new() },
        { Key.F24, new() },
        { Key.F25, new() },
        { Key.KP_0, new() },
        { Key.KP_1, new() },
        { Key.KP_2, new() },
        { Key.KP_3, new() },
        { Key.KP_4, new() },
        { Key.KP_5, new() },
        { Key.KP_6, new() },
        { Key.KP_7, new() },
        { Key.KP_8, new() },
        { Key.KP_9, new() },
        { Key.KP_DECIMAL, new() },
        { Key.KP_DIVIDE, new() },
        { Key.KP_MULTIPLY, new() },
        { Key.KP_SUBTRACT, new() },
        { Key.KP_ADD, new() },
        { Key.KP_ENTER, new() },
        { Key.KP_EQUAL, new() },
        { Key.LEFT_SHIFT, new() },
        { Key.LEFT_CONTROL, new() },
        { Key.LEFT_ALT, new() },
        { Key.LEFT_SUPER, new() },
        { Key.RIGHT_SHIFT, new() },
        { Key.RIGHT_CONTROL, new() },
        { Key.RIGHT_ALT, new() },
        { Key.RIGHT_SUPER, new() },
        { Key.MENU, new() },
    };
    internal static List<Key> pressed { get; set; } = [];

    // called every frame to do some check stuff
    internal static void update(double delta)
    {
        Stack<Key> released = [];
        foreach (Key key in pressed) {
            KeyInfo kinf = keyinfo[key];
            // a key should only be in the just pressed or release for 1 frame
            if (kinf.framesPressed > 0 && kinf.state == KeypressState.JUST_PRESSED) {
                kinf.state = KeypressState.PRESSED;
            }

            if (kinf.framesPressed > 0 && kinf.state == KeypressState.RELEASED) {
                kinf.state = KeypressState.INACTIVE;
                // we can't just .Remove() in a foreach loop lmao
                released.Push(key);
            }

            kinf.framesPressed++;
        }

        // we can't just .Remove() in a foreach loop lmao
        while (released.Count > 0) {
            pressed.Remove(released.Pop());
        }
    }

    internal static void setKeyState(Key key, InputAction state)
    {
        KeypressState systate = state switch {
            InputAction.Press => KeypressState.JUST_PRESSED,
            InputAction.Release => KeypressState.RELEASED,
            InputAction.Repeat => KeypressState.PRESSED,
            _ => throw new Exception("c# shut up"),
        };
        if (systate == KeypressState.JUST_PRESSED) {
            pressed.Add(key);
        }
        var hola = keyinfo[key];
        hola.state = systate;
    }

    // epic functions for polling input stuff
    /// <summary>
    /// self explanatory
    /// </summary>
    public static bool isKeyHeld(Key key) => keyinfo[key].state != KeypressState.INACTIVE;
    /// <summary>
    /// self explanatory
    /// </summary>
    public static bool isKeyJustPressed(Key key) => keyinfo[key].state == KeypressState.JUST_PRESSED;
    /// <summary>
    /// self explanatory
    /// </summary>
    public static bool isKeyJustReleased(Key key) => keyinfo[key].state == KeypressState.RELEASED;

    /// <summary>
    /// self explanatory
    /// </summary>
    public static bool isKeymapHeld(string keymap)
    {
        foreach (var elmierda in Starry.settings.keymap[keymap]) {
            if (keyinfo[elmierda].state != KeypressState.INACTIVE) {
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// self explanatory
    /// </summary>
    public static bool isKeymapJustPressed(string keymap)
    {
        foreach (var elmierda in Starry.settings.keymap[keymap]) {
            if (keyinfo[elmierda].state == KeypressState.JUST_PRESSED) {
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// self explanatory
    /// </summary>
    public static bool isKeymapJustReleased(string keymap)
    {
        foreach (var elmierda in Starry.settings.keymap[keymap]) {
            if (keyinfo[elmierda].state == KeypressState.RELEASED) {
                return true;
            }
        }
        return false;
    }
}

internal class KeyInfo() {
    public int framesPressed { get; set; } = 0;
    public KeypressState state { get; set; } = KeypressState.INACTIVE;
}

internal enum KeypressState
{
    PRESSED,
    RELEASED,
    JUST_PRESSED,
    INACTIVE,
}