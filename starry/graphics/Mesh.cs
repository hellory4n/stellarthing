namespace starry;

/// <summary>
/// uhhh uhmmm umm uhhhhh
/// </summary>
public class Mesh {
    public string name { get; set; } = "";
    public Vertex[] vertices { get; set; } = [];
    public uint[] indices { get; set; } = [];
    public uint vao { get; set; } = 0;
    public uint vbo { get; set; } = 0;
    public uint ebo { get; set; } = 0;
    public Material material { get; set; } = new();
    public uint textureId { get; set; } = 0;
    public uint normalMapId { get; set; } = 0;
    public uint specularMapId { get; set; } = 0;

    /// <summary>
    /// as the name implies it computes the tangent
    /// </summary>
    public void computeTangent()
    {
        // don't ask, i stole this
        for (int i = 0; i < indices.Length; i += 3) {
            Vertex v1 = vertices[indices[i]];
            Vertex v2 = vertices[indices[i + 1]];
            Vertex v3 = vertices[indices[i + 2]];

            vec2 uv1 = (v1.u, v1.v);
            vec2 uv2 = (v2.u, v3.v);
            vec2 uv3 = (v3.u, v3.v);

            vec3 v1pos = (v1.x, v1.y, v1.z);
            vec3 v2pos = (v2.x, v2.y, v2.z);
            vec3 v3pos = (v3.x, v3.y, v3.z);

            vec3 edge1 = v2pos - v1pos;
            vec3 edge2 = v3pos - v1pos;

            vec2 deltaUv1 = uv2 - uv1;
            vec2 deltaUv2 = uv3 - uv1;

            double f = 1.0 / (deltaUv1.x * deltaUv2.y - deltaUv2.x * deltaUv1.y);

            // the titular tangent is being computed!
            vec3 tangent = (
                f * (deltaUv2.y * edge1.x - deltaUv1.y * edge2.x),
                f * (deltaUv2.y * edge1.y - deltaUv1.y * edge2.y),
                f * (deltaUv2.y * edge1.z - deltaUv1.y * edge2.z)
            );
            tangent = tangent.normalize();

            // help me axon dendrite
            v1.tx = (float)tangent.x;
            v1.ty = (float)tangent.y;
            v1.tz = (float)tangent.z;
            v2.tx = (float)tangent.x;
            v2.ty = (float)tangent.y;
            v2.tz = (float)tangent.z;
            v3.tx = (float)tangent.x;
            v3.ty = (float)tangent.y;
            v3.tz = (float)tangent.z;

            vertices[indices[i]] = v1;
            vertices[indices[i + 1]] = v2;
            vertices[indices[i + 2]] = v3;
        }

        // el normalize
        for (uint i = 0; i < indices.Length; i++) {
            Vertex v = vertices[indices[i]];
            vec3 tnorm = (v.tx, v.ty, v.tz);
            tnorm = tnorm.normalize();
            vertices[indices[i]].tx = (float)tnorm.x;
            vertices[indices[i]].ty = (float)tnorm.y;
            vertices[indices[i]].tz = (float)tnorm.z;
        }
    }
}