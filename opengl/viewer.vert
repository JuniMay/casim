#version 330 core

layout (location = 0) in vec3 pos_;
layout (location = 1) in vec3 normal_;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

out vec3 frag_color;
out vec3 frag_pos;
out vec3 normal;

void main() {
    gl_Position = projection * view * model * vec4(pos_, 1.0);
    frag_color = color;
    frag_pos = vec3(model * vec4(pos_, 1.0));
    normal = mat3(transpose(inverse(model))) * normal_;
}
