namespace starry;

/// <summary>
/// it's hard to see in the dark
/// </summary>
public class Light {
    /// <summary>
    /// wehre isi the light
    /// </summary>
    public vec3 position { get; set; } = (0, 0, 0);
    /// <summary>
    /// what colro is the lgit
    /// </summary>
    public color color { get; set; } = color.white;
}