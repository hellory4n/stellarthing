using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using SkiaSharp;
namespace starry;

/// <summary>
/// the renderer. this is just skia lamo
/// </summary>
public static partial class Graphics {
    static readonly SKPaint paint = new() {
        IsAntialias = Starry.settings.antiAliasing,
    };
    static Dictionary<string, List<string>> wrappedstrs = new();

    /// <summary>
    /// clears screen. useful for when you don't want your game to look like you're on drugs
    /// </summary>
    public static void clear(color color)
    {
        actions.Enqueue(() => {
            canvas?.Clear(new SKColor(color.r, color.g, color.b, color.a));
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// draws a sprite. rects are in game render coordinates (no camera) and rotation is in degrees. src and dst are so you can draw a portion of the sprite. origin is from 0 to 1, with (0, 0) being the top left and (0.5, 0.5) being the center
    /// </summary>
    public static void drawSprite(ISprite sprite, rect2 rect, vec2 origin, double rotation, color tint)
    {
        actions.Enqueue(() => {
            if (skpaint == null) return;
            if (!sprite.isInternalValid()) {
                Starry.log($"Sprite is invalid; cannot draw");
                return;
            }
        
            canvas?.Save();
        
            // rotation
            vec2 actualOrigin = ((rect.w * origin.y + rect.x) * scale + offset.x,
                                 (rect.h * origin.x + rect.y) * scale + offset.y);
        
            canvas?.Translate((float)actualOrigin.x, (float)actualOrigin.y);
            canvas?.RotateDegrees((float)rotation);
            canvas?.Translate(-(float)actualOrigin.x, -(float)actualOrigin.y);
            
            // uitjekiopjteap4t6nmoaetgmai5ti3atneiatjgnmeikzvfgamgtjeatlhneaztijhgnkejzgnmekzgmjkxp;tgjmdzjjgkzl;fadlghnmdzlajdanmktglnadlthnakldthnoklahfnkal
            var colorfilter = SKColorFilter.CreateBlendMode(
                new SKColor(tint.r, tint.g, tint.b, tint.a), SKBlendMode.Modulate);
            paint.ColorFilter = colorfilter;
        
            // draw.
            canvas?.DrawImage(sprite.getInternalImage(),
                SKRect.Create((float)(rect.x * scale) + offset.x,
                (float)(rect.y * scale) + offset.y, (float)(rect.w * scale),
                (float)(rect.h * scale)), paint);
        
            // reset the canvas for other shits
            canvas?.Restore();

            // you fucking idiot
            colorfilter.Dispose();
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// draws text :D
    /// </summary>
    public static void drawText(string text, Font font, vec2 pos, color color)
    {
        actions.Enqueue(() => {
            if (skpaint == null) return; // shut
            skpaint.Color = new SKColor(color.r, color.g, color.b, color.a);

            // shut up
            #pragma warning disable CS0618 // Type or member is obsolete
            skpaint.TextSize = 16 * scale;
            skpaint.Typeface = font.skfnt;

            canvas?.DrawText(text,
                (float)(pos.x * scale) + offset.x,
                // it renders from the bottom left
                (float)(pos.y * scale) + offset.y + (skpaint.FontSpacing / 2),
            skpaint);
            #pragma warning restore CS0618 // Type or member is obsolete
        });
        actionLoopEvent.Set();
    }

    /// <summary>
    /// returns how many pixels wide the text is
    /// </summary>
    public static Task<double> getTextSize(string text, Font font)
    {
        TaskCompletionSource<double> tcs = new();
        actions.Enqueue(() => {
            // shit up
            #pragma warning disable CS0618 // Type or member is obsolete
            paint.Typeface = font.skfnt;
            var jjjj = paint.MeasureText(text);
            #pragma warning restore CS0618 // Type or member is obsolete
            tcs.SetResult(jjjj);
        });
        actionLoopEvent.Set();
        return tcs.Task;
    }
}