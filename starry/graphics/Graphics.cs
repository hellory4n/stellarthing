using System;
using System.Threading.Tasks;
using Silk.NET.GLFW;
using Silk.NET.OpenGL;

namespace starry;

/// <summary>
/// 3d opengl renderer that may have been partially stolen. send help.
/// </summary>
public static class Graphics {
    internal static GL? gl;
    static Shader? mainShader;
    static Shader? shadowShader;
    static Shader? debugShader;
    static Shader? skyboxShader;
    static uint depthFbo = 0;
    static uint depthMap = 0;
    static uint debugVao = 0;
    static uint debugVbo = 0;
    static bool debugEnabled = false;
    static int renderAabb = 0;
    static float shadowBias = 0.22f;
    static bool shadowPcfEnabled = true;
    static float shadowNear = 1;
    static float shadowFar = 10;
    public const uint SHADOW_WIDTH = 1024 * 4;
    public const uint SHADOW_HEIGHT = 1024 * 4;

    public static async Task create()
    {
        // this function isn't run if glfw is null, this is just here to make c# happy
        if (Window.glfw == null) return;
        Glfw glfw = Window.glfw;

        // the worldwide phenomenom OpenGL context
        gl = GL.GetApi(glfw.GetProcAddress);

        // uh
        initDepthFbo();
        setOpenGlState();
        await recompileShader();
    }

    /// <summary>
    /// idfk
    /// </summary>
    public static void setOpenGlState()
    {
        if (gl == null) return;

        gl.Enable(GLEnum.DepthTest);
        gl.Enable(GLEnum.Multisample);
        gl.Enable(GLEnum.CullFace);
    }

    public static void cleanup() {}

    public static unsafe void initDepthFbo()
    {
        if (gl == null) return;

        // um
        gl.GenFramebuffers(1, out depthFbo);

        gl.GenTextures(1, out depthMap);
        gl.BindTexture(GLEnum.Texture2D, depthMap);
        gl.TexImage2D(GLEnum.Texture2D, 0, (int)GLEnum.DepthComponent, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GLEnum.DepthComponent, GLEnum.Float, null);
        gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureMinFilter, (int)GLEnum.Nearest);
        gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureMagFilter, (int)GLEnum.Nearest);
        gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureWrapS, (int)GLEnum.ClampToBorder);
        gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureWrapT, (int)GLEnum.ClampToBorder);
        float[] borderColor = [1, 1, 1, 1]; // thats just white
        gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureBorderColor, borderColor);

        gl.BindFramebuffer(FramebufferTarget.Framebuffer, depthFbo);
        gl.FramebufferTexture2D(FramebufferTarget.Framebuffer, FramebufferAttachment.DepthAttachment, GLEnum.Texture2D, depthMap, 0);
        gl.DrawBuffer(GLEnum.None);
        gl.ReadBuffer(GLEnum.None);
        gl.BindFramebuffer(FramebufferTarget.Framebuffer, 0);
    }

    public static async Task recompileShader()
    {
        mainShader = await Shader.load("toon.vert", "toon.frag");
        shadowShader = await Shader.load("shadow.vert", "shadow.frag");
        debugShader = await Shader.load("debug.vert", "debug.frag");
        skyboxShader = await Shader.load("skybox.vert", "skybox.frag");

        mainShader.compile();
        shadowShader.compile();
        debugShader.compile();
        skyboxShader.compile();
    }
}