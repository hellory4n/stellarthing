using System;
using System.Diagnostics.CodeAnalysis;
namespace starry;

/// <summary>
/// it's like vector3 but + 1
/// </summary>
public struct vec3(double x, double y, double z) {
    public double x { get; set; } = x;
    public double y { get; set; } = y;
    public double z { get; set; } = z;

    public static implicit operator vec3((double, double, double) m) => new(m.Item1, m.Item2, m.Item3);
    public static vec3 operator +(vec3 a, vec3 b) => new(a.x + b.x, a.y + b.y, a.z + b.z);
    public static vec3 operator -(vec3 a, vec3 b) => new(a.x - b.x, a.y - b.y, a.z - b.z);
    public static vec3 operator *(vec3 a, vec3 b) => new(a.x * b.x, a.y * b.y, a.z * b.z);
    public static vec3 operator /(vec3 a, vec3 b) => new(a.x / b.x, a.y / b.y, a.z / b.z);
    public static vec3 operator %(vec3 a, vec3 b) => new(a.x % b.x, a.y % b.y, a.z % b.z);
    public static bool operator >(vec3 a, vec3 b) => a.x > b.x && a.x > b.x && a.z > b.z;
    public static bool operator <(vec3 a, vec3 b) => a.x < b.x && a.x < b.x && a.z < b.z;
    public static bool operator >=(vec3 a, vec3 b) => a.x >= b.x && a.x >= b.x && a.z >= b.z;
    public static bool operator <=(vec3 a, vec3 b) => a.x <= b.x && a.x <= b.x && a.z <= b.z;
    
    public static vec3 zero { get => new(0, 0, 0); }

    public override readonly bool Equals([NotNullWhen(true)] object? obj)
    {
        if (obj is vec3 vec) {
            return vec.x == x && vec.y == y && vec.z == z;
        }
        return false;
    }

    public static bool operator ==(vec3 a, vec3 b) => a.Equals(b);
    public static bool operator !=(vec3 a, vec3 b) => !(a == b);

    public override readonly int GetHashCode()
    {
        HashCode hash = new();
        hash.Add(x);
        hash.Add(y);
        hash.Add(z);
        return hash.ToHashCode();
    }

    /// <summary>
    /// extracts the z axis, which is used for layers by the top down renderer
    /// </summary>
    public readonly vec2 as2d() => new(x, y);

    // for using vec3 in switch statements :D
    public readonly void Deconstruct(out double ecks, out double why, out double zeezed)
    {
        ecks = x;
        why = y;
        zeezed = z;
    }

    public override readonly string ToString() => $"vec3({x:0.000}, {y:0.000}, {z:0.000})";

    /// <summary>
    /// rounds the components :)
    /// </summary>
    public readonly vec3i round() => new((long)Math.Round(x), (long)Math.Round(y), (long)Math.Round(z));
}