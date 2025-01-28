using System;
using System.Collections.Generic;

namespace starry;

/// <summary>
/// defines game engine settings
/// </summary>
public struct StarrySettings() {
    /// <summary>
    /// function ran when the game starts
    /// </summary>
    public required Action startup { get; set; }
    /// <summary>
    /// game Name
    /// </summary>
    public string gameName { get; set; } = "Starry Project";
    /// <summary>
    /// man
    /// </summary>
    public vec3i gameVersion { get; set; } = (0, 0, 1);
    /// <summary>
    /// livia forced me to add this
    /// </summary>
    public bool showVersion { get; set; } = true;
    /// <summary>
    /// if true it's fullscreen
    /// </summary>
    public bool fullscreen { get; set; } = true;
    /// <summary>
    /// the resolution the game is rendered at (it gets scaled to become the actual resolution)
    /// </summary>
    public vec2i renderSize { get; set; } = (200, 100);
    /// <summary>
    /// livia forced me to add this
    /// </summary>
    public bool antiAliasing { get; set; } = true;
    /// <summary>
    /// you could probably change this so there's resource packs
    /// </summary>
    public string assetPath { get; set; } = "";
    /// <summary>
    /// if false then Starry.log() does nothing
    /// </summary>
    public bool verbose { get; set; } = false;
    /// <summary>
    /// the size of the tiles
    /// </summary>
    public vec2i tileSize { get; set; } = (0, 0);
    /// <summary>
    /// keyboard actions that can be remapped
    /// </summary>
    public Dictionary<string, Key[]> keymap { get; set; } = new();
}