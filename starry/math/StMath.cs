using System;
using System.Collections.Generic;
using System.Text;
namespace starry;

/// <summary>
/// now its time for everybodys favorite subject.. MATH answer the three questions correctly and you might get something special
/// </summary>
public static class StMath
{
    static Random sorandom = new();
    static char[] base64chars = [
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
    ];

    /// <summary>
    /// degree to radian
    /// </summary>
    public static double deg2rad(double deg) => deg * (Math.PI / 180);
    
    /// <summary>
    /// radian to degree
    /// </summary>
    public static double rad2deg(double rad) => rad * (180 / Math.PI);

    /// <summary>
    /// returns a random integer greater/equal to min and less than max
    /// </summary>
    public static long randint(long min, long max) => sorandom.NextInt64(min, max);

    /// <summary>
    /// returns a random float greater/equal to min and less than max
    /// </summary>
    public static double randfloat(double min, double max) =>
        sorandom.NextDouble() * (max - min) + min;
    
    /// <summary>
    /// returns a random vec2 greater/equal to min and less than max
    /// </summary>
    public static vec2 randvec2(vec2 min, vec2 max) =>
        (sorandom.NextDouble() * (max.x - min.x) + min.x,
         sorandom.NextDouble() * (max.y - min.y) + min.y);
    
    /// <summary>
    /// lerp (time is between 0 and 1)
    /// </summary>
    public static double lerp(double start, double end, double time) =>
        start + (end - start) * Math.Clamp(time, 0, 1);
    
    /// <summary>
    /// lerp (time is between 0 and 1)
    /// </summary>
    public static vec2 lerp(vec2 start, vec2 end, double time) =>
        (start.x + (end.x - start.x) * Math.Clamp(time, 0, 1),
         start.y + (end.y - start.y) * Math.Clamp(time, 0, 1));
    
    /// <summary>
    /// lerp (time is between 0 and 1)
    /// </summary>
    public static color lerp(color start, color end, double time) =>
        ((byte)(start.r + (end.r - start.r) * Math.Clamp(time, 0, 1)),
         (byte)(start.g + (end.g - start.g) * Math.Clamp(time, 0, 1)),
         (byte)(start.b + (end.b - start.b) * Math.Clamp(time, 0, 1)),
         (byte)(start.a + (end.a - start.a) * Math.Clamp(time, 0, 1)));
    
    /// <summary>
    /// generates a random base64 string using the provided size (-_ instead of +/)
    /// </summary>
    public static string randomBase64(uint size)
    {
        StringBuilder str = new();
        for (int i = 0; i < size; i++) {
            str.Append(base64chars[randint(0, base64chars.Length)]);
        }
        return str.ToString();
    }

    /// <summary>
    /// chooses a random element from a collection
    /// </summary>
    public static T randomChoice<T>(IList<T> collection)
    {
        return collection[(int)randint(0, collection.Count)];
    }
}