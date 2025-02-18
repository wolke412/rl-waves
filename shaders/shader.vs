#version 330
float noise(vec2 st) {
    // Grid cell
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Interpolation weights using a simple fade function
    vec2 u = f * f * (3.0 - 2.0 * f);

    // Random values at each corner of the cell
    float a = fract(sin(dot(i + vec2(0.0, 0.0), vec2(127.1, 311.7))) * 43758.5453);
    float b = fract(sin(dot(i + vec2(1.0, 0.0), vec2(127.1, 311.7))) * 43758.5453);
    float c = fract(sin(dot(i + vec2(0.0, 1.0), vec2(127.1, 311.7))) * 43758.5453);
    float d = fract(sin(dot(i + vec2(1.0, 1.0), vec2(127.1, 311.7))) * 43758.5453);

    // Bilinear interpolation
    return mix(mix(a, b, u.x), mix(c, d, u.x), u.y);
}

in vec3 vertexPosition;
in vec2 vertexTexCoord;

out vec2 fragTexCoord;
out vec3 vertexPos;

uniform mat4 mvp;
uniform float u_time;

void main() {
    vec2 p = vec2( 00., 40. );

    fragTexCoord = vertexTexCoord;

    vec3 pos = vertexPosition;

    float offsetY = 1. * noise( pos.xz  ) * 1. ;

    offsetY *= 2. * ( sin( u_time + distance( pos.xz, p ) / 4. ) + 1.) ;

    pos.y += offsetY * 1. ;

    gl_Position = mvp * vec4(pos, 1.0);

    vertexPos = pos;
}

