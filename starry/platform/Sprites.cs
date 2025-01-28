using System;
using System.IO;
using SkiaSharp;
namespace starry;

/// <summary>
/// interface for sprites (sprite, tile sprite, animation sprite)
/// </summary>
public interface ISprite {
    /// <summary>
    /// returns the internal representation of an image
    /// </summary>
    public SKImage? getInternalImage();
    /// <summary>
    /// if true, the internal representation is valid
    /// </summary>
    public bool isInternalValid();
    /// <summary>
    /// in pixels
    /// </summary>
    public vec2i getSize();
    /// <summary>
    /// frees the internal image
    /// </summary>
    public void cleanupImage();
}

/// <summary>
/// it's an image. supported formats are png, jpeg, NOT GIF, bpm, webm, wbmb, ico, pkm, ktx, astc, dng, heif, and avif. please note this is implemented through skia so if you want more formats complain to them instead. generally a good idea to only use png though
/// </summary>
public record class Sprite: IAsset, ISprite {
    internal SKBitmap? skbmp;
    internal SKImage? skimg;
    /// <summary>
    /// it's the path.
    /// </summary>
    public string path { get; private set; } = "";

    public void load(string path)
    {
        Graphics.actions.Enqueue(() => {
            skbmp = SKBitmap.Decode(path);
            if (skbmp == null) {
                Starry.log($"Couldn't load {path} as sprite");
                return;
            }

            skimg = SKImage.FromBitmap(skbmp);

            Starry.log($"Loaded sprite at {path}");
            this.path = path;
        });
        Graphics.actionLoopEvent.Set();
    }

    public void cleanup()
    {
        Graphics.actions.Enqueue(() => {
            skbmp?.Dispose();
            skimg?.Dispose();
            Starry.log($"Deleted sprite at {path}");
        });
        Graphics.actionLoopEvent.Set();
    }

    public void cleanupImage() => cleanup();
    public bool isInternalValid() => skbmp != null && skimg != null;
    public SKImage? getInternalImage() => skimg;
    public vec2i getSize() => (skbmp?.Width ?? 0, skbmp?.Height ?? 0);
}

/// <summary>
/// it's a sprite but with multiple sides. the sprite must be a png (can't be bothered) with filenames ending with the side's letter ((l)eft, (r)ight, (t)op, (b)ottom)
/// </summary>
public record class TileSprite: ISprite {
    public ISprite left { get; set; }
    public ISprite right { get; set; }
    public ISprite top { get; set; }
    public ISprite bottom { get; set; }
    /// <summary>
    /// side.
    /// </summary>
    public TileSide side { get; set; }

    public TileSprite(ISprite left, ISprite right, ISprite top, ISprite bottom)
    {
        this.left = left;
        this.right = right;
        this.top = top;
        this.bottom = bottom;
    }

    public void cleanupImage()
    {
        left.cleanupImage();
        right.cleanupImage();
        top.cleanupImage();
        bottom.cleanupImage();
    }

    public bool isInternalValid() => left.isInternalValid() && right.isInternalValid() &&
                                     top.isInternalValid() && bottom.isInternalValid();
    public vec2i getSize() => left.getSize();
    public SKImage? getInternalImage()
    {
        return (side switch {
            TileSide.LEFT => left,
            TileSide.RIGHT => right,
            TileSide.TOP => top,
            TileSide.BOTTOM => bottom,
            _ => throw new Exception("moron"),
        }).getInternalImage();
    }
}

/// <summary>
/// it's a sprite but animated lmao
/// </summary>
public record class AnimationSprite: ISprite {
    public uint currentFrame { get; set; } = 0;
    public ISprite[] frames { get; set; } = [];
    public double frameDuration { get => timer.duration; set => timer.duration = value; }
    public bool playing { get => timer.playing; }
    Timer timer;

    /// <summary>
    /// frame duration is in seconds
    /// </summary>
    public AnimationSprite(double frameDuration, params ISprite[] frames)
    {
        this.frames = frames;
        timer = new(frameDuration, true);
        timer.timeout += () => {
            currentFrame++;
            if (currentFrame == this.frames.Length) currentFrame = 0;
        };
    }

    /// <summary>
    /// starts the animation.
    /// </summary>
    public void start() => timer.start();
    public void stop() => timer.stop();

    public void cleanupImage()
    {
        foreach (ISprite sprite in frames) {
            sprite.cleanupImage();
        }
    }

    public bool isInternalValid()
    {
        int invalids = 0;
        foreach (ISprite sprite in frames) {
            if (!sprite.isInternalValid()) invalids++;
        }
        return invalids == 0;
    }

    public vec2i getSize() => frames[currentFrame].getSize();
    public SKImage? getInternalImage() => frames[currentFrame].getInternalImage();
}