namespace starry;

/// <summary>
/// it's an aabb
/// </summary>
public struct @aabb(double minx, double maxx, double miny, double maxy, double minz, double maxz) {
    public double minx { get; set; } = minx;
    public double maxx { get; set; } = maxx;
    public double miny { get; set; } = miny;
    public double maxy { get; set; } = maxy;
    public double minz { get; set; } = minz;
    public double maxz { get; set; } = maxz;
    public uint vao { get; set; } = 0;
    public uint vbo { get; set; } = 0;
    public uint ebo { get; set; } = 0;
}