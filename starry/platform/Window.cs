using System;
using System.Collections.Concurrent;
using System.Threading;
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
    internal static ConcurrentQueue<Action> actions = [];
    internal static AutoResetEvent actionLoopEvent = new(false);

    /// <summary>
    /// creates the window :D
    /// </summary>
    public static unsafe void create(string title)
    {
        actions.Enqueue(() => {
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
            glfw.WindowHint(WindowHintOpenGlProfile.OpenGlProfile, OpenGlProfile.Core);
            glfw.WindowHint(WindowHintInt.Samples, 4);
            Starry.log("GLFW has been initialized");

            // make the infamous window
            window = glfw.CreateWindow(1280, 720, title, null, null);
            
            if (window == null) {
                glfw.Terminate();
                throw new Exception("Couldn't create a window");
            }
            glfw.MakeContextCurrent(window);
            Starry.log("Created window");

            // there's a lot of callbacks
            setupCallbacks();
        });
        actionLoopEvent.Set();
    }

    static unsafe void setupCallbacks()
    {
        actions.Enqueue(() => {
            if (glfw == null) return;

            glfw.SetErrorCallback((error, description) => {
                Starry.log($"OPENGL ERROR: {error}: {description}");
            });

            glfw.SetFramebufferSizeCallback(window, (win, w, h) => {
                onResize?.Invoke((w, h));
            });

            // end the suffering
            glfw.SetKeyCallback(window, (just, fucking, kill, me, now) => {
                // they're not fucking me
                Input.keyCallback(fucking, me);
            });

            // help me axon dendrite help me axon dendrite help me axon dendrite
            // HELP ME AXON DENDRITE
            glfw.SetMouseButtonCallback(window, (window, button, action, mods) => {
                Input.mouseButtonCallback((MouseButton)button, action);
            });

            glfw.SetCursorPosCallback(window, (oimate, x, y) => {
                Input.mouseCursorCallback(x, y);
            });
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// if true, the window is gonna be fullscreen
    /// </summary>
    public static void setFullscreen(bool fullscreen)
    {
        actions.Enqueue(() => {
            if (glfw == null) return;
            Window.fullscreen = fullscreen;

            if (fullscreen) {
                Silk.NET.GLFW.Monitor* monitor = glfw.GetPrimaryMonitor();
                if (monitor == null) return;
                VideoMode* mode = glfw.GetVideoMode(monitor);
                glfw.SetWindowMonitor(window, monitor, 0, 0, mode->Width, mode->Height,
                    Glfw.DontCare);
                
                screensize = (mode->Width, mode->Height);
                
                Starry.log("Window is now fullscreen");
            }
            else {
                glfw.SetWindowMonitor(window, null, 40, 40, 1280, 720, Glfw.DontCare);
                
                Starry.log("Windows is now windowed");
            }
        });
        actionLoopEvent.Set();
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
        actions.Enqueue(() => {
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
        actionLoopEvent.Set();
        return tcs.Task;
    }

    /// <summary>
    /// run at the end of the thing
    /// </summary>
    public static void cleanup()
    {
        actions.Enqueue(() => {
            if (glfw == null) return;

            Graphics.cleanup();
            glfw.DestroyWindow(window);
            glfw.Terminate();
            Starry.log("🛑 ITS JOEVER");
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// the size of the window
    /// </summary>
    public static Task<vec2i> getSize()
    {
        TaskCompletionSource<vec2i> tcs = new();
            actions.Enqueue(() => {
            if (glfw == null) {
                tcs.SetResult((0, 0));
                return;
            }

            glfw.GetFramebufferSize(window, out int width, out int height);
            tcs.SetResult((width, height));
        });
        actionLoopEvent.Set();
        return tcs.Task;
    }

    internal static void invokeTheInfamousCloseEventBecauseCeeHashtagIsStupid()
    {
        actions.Enqueue(() => {
            onClose?.Invoke(null, EventArgs.Empty);
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// closes the window :) (it's actualy gonna close on the next frame)
    /// </summary>
    public static void close() => closing = true;

    /// <summary>
    /// this manages opengl shit so it works with async/await multithreading all that crap
    /// </summary>
    internal static void glLoop()
    {
        while (true) {
            actionLoopEvent.WaitOne();
            while (actions.TryDequeue(out Action? man)) {
                man();
            }
        }
    }

    public delegate void ResizeEvent(vec2i newSize);
}