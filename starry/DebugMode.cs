using System;
using static starry.Starry;
namespace starry;

/// <summary>
/// handles debug mode stuff :D
/// </summary>
public static class DebugMode {
    /*static TextComp? ltextrender;
    static TextComp? rtextrender;
    public static string text { get; set; } = "";
    static bool ondebug = false;

    internal static void create()
    {
        ltextrender = new() {
            font = load<Font>(settings.defaultFont),
            fontSize = 24,
            position = vec2i(),
            size = settings.renderSize / vec2i(2, 1),
            wordWrap = true
        };
        rtextrender = new() {
            font = load<Font>(settings.defaultFont),
            fontSize = 24,
            position = vec2i(settings.renderSize.x / 2, 0),
            size = settings.renderSize / vec2i(2, 1),
            wordWrap = false
        };
    }

    internal static void update()
    {
        if (Input.isKeyJustPressed(Key.f3)) ondebug = !ondebug;
        if (!ondebug) return;

        Platform.renderRectangle(vec2i(), settings.renderSize, color(0, 0, 0, 75));
        //ltextrender?.update(text);

        string rtext =
            $@"Stellarthing {settings.gameVersion}
            {Platform.getFps()} FPS
            Running {Environment.OSVersion.VersionString}
            Tilemap: x, y: {Camera.target}; world ""{Tilemap.world}""; layer {Tilemap.layer}
            Memory: {GC.GetTotalMemory(false) / 1_049_000} MB";
        //rtextrender?.update(text);
    }*/
}