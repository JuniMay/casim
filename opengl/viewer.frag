#version 330 core

in vec3 frag_color;
in vec3 frag_pos;
in vec3 normal;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 view_pos;

out vec4 out_color;

void main() {
    float ambient_strength = 0.6;
    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * light_color;

    // float specular_strength = 0.5;

    // vec3 reflect_direction = reflect(-light_direction, norm);
    // vec3 view_direction = normalize(view_pos - frag_pos);
    // float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 1);
    // vec3 specular = specular_strength * spec * light_color;

    // vec3 res = (ambient + diffuse + specular) * frag_color;
    vec3 res = (ambient + diffuse) * frag_color;

    out_color = vec4(res, 1.0);
}
