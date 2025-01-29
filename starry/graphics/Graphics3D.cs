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
            float[,] materix = persp((float)fov, Starry.settings.renderSize.x / Starry.settings.renderSize.y, (float)near, (float)far);
            SKPoint[] points = [
                project(t.v1.pos + position, materix, (int)Starry.settings.renderSize.x, (int)Starry.settings.renderSize.y),
                project(t.v2.pos + position, materix, (int)Starry.settings.renderSize.x, (int)Starry.settings.renderSize.y),
                project(t.v3.pos + position, materix, (int)Starry.settings.renderSize.x, (int)Starry.settings.renderSize.y),
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

    static float[,] persp(float fov, float aspect, float near, float far)
    {
        float fovRad = 1.0f / MathF.Tan(fov * 0.5f * MathF.PI / 180.0f);
        return new float[,] {
            { fovRad / aspect, 0, 0,  0 },
            { 0, fovRad, 0,  0 },
            { 0, 0, far / (far - near), -far * near / (far - near) },
            { 0, 0, 1,  0 }
        };
    }

    static SKPoint project(vec3 pint, float[,] projectionMatrix, int width, int height)
    {
        var point = new SKPoint3((float)pint.x, (float)pint.y, (float)pint.z);
        float x = point.X * projectionMatrix[0, 0] + point.Z * projectionMatrix[0, 2];
        float y = point.Y * projectionMatrix[1, 1] + point.Z * projectionMatrix[1, 2];
        float z = point.Z * projectionMatrix[2, 2] + projectionMatrix[2, 3];
        float w = point.Z * projectionMatrix[3, 2] + projectionMatrix[3, 3];

        if (w != 0) {
            x /= w;
            y /= w;
        }

        x = (x + 1) * width / 2;
        y = (1 - y) * height / 2;

        return new SKPoint(x, y);
    }
}