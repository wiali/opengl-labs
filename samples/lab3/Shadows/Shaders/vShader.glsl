uniform mediump mat4 MVP;
uniform mediump mat4 M;

attribute highp vec3 vertexPos;
attribute highp vec2 vertexUV;
attribute highp vec3 vertexNorm;

varying lowp vec3 fragmentPos;
varying lowp vec3 fragmentNorm;
varying lowp vec2 fragmentUV;

void main()
{
    fragmentUV = vertexUV;
    fragmentNorm = (M * vec4(vertexNorm, 0)).xyz;
    fragmentPos = (M * vec4(vertexPos, 1)).xyz;
    gl_Position = MVP * vec4(vertexPos, 1);
}
