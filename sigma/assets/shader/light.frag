// stolen
#version 330

in vec3 fragNormal;      // Normal vector from the vertex shader
in vec2 fragTexCoord;    // Texture coordinates passed from vertex shader

uniform vec3 lightDir;   // Light direction (normalized)
uniform vec4 ambient;    // Ambient light color
uniform sampler2D texture0; // Texture map
uniform vec4 materialColor; // Material's color (this can be the tint passed to the shader)

out vec4 fragColor;

void main()
{
    // Normalize the normal vector
    vec3 norm = normalize(fragNormal);

    // Calculate diffuse lighting based on the normal and light direction
    float diff = max(dot(norm, -lightDir), 0.0);

    // Sample the diffuse texture
    vec4 texColor = texture(texture0, fragTexCoord);

    // Combine material color with texture color (we assume that materialColor is passed in)
    vec4 finalColor = texColor * materialColor;

    // Apply lighting (ambient + diffuse)
    vec3 lighting = ambient.rgb + diff;
    fragColor = vec4(finalColor.rgb * lighting, finalColor.a);
}