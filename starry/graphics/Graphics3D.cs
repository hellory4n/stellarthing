using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using SkiaSharp;
namespace starry;

/// <summary>
/// the renderer. this is just skia lamo
/// </summary>
public static partial class Graphics {
    static SKPaint help = new() {
        Shader = SKShader.CreateColor(SKColors.Transparent),
        BlendMode = SKBlendMode.SrcOver,
    };
    
    /// <summary>
    /// it draws a triangle :)
    /// </summary>
    public static void drawTriangle(Triangle triangle)
    {
        SKVertices lma = triangle.asSkVerts();
        canvas?.DrawVertices(lma, SKBlendMode.SrcOver, help);
    }
}