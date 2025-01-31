using System.IO;
using System.Threading.Tasks;
using Silk.NET.OpenGL;

namespace starry;

/// <summary>
/// In computer graphics, a shader is a computer program that calculates the appropriate levels of light, darkness, and color during the rendering of a 3D scene—a process known as shading. Shaders have evolved to perform a variety of specialized functions in computer graphics special effects and video post-processing, as well as general-purpose computing on graphics processing units.
/// </summary>
public class Shader {
    /// <summary>
    /// type of shader :)
    /// </summary>
    public enum ShaderType {
        /// <summary>
        /// linked shader thingy
        /// </summary>
        PROGRAM,
        /// <summary>
        /// it does stuff with color and stuff :)
        /// </summary>
        FRAGMENT,
        /// <summary>
        /// it does stuff with positions and stuff :)
        /// </summary>
        VERTEX,
    }

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

    /// <summary>
    /// checks if the shader is busted, returns true if it is busted
    /// </summary>
    public unsafe bool didCompilationFail(uint obj, ShaderType type)
    {
        if (Graphics.gl == null) return true;
        GL gl = Graphics.gl;

        string shadertypestr = type switch {
            ShaderType.PROGRAM => "program",
            ShaderType.FRAGMENT => "fragment",
            ShaderType.VERTEX => "vertex",
            _ => "what",
        };

        if (type != ShaderType.PROGRAM) {
            gl.GetShader(obj, GLEnum.CompileStatus, out int success);
            if (success == 0) {
                gl.GetShaderInfoLog(obj, 1024, null, out string infolog);
                Starry.log($"Error compiling {shadertypestr} shader: {infolog}");
                return true;
            }
            else return false;
        }
        else {
            gl.GetProgram(obj, GLEnum.LinkStatus, out int success);
            if (success == 0) {
                gl.GetProgramInfoLog(obj, 1024, null, out string infolog);
                Starry.log($"Error linking {shadertypestr} shader: {infolog}");
                return true;
            }
            else return false;
        }
    }

    /// <summary>
    /// compiles the shader. returns true if it succeeded, returns false otherwise
    /// </summary>
    public bool compile()
    {
        if (Graphics.gl == null) return false;
        GL gl = Graphics.gl;

        uint svert = gl.CreateShader(GLEnum.VertexShader);
        gl.ShaderSource(svert, vertSrc);
        gl.CompileShader(svert);
        if (didCompilationFail(svert, ShaderType.VERTEX)) return false;

        uint sfrag = gl.CreateShader(GLEnum.FragmentShader);
        gl.ShaderSource(sfrag, fragSrc);
        gl.CompileShader(sfrag);
        if (didCompilationFail(sfrag, ShaderType.FRAGMENT)) return false;

        obj = gl.CreateProgram();
        gl.AttachShader(obj, svert);
        gl.AttachShader(obj, sfrag);
        gl.LinkProgram(obj);
        if (didCompilationFail(obj, ShaderType.PROGRAM)) return false;

        // we dont need those anymore :)
        gl.DeleteShader(svert);
        gl.DeleteShader(sfrag);
        return true;
    }
}