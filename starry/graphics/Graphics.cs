using System;
using System.Collections.Concurrent;
using System.IO;
using System.Numerics;
using System.Runtime.InteropServices;
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
    static bool renderaabb = false;
    static float shadowBias = 0.22f;
    static bool shadowPcfEnabled = true;
    static float shadowNear = 1;
    static float shadowFar = 10;
    public const uint SHADOW_WIDTH = 1024 * 4;
    public const uint SHADOW_HEIGHT = 1024 * 4;
    internal static ConcurrentQueue<Object3D> renderobjs = [];
    internal static ConcurrentQueue<Light> lights = [];
    internal static Camera currentCamera = new();
    internal static Skybox? sky;

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
        await recompileShaders();
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

    public static async Task recompileShaders()
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

    /// <summary>
    /// it draws the object of 3d variety
    /// </summary>
    public static void drawObject3D(Object3D obj)
    {
        renderobjs.Enqueue(obj);
    }

    /// <summary>
    /// it adds the aabb and returns an updated aabb
    /// </summary>
    static aabb addAabb(Object3D obj) {
        if (gl == null) return obj.box;

        aabb aabb = obj.box;

        // funni
        float[] vertices = [
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
        ];

        gl.GenVertexArrays(1, out uint ihateyou);
        aabb.vao = ihateyou;
        gl.GenBuffers(1, out uint everyonecanfindloveexceptyouopenparenthesissongcloseparenthesis);
        aabb.vbo = everyonecanfindloveexceptyouopenparenthesissongcloseparenthesis;
        gl.GenBuffers(1, out uint yourelikeaconstantstateofpsychosis);
        aabb.ebo = yourelikeaconstantstateofpsychosis;

        gl.BindVertexArray(aabb.vao);

        gl.BindBuffer(BufferTargetARB.ArrayBuffer, aabb.vbo);
        gl.BufferData<float>(BufferTargetARB.ArrayBuffer, vertices, BufferUsageARB.StaticDraw);

        ushort[] elements = [
            0, 1, 2, 3,
            4, 5, 6, 7,
            0, 4, 1, 5, 2, 6, 3, 7,
        ];
        gl.BindBuffer(BufferTargetARB.ArrayBuffer, aabb.ebo);
        gl.BufferData<ushort>(BufferTargetARB.ArrayBuffer, elements, BufferUsageARB.StaticDraw);

        gl.VertexAttribPointer(0, 3, GLEnum.Float, false, 0, 0);
        gl.EnableVertexAttribArray(0);

        return aabb;
    }

    public static unsafe void initObject(Object3D obj)
    {
        if (gl == null) return;

        foreach (Mesh mesh in obj.meshes) {
            gl.GenVertexArrays(1, out uint vaodeeznuts);
            mesh.vao = vaodeeznuts;
            gl.GenBuffers(1, out uint vbodeeznuts);
            mesh.vbo = vbodeeznuts;
            gl.GenBuffers(1, out uint ebodeeznuts);
            mesh.ebo = ebodeeznuts;

            gl.BindVertexArray(mesh.vao);

            gl.BindBuffer(BufferTargetARB.ArrayBuffer, mesh.vbo);
            // SHUT UP MARGE SHUT UP
            #pragma warning disable CS8500
            fixed (void* help = mesh.vertices) {
                gl.BufferData(BufferTargetARB.ArrayBuffer, (nuint)(mesh.vertices.Length * sizeof(Vertex)), help, BufferUsageARB.StaticDraw);
            }
            #pragma warning restore CS8500

            // akson dendryt
            gl.BindBuffer(BufferTargetARB.ArrayBuffer, mesh.ebo);
            gl.BufferData<uint>(BufferTargetARB.ArrayBuffer, mesh.indices, BufferUsageARB.StaticDraw);

            // position attribute
            gl.VertexAttribPointer(0, 3, GLEnum.Float, false, 11 * sizeof(float), null);
            gl.EnableVertexAttribArray(0);

            // texture coord attribute
            gl.VertexAttribPointer(1, 2, GLEnum.Float, false, 11 * sizeof(float), (void*)(3 * sizeof(float)));
            gl.EnableVertexAttribArray(1);

            // normals attribute
            gl.VertexAttribPointer(2, 3, GLEnum.Float, false, 11 * sizeof(float), (void*)(5 * sizeof(float)));
            gl.EnableVertexAttribArray(2);

            // tangents attribute
            gl.VertexAttribPointer(3, 3, GLEnum.Float, false, 11 * sizeof(float), (void*)(8 * sizeof(float)));
            gl.EnableVertexAttribArray(3);

            // texutre
            // Assets forces loading to be async, that doesnt work in unsafe functions
            Texture texture = new();
            Texture normalMap = new();
            Texture specularMap = new();
            texture.load(Path.Combine(Starry.settings.assetPath, mesh.material.texturePath));
            normalMap.load(Path.Combine(Starry.settings.assetPath, mesh.material.normalMapPath));
            specularMap.load(Path.Combine(Starry.settings.assetPath, mesh.material.specularMapPath));
            mesh.textureId = texture.globj;
            mesh.normalMapId = normalMap.globj;
            mesh.specularMapId = specularMap.globj;

            addAabb(obj);
        }
    }

    public static void freeObject(Object3D obj)
    {
        if (gl == null) return;

        foreach (Mesh mesh in obj.meshes) {
            gl.DeleteVertexArray(mesh.vao);
            gl.DeleteBuffer(mesh.vbo);
            gl.DeleteBuffer(mesh.ebo);
        }
    }

    unsafe static void renderAabb(Object3D obj)
    {
        if (gl == null) return;

        aabb aabb = obj.box;
        Matrix4x4 m = Matrix4x4.Identity;

        Vector3 size = new(
            (float)(aabb.maxx - aabb.minx),
            (float)(aabb.maxy - aabb.miny),
            (float)(aabb.maxz - aabb.minz)
        );
        m *= Matrix4x4.CreateScale(size);

        Vector3 center = new(
            (float)((aabb.minx + aabb.maxx) / 2),
            (float)((aabb.miny + aabb.maxy) / 2),
            (float)((aabb.minz + aabb.maxz) / 2)
        );

        Vector3 pos = new(
            (float)((obj.position.x * obj.scale.x + center.X) / size.X),
            (float)((obj.position.y * obj.scale.y + center.Y) / size.Y),
            (float)((obj.position.z * obj.scale.z + center.Z) / size.Z)
        );
        m *= Matrix4x4.CreateTranslation(pos);

        var aks = MemoryMarshal.CreateSpan(ref m.M11, 16).ToArray();
        gl.UniformMatrix4(gl.GetUniformLocation(mainShader?.obj ?? 0, "M"), 1, false, aks);

        gl.BindVertexArray(aabb.vao);
        gl.DrawElements(GLEnum.LineLoop, 4, DrawElementsType.UnsignedShort, (void*)0);
        gl.DrawElements(GLEnum.LineLoop, 4, DrawElementsType.UnsignedShort, (void*)(4 * sizeof(ushort)));
        gl.DrawElements(GLEnum.Lines, 8, DrawElementsType.UnsignedShort, (void*)(8 * sizeof(ushort)));

        gl.BindBuffer(BufferTargetARB.ArrayBuffer, 0);
    }

    /// <summary>
    /// help
    /// </summary>
    public static unsafe void renderObjects(Object3D[] objs, uint shader)
    {
        if (gl == null) return;

        foreach (Object3D o in objs) {
            Matrix4x4 m = Matrix4x4.Identity;
            
            // la escala
            m *= Matrix4x4.CreateScale((float)o.scale.x, (float)o.scale.y, (float)o.scale.z);

            // la tradución
            m *= Matrix4x4.CreateTranslation((float)o.position.x, (float)o.position.y, (float)o.position.z);

            // la rotación
            Matrix4x4 matrot = Matrix4x4.CreateFromQuaternion(o.rotationQuat);
            Matrix4x4 t1 = Matrix4x4.CreateTranslation((float)o.origin.x, (float)o.origin.y, (float)o.origin.z);
            m *= t1;
            m *= matrot;
            Matrix4x4 t2 = Matrix4x4.CreateTranslation(-(float)o.origin.x, -(float)o.origin.y, -(float)o.origin.z);
            m *= t2;

            var aks = MemoryMarshal.CreateSpan(ref m.M11, 16).ToArray();
            gl.UniformMatrix4(gl.GetUniformLocation(shader, "M"), 1, false, aks);

            // sh
            gl.Uniform3(gl.GetUniformLocation(shader, "color_mask"), 1, new float[] { (float)o.colorMask.x, (float)o.colorMask.y, (float)o.colorMask.z });
            gl.Uniform1(gl.GetUniformLocation(shader, "glowing"), o.glowing ? 1 : 0);
            gl.Uniform3(gl.GetUniformLocation(shader, "glow_color"), 1, new float[] { o.glowColor.r / 256f, o.glowColor.g / 256f, o.glowColor.b / 256f });
            gl.Uniform1(gl.GetUniformLocation(shader, "receive_shadows"), o.receiveShadows ? 1 : 0);

            // :(
            foreach (Mesh mesh in o.meshes) {
                // psdd smyritsldj
                // pass material
                gl.Uniform3(gl.GetUniformLocation(shader, "material.diffuse"), 1, new float[] { (float)mesh.material.diffuse.x, (float)mesh.material.diffuse.y, (float)mesh.material.diffuse.z });
                gl.Uniform3(gl.GetUniformLocation(shader, "material.specular"), 1, new float[] { (float)mesh.material.specular.x, (float)mesh.material.specular.y, (float)mesh.material.specular.z });

                // tind the bexture
                if (mesh.material.texturePath.Length > 0) {
                    gl.Uniform1(gl.GetUniformLocation(shader, "texture1"), 1);
                    gl.ActiveTexture(GLEnum.Texture1);
                    gl.BindTexture(GLEnum.Texture2D, mesh.textureId);
                    gl.Uniform1(gl.GetUniformLocation(shader, "hasTexture"), 1);
                    gl.Uniform1(gl.GetUniformLocation(shader, "texture_subdivision"), mesh.material.textureSubdivision);
                }
                else {
                    gl.Uniform1(gl.GetUniformLocation(shader, "hasTexture"), 0);
                }

                // bind mormal nap
                if (mesh.material.normalMapPath.Length > 0) {
                    gl.Uniform1(gl.GetUniformLocation(shader, "normalMap"), 2);
                    gl.ActiveTexture(GLEnum.Texture2);
                    gl.BindTexture(GLEnum.Texture2D, mesh.normalMapId);
                    gl.Uniform1(gl.GetUniformLocation(shader, "hasNormalMap"), 1);
                }
                else {
                    gl.Uniform1(gl.GetUniformLocation(shader, "hasNormalMap"), 0);
                }

                // bind mecular spap
                if (mesh.material.specularMapPath.Length > 0) {
                    gl.Uniform1(gl.GetUniformLocation(shader, "specularMap"), 3);
                    gl.ActiveTexture(GLEnum.Texture3);
                    gl.BindTexture(GLEnum.Texture3, mesh.specularMapId);
                    gl.Uniform1(gl.GetUniformLocation(shader, "hasSpecularMap"), 1);
                }
                else {
                    gl.Uniform1(gl.GetUniformLocation(shader, "hasSpecularMap"), 0);
                }

                // mender the resh
                gl.BindVertexArray(mesh.vao);
                gl.DrawElements(GLEnum.Triangles, (uint)mesh.indices.Length, DrawElementsType.UnsignedInt, null);
            }

            // 
            if (renderaabb) renderAabb(o);
        }
    }

    static unsafe void debugQuad()
    {
        if (gl == null) return;
        // tehre eeneeds to be debug vao to use the debug vao
        if (debugVao == 0) {
            float[] quadVertices = [
                // positions // texture coords
                -1,  1,  0,  0,  1,
                -1, -1,  0,  0,  0,
                 1,  1,  0,  1,  1,
                 1, -1,  0,  1,  0
            ];

            gl.GenVertexArrays(1, out debugVao);
            gl.GenBuffers(1, out debugVbo);
            gl.BindVertexArray(debugVao);
            gl.BufferData<float>(BufferTargetARB.ArrayBuffer, quadVertices, BufferUsageARB.StaticDraw);
            gl.EnableVertexAttribArray(0);
            gl.VertexAttribPointer(0, 3, GLEnum.Float, false, 5 * sizeof(float), null);
            gl.EnableVertexAttribArray(1);
            gl.VertexAttribPointer(1, 2, GLEnum.Float, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        gl.BindVertexArray(debugVao);
        gl.DrawArrays(GLEnum.TriangleStrip, 0, 4);
        gl.BindVertexArray(0);       
    }

    public void endDrawing()
    {
        if (Window.glfw == null) return;
        Glfw glfw = Window.glfw;
    }
}