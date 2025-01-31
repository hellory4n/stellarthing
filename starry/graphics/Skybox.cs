using System;
using System.IO;
using Silk.NET.OpenGL;
using StbImageSharp;

namespace starry;

/// <summary>
/// as the name implies it's a box that looks like the sky
/// </summary>
public class Skybox {
    internal uint vao = 0;
    internal uint vbo = 0;
    internal uint textureId = 0;
    public string[] faces { get; set; } = [
        "", "", "", "", "", ""
    ];

    // i know
    public readonly float[] skyboxVertices = [
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    ];

    /// <summary>
    /// REMEMBER CUBES HAVE 6 FACES
    /// </summary>
    unsafe void loadCubemap(string[] faces)
    {
        if (Graphics.gl == null) return;
        GL gl = Graphics.gl;

        if (faces.Length > 6) throw new Exception("cubes have only 6 faces you big stupid");

        gl.GenTextures(1, out textureId);
        gl.BindTexture(GLEnum.TextureCubeMap, textureId);

        StbImage.stbi_set_flip_vertically_on_load(0);
        int i = 0;
        foreach (string face in faces) {
            byte[] buffer = File.ReadAllBytes(face);
            ImageResult image = ImageResult.FromMemory(buffer, ColorComponents.RedGreenBlueAlpha);
            gl.TexImage2D<byte>(GLEnum.TextureCubeMapPositiveX + i, 0, (int)GLEnum.Rgba, (uint)image.Width, (uint)image.Height, 0, GLEnum.Rgb, GLEnum.UnsignedByte, image.Data);

            i++;
        }

        int imtiredsotired = (int)GLEnum.Linear;
        int imtiredofhavingses = (int)GLEnum.ClampToEdge;
        gl.TexParameterI(GLEnum.TextureCubeMap, GLEnum.TextureMinFilter, ref imtiredsotired);
        gl.TexParameterI(GLEnum.TextureCubeMap, GLEnum.TextureMagFilter, ref imtiredsotired);
        gl.TexParameterI(GLEnum.TextureCubeMap, GLEnum.TextureWrapS, ref imtiredofhavingses);
        gl.TexParameterI(GLEnum.TextureCubeMap, GLEnum.TextureWrapT, ref imtiredofhavingses);
        gl.TexParameterI(GLEnum.TextureCubeMap, GLEnum.TextureWrapR, ref imtiredofhavingses);
    }

    /// <summary>
    /// REMEMBE
    /// </summary>
    /// <param name="faces"></param>
    public Skybox(string[] faces)
    {
        if (Graphics.gl == null) return;
        GL gl = Graphics.gl;

        // i love opengl
        gl.GenVertexArrays(1, out vao);
        gl.GenBuffers(1, out vbo);
        gl.BindVertexArray(vao);
        gl.BindBuffer(BufferTargetARB.ArrayBuffer, vbo);
        gl.BufferData<float>(BufferTargetARB.ArrayBuffer, skyboxVertices, BufferUsageARB.StaticDraw);
        gl.EnableVertexAttribArray(0);
        gl.VertexAttribPointer(0, 3, GLEnum.Float, false, 3 * sizeof(float), 0);

        // akson dendryt
        loadCubemap(faces);
    }

    /// <summary>
    /// cleans the up
    /// </summary>
    public void cleanup() {
        if (Graphics.gl == null) return;
        GL gl = Graphics.gl;

        gl.DeleteVertexArrays(1, ref vao);
        gl.DeleteBuffers(1, ref vbo);
    }
}