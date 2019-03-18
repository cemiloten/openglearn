#version 330 core

out vec4 frag_color;

in vec3 v_color;
in vec2 uv_coords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blending;

void main()
{
    vec4 tex1 = texture(texture1, uv_coords);
    vec4 tex2 = texture(texture2, vec2(1.0 - uv_coords.x, uv_coords.y));
    frag_color = mix(tex1, tex2, blending);
}
