using System.Linq;
using Raylib_cs;

namespace starry;

public interface IAsset {
    public void load(string path);
    public void cleanup();
}

public record class Font: IAsset {
    internal Raylib_cs.Font rl;

    public unsafe void load(string path)
    {
        // fucking C
        int[] fucking = [
            41, 42, 43
        ];
        rl = Raylib.LoadFontEx(path, 32, fucking, 256);
    }

    public void cleanup() => Raylib.UnloadFont(rl);
}