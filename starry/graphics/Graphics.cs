using Silk.NET.OpenGL;

namespace starry;

/// <summary>
/// 3d opengl renderer that may have been partially stolen. send help.
/// </summary>
public static class Graphics {
    internal static GL? gl;
    static uint mainShader = 0;
    static uint shadowShader = 0;
    static uint debugShader = 0;
    static uint skyboxShader = 0;
    static uint depthFbo = 0;
    static uint depthMap = 0;
    static uint debugVao = 0;
    static uint debugVbo = 0;
    static bool debugEnabled = false;
    static int renderAabb = 0;
    static float shadowBias = 0;
    static bool shadowPcfEnabled = false;
    static float shadowNear = 0;
    static float shadowFar = 0;

    public static void create()
    {
    }

    public static void cleanup()
    {
    }

    public static void recompileShader()
    {
    }
}