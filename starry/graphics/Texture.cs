using System.IO;
using Silk.NET.OpenGL;
using StbImageSharp;

namespace starry;

/// <summary>
/// its a texture :D
/// </summary>
public record class Texture : IAsset {
    /// <summary>
    /// pronounced gee ell object not globge
    /// </summary>
    internal uint globj = 0;

    public void load(string path)
    {
        Window.actions.Enqueue(() => {
            if (Graphics.gl == null) return;
            GL gl = Graphics.gl;
            StbImage.stbi_set_flip_vertically_on_load(1);
            
            // actually load the stuff
            byte[] buffer = File.ReadAllBytes(path);
            ImageResult image = ImageResult.FromMemory(buffer, ColorComponents.RedGreenBlueAlpha);

            // and put it in opengl
            gl.GenTextures(1, out uint texture);
            gl.BindTexture(GLEnum.Texture2D, texture);

            // pextaramater
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureWrapS, (int)GLEnum.Repeat);
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureWrapT, (int)GLEnum.Repeat);
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureMinFilter, (int)GLEnum.Linear);
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureMagFilter, (int)GLEnum.Linear);

            // hleop
            gl.BindTexture(GLEnum.Texture2D, texture);
            gl.TexImage2D<byte>(GLEnum.Texture2D, 0, (int)GLEnum.Rgb, (uint)image.Width, (uint)image.Height, 0, GLEnum.Rgba, GLEnum.UnsignedByte, image.Data);
            gl.GenerateMipmap(GLEnum.Texture2D);

            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureWrapS, (int)GLEnum.Repeat);
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureWrapT, (int)GLEnum.Repeat);
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureMinFilter, (int)GLEnum.LinearMipmapLinear); // linear mipmap linear
            gl.TexParameter(GLEnum.Texture2D, GLEnum.TextureMagFilter, (int)GLEnum.Linear);
        });
        Window.actionLoopEvent.Set();
    }

    public void cleanup() {}
}