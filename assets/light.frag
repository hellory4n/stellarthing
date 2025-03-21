// i didnt write this :)
#version 330

in vec3 fragNormal;  // Normal vector
in vec2 fragTexCoord;  // Texture coordinates

uniform vec3 lightDir;  // Light direction (normalized)
uniform vec4 ambient;   // Ambient light color
uniform sampler2D texture0; // Texture map

out vec4 fragColor;

void main()
{
    vec3 norm = normalize(fragNormal);
    // Compute diffuse lighting
    float diff = max(dot(norm, -lightDir), 0.0);  // Light intensity

    // Sample the diffuse texture
    vec4 texColor = texture(texture0, fragTexCoord);

    // Final color = texture color * (ambient + diffuse)
    vec3 lighting = ambient.rgb + diff;  // Combine ambient and diffuse light
    fragColor = vec4(texColor.rgb * lighting, texColor.a);  // Apply lighting to texture color
}
