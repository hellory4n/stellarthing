using System.Threading.Tasks;
using SkiaSharp;
namespace starry;

/// <summary>
/// it's an asset. can be loaded or deleted. please note assets are stored in a dictionary so they're only loaded once and only deleted at the end of the game.
/// </summary>
public interface IAsset {
    /// <summary>
    /// you're supposed to call this through Starry.load<T>()
    /// </summary>
    public void load(string path);
    /// <summary>
    /// calling this doesn't modify the asset dictionary so don't use this unless you know what you're doing
    /// </summary>
    public void cleanup();
}

/// <summary>
/// font
/// </summary>
public record class Font: IAsset {
    internal SKTypeface? skfnt;

    public void load(string path)
    {
        Graphics.actions.Enqueue(() => {
            skfnt = SKTypeface.FromFile(path);
        });
        Graphics.actionLoopEvent.Set();
    }

    public void cleanup()
    {
        Graphics.actions.Enqueue(() => {
            skfnt?.Dispose();
        });
        Graphics.actionLoopEvent.Set();
    }
}