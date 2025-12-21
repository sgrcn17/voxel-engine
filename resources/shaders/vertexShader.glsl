#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aEncodedUV;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec2 DecodeUV(float encoded) {
    const float invMax = 1.0 / 65535.0;
    uint bits = floatBitsToUint(encoded);
    uint uInt = (bits >> 16) & 0xFFFFu; 
    uint vInt = bits & 0xFFFFu;
    return vec2(float(uInt) * invMax, float(vInt) * invMax);
}

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = DecodeUV(aEncodedUV);
}    