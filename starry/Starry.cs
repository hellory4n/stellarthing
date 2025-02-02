﻿using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
namespace starry;

public static class Starry {
    /// <summary>
    /// starry settings
    /// </summary>
    public static StarrySettings settings { get; set; }
    /// <summary>
    /// the engine version (semantic versioning)
    /// </summary>
    public static vec3i starryVersion => (2, 1, 0);

    /// <summary>
    /// sets up the engine
    /// </summary>
    public static async Task create(StarrySettings settings)
    {
        // funni
        settings.shaderPath = Path.GetFullPath("assets/engine/shaders");
        Starry.settings = settings;
        Console.WriteLine($"{settings.gameName} {settings.gameVersion.asVersion()} - Starry {starryVersion.asVersion()}");
        Console.WriteLine("Use --verbose if the game is broken.");

        // opengl thread lmao
        Thread thread = new(Window.glLoop) {
            IsBackground = true,
        };
        thread.Start();

        string title = $"{settings.gameName}";
        if (settings.showVersion) title += " " + settings.gameVersion.asVersion();
        
        // the size doesn't matter once you make it fullscreen
        Window.create(title);
        Window.setFullscreen(settings.fullscreen);
        
        // fccking kmodules
        Audio.create(); // can't multithread that
        await DebugMode.create();

        settings.startup();
        
        while (!await Window.isClosing()) {
            // it's hardcoded into my brain
            if (isDebug()) {
                if (Input.isKeyJustPressed(Key.F8)) Window.close();
            }
            
            // stuff
            await Task.Run(Timer.update);
            await DebugMode.update();
            await Task.Run(Audio.update);
            await Task.Run(Music.update);
            await Entities.update();
            Input.update();

            Graphics.endDrawing();
        }

        log("Starry is closing...");

        Window.invokeTheInfamousCloseEventBecauseCeeHashtagIsStupid();

        // fccking kmodules
        Audio.cleanupButAtTheEndBecauseItCleansUpTheBackend();
        Assets.cleanup();
        Window.cleanup();
    }

    /// <summary>
    /// Console.WriteLine but cooler (it prints more types and has caller information)
    /// </summary>
    public static void log(params object[] x)
    {
        if (!settings.verbose) return;

        StringBuilder str = new();

        // show the class and member lmao
        StackTrace stackTrace = new();
        StackFrame? frame = stackTrace.GetFrame(1);
        var method = frame?.GetMethod();
        var className = method?.DeclaringType?.Name;
        var methodName = method?.Name;
        str.Append($"[{className ?? string.Empty}.{methodName ?? string.Empty}] ");

        foreach (var item in x) {
            // we optimize common types so the game doesn't explode
            switch (item) {
                case string:
                case sbyte:
                case byte:
                case short:
                case ushort:
                case int:
                case uint:
                case long:
                case ulong:
                case float:
                case double:
                case decimal:
                case bool:
                    str.Append(item.ToString());
                    break;
                
                case vec2 wec2: str.Append($"vec2({wec2.x}, {wec2.y})"); break;
                case vec2i wec2i: str.Append($"vec2i({wec2i.x}, {wec2i.y})"); break;
                case vec3 wec3: str.Append($"vec3({wec3.x}, {wec3.y}, {wec3.z})"); break;
                case vec3i wec3i: str.Append($"vec3i({wec3i.x}, {wec3i.y}, {wec3i.z})"); break;
                case color coughlour: str.Append($"rgba({coughlour.r}, {coughlour.g}, {coughlour.b}, {coughlour.a})"); break;
                case null: str.Append("null"); break;
                default: str.Append(JsonConvert.SerializeObject(item)); break;
            }

            if (x.Length > 1) str.Append(", ");
        }
        Console.WriteLine(str);
    }

    /// <summary>
    /// if true, the game is running in debug mode
    /// </summary>
    public static bool isDebug()
    {
        #if DEBUG
        return true;
        #else
        return false;
        #endif
    }
    
    // shorthands, youre supposed to use starry statically using static starry.Starry;
    /// <summary>
    /// loads the assets and then puts it in a handsome dictionary of stuff so its blazingly fast or smth idfk
    /// </summary>
    public static async Task<T> load<T>(string path) where T: IAsset, new() =>
        await Assets.load<T>(path);
    
    /// <summary>
    /// gets the reference thingy for an entity
    /// </summary>
    public static string ent2ref(IEntity entity) => Entities.entrefs[entity.GetHashCode()];

    /// <summary>
    /// gets an entity from a reference thingy
    /// </summary>
    public static IEntity ref2ent(string entref) => Entities.entities[entref];
}