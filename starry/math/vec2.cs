using System;
using System.Diagnostics.CodeAnalysis;
namespace starry;

/// <summary>
/// the worst math classes of all time
/// </summary>
public struct vec2(double x, double y) {
    public double x { get; set; } = x;
    public double y { get; set; } = y;

    public static implicit operator vec2((double, double) m) => new(m.Item1, m.Item2);
    public static vec2 operator +(vec2 a, vec2 b) => new(a.x + b.x, a.y + b.y);
    public static vec2 operator -(vec2 a, vec2 b) => new(a.x - b.x, a.y - b.y);
    public static vec2 operator *(vec2 a, vec2 b) => new(a.x * b.x, a.y * b.y);
    public static vec2 operator /(vec2 a, vec2 b) => new(a.x / b.x, a.y / b.y);
    public static vec2 operator %(vec2 a, vec2 b) => new(a.x % b.x, a.y % b.y);
    public static bool operator >(vec2 a, vec2 b) => a.x > b.x && a.x > b.x;
    public static bool operator <(vec2 a, vec2 b) => a.x < b.x && a.x < b.x;
    public static bool operator >=(vec2 a, vec2 b) => a.x >= b.x && a.x >= b.x;
    public static bool operator <=(vec2 a, vec2 b) => a.x <= b.x && a.x <= b.x;
    public static vec2 operator -(vec2 a) => new(-a.x, -a.y);

    public static vec2 zero => new(0, 0);

    public override readonly bool Equals([NotNullWhen(true)] object? obj)
    {
        if (obj is vec2 vec) {
            return vec.x == x && vec.y == y;
        }
        return false;
    }

    public static bool operator ==(vec2 a, vec2 b) => a.Equals(b);
    public static bool operator !=(vec2 a, vec2 b) => !(a == b);

    public override readonly int GetHashCode()
    {
        HashCode hash = new();
        hash.Add(x);
        hash.Add(y);
        return hash.ToHashCode();
    }

    public readonly vec2 normalized()
    {
        vec2 r = this;
        double l = x * x + y * y;
        if (l != 0) {
            l = Math.Sqrt(l);
            r.x /= l;
            r.y /= l;
        }
        return r;
    }

    /// <summary>
    /// adds a z component, which is used for layers by the top down renderer
    /// </summary>
    public readonly vec3 as3d(double layer) => new(x, y, layer);

    // for using vec2 in switch statements :D
    public readonly void Deconstruct(out double ecks, out double why)
    {
        ecks = x;
        why = y;
    }

    /// <summary>
    /// it rounds the vector.
    /// </summary>
    public readonly vec2i round() => new((int)Math.Round(x), (int)Math.Round(y));
    /// <summary>
    /// it floors the vector.
    /// </summary>
    public readonly vec2i floor() => new((int)Math.Floor(x), (int)Math.Floor(y));

    public override readonly string ToString() => $"vec2({x:0.000}, {y:0.000})";
}