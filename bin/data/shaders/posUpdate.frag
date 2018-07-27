#version 150
precision mediump float;

uniform sampler2DRect posData;
uniform sampler2DRect velData;
uniform sampler2DRect accData;
uniform vec3 attractor;
uniform bool isAttract;
uniform vec2 mouse;
uniform float strength;
uniform float time;

in vec2 vTexCoord;

out vec4 vFragColor0;
out vec4 vFragColor1;
out vec4 vFragColor2;

vec3 checkEdges(vec3 p, vec3 v) {
    if(p.x < 0.0 || p.x > 1.0) {
        v.x *= -1;
    }
    if(p.y < 0.0 || p.y > 1.0) {
        v.y *= -1;
    }
    if(p.z < 0.0 || p.z > 1.0) {
        v.z *= -1;
    }
    return v;
}

void main() {
    vec3 pos = texture(posData, vTexCoord).xyz;
    vec3 vel = texture(velData, vTexCoord).xyz;
    vec3 acc = texture(accData, vTexCoord).xyz;

//    vec2 m = mouse / vec2(1024.0, 768.0); // mouse position
    vec3 m = attractor / vec3(1024.0, 768.0, 1024.0);
    vec3 dir = m - pos; // caluculate direction
    float dist = length(m - pos) * 2.0; // distance from mouse to pos

    float limit = 0.005;
    if(dist < limit) dist = limit;

    float st = strength / (dist * dist); // attractive calc
    dir *= st;
    if(isAttract) acc += dir; // attract
    else acc -= dir * 0.1;    // repulsion
    vel += acc;
    vel *= 0.01;
    if(vel.x > 2.0) vel.x = 2.0;
    if(vel.y > 2.0) vel.y = 2.0;
    if(vel.z > 2.0) vel.z = 2.0;

    vec3 nextPos = pos + vel;
    vel = checkEdges(nextPos, vel);

    // Update the Position
    pos += vel;

    vFragColor0 = vec4(pos, 1.0);
    vFragColor1 = vec4(vel, 1.0);
    vFragColor2 = vec4(acc, 1.0);
}
