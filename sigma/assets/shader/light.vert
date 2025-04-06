// stolen
#version 330

in vec3 vertexPosition;  // Vertex position
in vec3 vertexNormal;    // Vertex normal
in vec2 vertexTexCoord;  // Texture coordinates

uniform mat4 mvp;        // Model-View-Projection matrix

out vec3 fragNormal;     // Normal to pass to fragment shader

void main()
{
    // Just pass the normal as is (no transformation)
    fragNormal = normalize(vertexNormal);
    
    // Standard transformation to camera space
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}