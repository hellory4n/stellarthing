using System;
using System.Collections.Generic;
using System.Linq;
using SkiaSharp;

namespace starry;

/// <summary>
/// mesh
/// </summary>
public class Mesh(IEnumerable<Triangle> triangles) {
    /// <summary>
    /// triângulo
    /// </summary>
    public Triangle[] triangles { get; set; } = triangles.ToArray();
}

/// <summary>
/// triangle :)
/// </summary>
public class Triangle(Vert one, Vert two, Vert three) {
    public Vert v1 { get; } = one;
    public Vert v2 { get; } = two;
    public Vert v3 { get; } = three;
    SKVertices? verts;

    public SKVertices asSkVerts()
    {
        // man
        if (verts != null) return verts;

        // TODO add projections :)
        SKPoint[] points = [
            new SKPoint((float)v1.pos.x, (float)v1.pos.z),
            new SKPoint((float)v2.pos.x, (float)v2.pos.z),
            new SKPoint((float)v3.pos.x, (float)v3.pos.z),
        ];

        SKColor[] colors = [
            new SKColor(v1.col.r, v1.col.g, v1.col.b, v1.col.a),
            new SKColor(v2.col.r, v2.col.g, v2.col.b, v2.col.a),
            new SKColor(v3.col.r, v3.col.g, v3.col.b, v3.col.a),
        ];

        verts = SKVertices.CreateCopy(SKVertexMode.Triangles, points, colors);
        return verts;
    }

    public override int GetHashCode()
    {
        HashCode help = new();
        help.Add(v1.GetHashCode());
        help.Add(v2.GetHashCode());
        help.Add(v3.GetHashCode());
        return help.ToHashCode();
    }

    // i know
    ~Triangle()
    {
        verts?.Dispose();
    }
}

/// <summary>
/// point in a 3d space. also has a color bcuz why not
/// </summary>
public struct Vert(vec3 pos, color col) {
    public vec3 pos { get; set; } = pos;
    public color col { get; set; } = col;

    public override readonly int GetHashCode()
    {
        HashCode help = new();
        help.Add(pos.GetHashCode());
        help.Add(col.GetHashCode());
        return help.ToHashCode();
    }
}