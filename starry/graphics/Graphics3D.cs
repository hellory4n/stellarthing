using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using SkiaSharp;
namespace starry;

/// <summary>
/// the renderer. this is just skia lamo
/// </summary>
public static partial class Graphics {
    public static double fov { get; set; } = 90;
    public static double camDistance { get; set; } = 5;
    public static double near { get; set; } = 0.1;
    public static double far { get; set; } = 1000;

    static SKPaint help = new() {
        Shader = SKShader.CreateColor(SKColors.Transparent),
        BlendMode = SKBlendMode.SrcOver,
    };

    /// <summary>
    /// it draws a triangle.
    /// </summary>
    public static void drawTriangle(Triangle triangle)
    {
        SKVertices lma = triangle.asSkVerts();
        canvas?.DrawVertices(lma, SKBlendMode.SrcOver, help);
    }

    public static void drawMesh(Mesh mesh, vec3 position)
    {
        foreach (Triangle t in mesh.triangles) {
            SKPoint[] points = [
                perspective(t.v1.pos + position),
                perspective(t.v2.pos + position),
                perspective(t.v3.pos + position),
            ];

            SKColor[] colors = [
                new SKColor(t.v1.col.r, t.v1.col.g, t.v1.col.b, t.v1.col.a),
                new SKColor(t.v2.col.r, t.v2.col.g, t.v2.col.b, t.v2.col.a),
                new SKColor(t.v3.col.r, t.v3.col.g, t.v3.col.b, t.v3.col.a),
            ];

            SKVertices verts = SKVertices.CreateCopy(SKVertexMode.Triangles, points, colors);
            canvas?.DrawVertices(verts, SKBlendMode.SrcOver, help);
        }
    }

    /// <summary>
    /// projects shit in a perspective camera :)
    /// </summary>
    internal static SKPoint perspective(vec3 from)
    {
        double fovrad = fov * Math.PI / 180;
        double tanfov = Math.Tan(fovrad / 2);
        double zedzee = from.z + camDistance;
        double xproj = from.x / (tanfov * zedzee) * camDistance * Starry.settings.renderSize.x;
        double yproj = from.y / (tanfov * zedzee) * camDistance * Starry.settings.renderSize.y;

        Starry.log("help", (float)(xproj + Starry.settings.renderSize.x / 2.0), (float)(-yproj + Starry.settings.renderSize.y / 2.0));

        return new SKPoint(
            (float)(xproj + Starry.settings.renderSize.x / 2.0
            ),
            (float)(-yproj + Starry.settings.renderSize.y / 2.0)
        );
    }
}