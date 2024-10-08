using System;
using System.Collections.Generic;
using static starry.Starry;

namespace starry;

public struct StarrySettings
{
    public StarrySettings() {}

    /// <summary>
    /// ran when the game starts
    /// </summary>
    public required Action startup { get; set; }
    /// <summary>
    /// the game name, used for the window title and stuff
    /// </summary>
    public string gameName { get; set; } = "Starry Engine";
    /// <summary>
    /// the game's version. should start with a lowercase V.
    /// </summary>
    public string gameVersion { get; set; } = "v0.0.0";
    /// <summary>
    /// if true, the engine will display all logging, which is probably bad for performance since json
    /// </summary>
    public bool verbose { get; set; } = false;
    /// <summary>
    /// keyboard actions that can be remapped
    /// </summary>
    public Dictionary<string, Key[]> keymap { get; set; } = [];
    /// <summary>
    /// place where assets are loaded, usually relative to the project folder
    /// </summary>
    public string assetPath { get; set; } = "";
    /// <summary>
    /// resolution in which the game is rendered.
    /// </summary>
    public vec2i renderSize { get; set; } = vec2i(1920, 1080);
    /// <summary>
    /// how many pixels is each tile
    /// </summary>
    public vec2i tileSize { get; set; } = vec2i(1, 1);
    /// <summary>
    /// path for the default font, must be a mono sprite font (it's easier when every character is the same size)
    /// </summary>
    public string defaultFont { get; set; } = "";
    /// <summary>
    /// the size for every character in pixels, at a font size of 100. it needs to be a monospace font so every character has the same size
    /// </summary>
    public vec2i fontCharacterSize { get; set; } = vec2i();
    /// <summary>
    /// the grid for the characters in the sprite font, multiplied by <c>fontCharacterSize</c> since it's nicer that way
    /// </summary>
    public Dictionary<char, vec2i> fontCharacters { get; set; } = [];
}