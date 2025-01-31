namespace starry;

/// <summary>
/// camera of three dimensional variety
/// </summary>
public class Camera {
    /// <summary>
    /// front
    /// </summary>
    public vec3 front { get; set; } = (0, 0, 1);
    /// <summary>
    /// up
    /// </summary>
    public vec3 up { get; set; } = (0, 1, 0);
    /// <summary>
    /// position
    /// </summary>
    public vec3 position { get; set; } = (0, 0, 0);
    /// <summary>
    /// speed
    /// </summary>
    public double speed { get; set; } = 0;
}