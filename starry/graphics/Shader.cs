using System.IO;
using System.Threading.Tasks;

namespace starry;

/// <summary>
/// In computer graphics, a shader is a computer program that calculates the appropriate levels of light, darkness, and color during the rendering of a 3D scene—a process known as shading. Shaders have evolved to perform a variety of specialized functions in computer graphics special effects and video post-processing, as well as general-purpose computing on graphics processing units.
/// </summary>
public class Shader {
    public string vertSrc { get; set; } = "";
    public string fragSrc { get; set; } = "";
    public uint obj { get; set; }

    /// <summary>
    /// loads a shader from shader paths
    /// </summary>
    public static async Task<Shader> load(string vertPath, string fragPath)
    {
        Shader shadema = new();
        string realvertpath = Path.Combine(Starry.settings.shaderPath, vertPath);
        string realfragpath = Path.Combine(Starry.settings.shaderPath, fragPath);
        shadema.vertSrc = await File.ReadAllTextAsync(realvertpath);
        shadema.fragSrc = await File.ReadAllTextAsync(realfragpath);
        return shadema;
    }
}