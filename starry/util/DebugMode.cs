using System;
using System.Diagnostics;
using System.Threading.Tasks;
namespace starry;

/// <summary>
/// debug mode :D
/// </summary>
public static class DebugMode {
    static Font font = new();
    static Sprite white = new();
    static bool showing = false;

    public static async Task create()
    {
        font = await Starry.load<Font>("font/pixel-unicode.ttf");
        white = await Starry.load<Sprite>("white.png");
    }

    public static async Task update()
    {
        await Task.Run(() => {
            if (Input.isKeyJustReleased(Key.F3)) showing = !showing;
            if (!showing) return;

            var p = Process.GetCurrentProcess();

            // i know
            Graphics.drawSprite(white, (0, 0, Starry.settings.renderSize.x, Starry.settings.renderSize.y), (0, 0), 0, (0, 0, 0, 40));

            // majestic!
            // i can't be bothered to make the lines not comically long
            Graphics.drawText($"Stellarthing {Starry.settings.gameVersion.asVersion()}", font, (0, 0), color.white);
            Graphics.drawText($"Starry {Starry.starryVersion.asVersion()}", font, (0, 16), color.white);
            Graphics.drawText($"Running {Environment.OSVersion.VersionString}", font, (0, 16 * 2), color.white);
            Graphics.drawText($"{Window.fps:0} FPS", font, (0, 16 * 4), color.white);
            Graphics.drawText($"Memory (.NET heap): {GC.GetTotalMemory(false) / 1024f / 1024f:0.0000} MB", font, (0, 16 * 5), color.white);
            Graphics.drawText($"Memory (physical): {p.WorkingSet64 / 1024f / 1024f:0.0000} MB", font, (0, 16 * 6), color.white);
            Graphics.drawText($"World \"{Tilemap.currentWorld}\", tilemap: {Tilemap.camPosition}", font, (0, 16 * 8), color.white);
            Graphics.drawText($"Layer {Tilemap.currentLayers[Tilemap.currentWorld]}, chunk {Tilemap.currentChunks[Tilemap.currentWorld]}", font, (0, 16 * 9), color.white);
        });
    }
}