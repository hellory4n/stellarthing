using System;
using System.Collections.Concurrent;
using System.Threading;
using SkiaSharp;
namespace starry;

/// <summary>
/// the renderer. this is just skia lamo
/// </summary>
public static partial class Graphics {
    internal static SKCanvas? canvas;
    internal static SKSurface? surface;
    internal static GRContext? grContext;
    internal static SKPaint? skpaint;
    internal static GRBackendRenderTarget? renderTarget;
    internal static ConcurrentQueue<Action> actions = [];
    internal static AutoResetEvent actionLoopEvent = new(false);

    /// <summary>
    /// the scale factor for the thingy
    /// </summary>
    public static int scale { get; private set; } = 0;
    /// <summary>
    /// offset because not every screen is gonna scale exactly perfectly
    /// </summary>
    public static vec2i offset { get; private set; } = (0, 0);

    public static void create()
    {
        actions.Enqueue(async () => {
            // shut up
            if (Window.glfw == null) return;

            // setup fucking skia fucking sharp
            var glInterface = GRGlInterface.CreateOpenGl(Window.glfw.GetProcAddress);
            grContext = GRContext.CreateGl(glInterface);

            vec2i winsize = await Window.getSize();
            GRGlFramebufferInfo frameBufferInfo = new(0, SKColorType.Rgba8888.ToGlSizedFormat());
            renderTarget = new((int)winsize.x, (int)winsize.y, 0, 8, frameBufferInfo);
            
            surface = SKSurface.Create(grContext, renderTarget, GRSurfaceOrigin.TopLeft,
                SKColorType.Rgba8888);
            canvas = surface.Canvas;

            // sick pain(t) stuff
            skpaint = new SKPaint() {
                Color = SKColors.White,
                IsAntialias = Starry.settings.antiAliasing
            };

            calcScale(winsize);
            Window.onResize += calcScale;
            Window.onResize += resizeTarget;

            // why is it flipped ??
            canvas?.Scale(1, -1);
            canvas?.Translate(0, -winsize.y);

            Starry.log("Skia has loaded");
        });
        actionLoopEvent.Set();
    }

    internal static void cleanup()
    {
        actions.Enqueue(() => {
            Starry.log("Annihilating Skia");
            skpaint?.Dispose();
            paint?.Dispose();
            surface?.Dispose();
            grContext?.Dispose();
            Starry.log("Skia has been annihilated");
        });
        actionLoopEvent.Set();
    }

    internal static void calcScale(vec2i size)
    {
        scale = (int)Math.Min(size.x / Starry.settings.renderSize.x, size.y /
            Starry.settings.renderSize.y);
        offset = ((size - (Starry.settings.renderSize * (vec2)(scale, scale))) *
            (0.5, 0.5)).round();
    }

    internal static void resizeTarget(vec2i size)
    {
        actions.Enqueue(() => {
            // delete the old stuff
            surface?.Dispose();
            renderTarget?.Dispose();

            // and make new shit
            GRGlFramebufferInfo frameBufferInfo = new(0, SKColorType.Rgba8888.ToGlSizedFormat());
            renderTarget = new((int)size.x, (int)size.y, 0, 8, frameBufferInfo);
            
            surface = SKSurface.Create(grContext, renderTarget, GRSurfaceOrigin.TopLeft,
                SKColorType.Rgba8888);
            canvas = surface.Canvas;

            // why is it flipped ??
            canvas?.Scale(1, -1);
            canvas?.Translate(0, -size.y);
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// ends drawing. this must be called for skia stuff to actually happen
    /// </summary>
    public static unsafe void endDrawing()
    {
        actions.Enqueue(() => {
            canvas?.Flush();
            grContext?.Flush();
            Window.glfw?.SwapBuffers(Window.window);
        });
        actionLoopEvent.Set();
    }

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
}