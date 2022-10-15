#version 400
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// uniform mat4 transform;
uniform mat4 model;     
uniform mat4 view;      
uniform mat4 projection;

void main()
{
    // gl_Position = transform * vec4(aPos, 1.0f);
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}