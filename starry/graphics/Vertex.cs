using System.Runtime.InteropServices;

namespace starry;

/// <summary>
/// point
/// </summary>
[StructLayout(LayoutKind.Sequential)]
public class Vertex {
    public float x { get; set; } = 0;
    public float y { get; set; } = 0;
    public float z { get; set; } = 0;
    public float u { get; set; } = 0;
    public float v { get; set; } = 0;
    public float nx { get; set; } = 0;
    public float ny { get; set; } = 0;
    public float nz { get; set; } = 0;
    public float tx { get; set; } = 0;
    public float ty { get; set; } = 0;
    public float tz { get; set; } = 0;
}