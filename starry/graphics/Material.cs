namespace starry;

/// <summary>
/// so your models aren't giant blobs of gray
/// </summary>
public class Material {
    public string name { get; set; } = "";
    public string texturePath { get; set; } = "";
    public string normalMapPath { get; set; } = "";
    public string specularMapPath { get; set; } = "";
    public vec3 diffuse { get; set; } = (1, 1, 1);
    public vec3 specular { get; set; } = (1, 1, 1);
    public int textureSubdivision { get; set; } = 1;
}