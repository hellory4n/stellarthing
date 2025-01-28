using System;
using System.Threading.Tasks;
using Silk.NET.GLFW;
namespace starry;

/// <summary>
/// the game window. static since i don't think games need several of those
/// </summary>
public static unsafe class Window {
    /// <summary>
    /// called when the window is resized
    /// </summary>
    public static event ResizeEvent? onResize;
    /// <summary>
    /// called right before the engine starts cleaning up
    /// </summary>
    public static event EventHandler? onClose;
    /// <summary>
    /// delta time in seconds
    /// </summary>
    public static double deltaTime { get; private set; } = 0;
    /// <summary>
    /// time since the engine started, in seconds
    /// </summary>
    public static double elapsedTime { get; private set; } = 0;
    /// <summary>
    /// the fps the game is running on
    /// </summary>
    public static double fps { get; private set; } = 0;

    internal static Glfw? glfw;
    internal static WindowHandle* window;
    internal static bool fullscreen = false;
    internal static vec2i screensize = (0, 0);
    internal static bool closing = false;

    /// <summary>
    /// creates the window :D
    /// </summary>
    public static unsafe void create(string title, vec2i size)
    {
        Graphics.actions.Enqueue(() => {
            // first we need glfw
            glfw = Glfw.GetApi();
            if (!glfw.Init()) {
                // crash because glfw is quite important
                throw new Exception("Couldn't initialize GLFW");
            }

            // hints :D
            glfw.WindowHint(WindowHintInt.ContextVersionMajor, 3);
            glfw.WindowHint(WindowHintInt.ContextVersionMinor, 3);
            glfw.WindowHint(WindowHintInt.RefreshRate, Glfw.DontCare);
            Starry.log("GLFW has been initialized");

            // make the infamous window
            window = glfw.CreateWindow((int)Starry.settings.renderSize.x,
                (int)Starry.settings.renderSize.y, title, null, null);
            
            if (window == null) {
                glfw.Terminate();
                throw new Exception("Couldn't create a window");
            }
            glfw.MakeContextCurrent(window);
            Starry.log("Created window");

            // there's a lot of callbacks
            setupCallbacks();

            // this setups up opengl
            Graphics.create();
        });
        Graphics.actionLoopEvent.Set();
    }

    static unsafe void setupCallbacks()
    {
        Graphics.actions.Enqueue(() => {
            if (glfw == null) return;

            glfw.SetErrorCallback((error, description) => {
                Starry.log($"OPENGL ERROR: {error}: {description}");
            });

            glfw.SetFramebufferSizeCallback(window, (win, w, h) => {
                onResize?.Invoke((w, h));
            });

            glfw.SetKeyCallback(window, (just, fucking, kill, me, now) => {
                // end the suffering
                Input.setKeyState((Key)fucking, me);
            });

            // help me axon dendrite help me axon dendrite help me axon dendrite
            // HELP ME AXON DENDRITE
            glfw.SetMouseButtonCallback(window, (window, button, action, mods) => {
                Input.setStouseMate((MouseButton)button, action);
            });
        });
        Graphics.actionLoopEvent.Set();
    }

    /// <summary>
    /// if true, the window is gonna be fullscreen
    /// </summary>
    public static void setFullscreen(bool fullscreen)
    {
        Graphics.actions.Enqueue(() => {
            if (glfw == null) return;
            Window.fullscreen = fullscreen;

            if (fullscreen) {
                Monitor* monitor = glfw.GetPrimaryMonitor();
                if (monitor == null) return;
                VideoMode* mode = glfw.GetVideoMode(monitor);
                glfw.SetWindowMonitor(window, monitor, 0, 0, mode->Width, mode->Height,
                    Glfw.DontCare);
                
                screensize = (mode->Width, mode->Height);
                
                Starry.log("Window is now fullscreen");
            }
            else {
                glfw.SetWindowMonitor(window, null, 40, 40, (int)Starry.settings.renderSize.x,
                (int)Starry.settings.renderSize.y, Glfw.DontCare);
                
                Starry.log("Windows is now windowed");
            }
        });
        Graphics.actionLoopEvent.Set();
    }

    /// <summary>
    /// if true, the window is currently fullscreen
    /// </summary>
    public static bool isFullscreen() => fullscreen;

    /// <summary>
    /// if true the window is closing. convenient for making a main loop
    /// </summary>
    public static Task<bool> isClosing()
    {
        TaskCompletionSource<bool> tcs = new();
        Graphics.actions.Enqueue(() => {
            if (glfw == null) {
                tcs.SetResult(false);
                return;
            }
            glfw.PollEvents();

            // YOU UNDERSTAND MECHANCIAL HANDS ARE THE RULER OF EVERYTHING
            double current = glfw.GetTime();
            deltaTime = current - elapsedTime;
            elapsedTime = current;
            fps = 1.0 / deltaTime;

            tcs.SetResult(glfw.WindowShouldClose(window) || closing);
        });
        Graphics.actionLoopEvent.Set();
        return tcs.Task;
    }

    /// <summary>
    /// run at the end of the thing
    /// </summary>
    public static void cleanup()
    {
        Graphics.actions.Enqueue(() => {
            if (glfw == null) return;

            Graphics.cleanup();
            glfw.DestroyWindow(window);
            glfw.Terminate();
            Starry.log("🛑 ITS JOEVER");
        });
        Graphics.actionLoopEvent.Set();
    }

    /// <summary>
    /// the size of the window
    /// </summary>
    public static Task<vec2i> getSize()
    {
        TaskCompletionSource<vec2i> tcs = new();
            Graphics.actions.Enqueue(() => {
            if (glfw == null) {
                tcs.SetResult((0, 0));
                return;
            }

            glfw.GetFramebufferSize(window, out int width, out int height);
            tcs.SetResult((width, height));
        });
        Graphics.actionLoopEvent.Set();
        return tcs.Task;
    }

    internal static void invokeTheInfamousCloseEventBecauseCeeHashtagIsStupid()
    {
        Graphics.actions.Enqueue(() => {
            onClose?.Invoke(null, EventArgs.Empty);
        });
        Graphics.actionLoopEvent.Set();
    }

    /// <summary>
    /// closes the window :) (it's actualy gonna close on the next frame)
    /// </summary>
    public static void close() => closing = true;

    public delegate void ResizeEvent(vec2i newSize);
}