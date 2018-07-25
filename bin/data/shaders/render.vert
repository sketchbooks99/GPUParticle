#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

in vec2 texcoord;
in vec4 color;

uniform sampler2DRect posTex;
uniform vec2 screen;

// out vec4 vPosition;
out vec4 vColor;
out vec2 vTexCoord;

void main() {
    vec4 pixPos = texture(posTex, texcoord);
    vColor = vec4(pixPos.xy, 1.0 - pixPos.y, 1.0);
    pixPos.x = pixPos.x * screen.x - screen.x / 2;
    pixPos.y = pixPos.y * screen.y - screen.y / 2;
    pixPos.z = pixPos.z * screen.x - screen.x / 2;
    
    vTexCoord = texcoord;
//    vColor = color;
    gl_Position = modelViewProjectionMatrix * pixPos;
//    gl_PointSize = 1.0f;
}
