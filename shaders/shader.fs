#version 330


in vec2 fragTexCoord;
in vec3 vertexPos;
out vec4 finalColor;

uniform sampler2D grassTexture; 

void main() {
    vec2 uv = fragTexCoord;
    vec2 st = uv * 2. - 1.;

    vec3 pos = vertexPos;

    float n_height = clamp(pos.y / 5., 0.0, 1.0);

    vec3 white = vec3(1.);

    vec3 color = vec3(0.);

    color = vec3( .08, .12, .5 );
    
    color = mix(color, white, n_height);

    float d = 1. - length( st );

    finalColor = vec4(color, 1.);
}


