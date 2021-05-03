#version 330 core
in vec2 Coords;

out vec4 FragColor;

uniform vec3 color;

void main()
{   

    float brightness = 1 - sqrt(Coords.x * Coords.x + Coords.y * Coords.y);
    if(brightness < 0.1)
        discard;
    FragColor = vec4(color * brightness, 1);
}