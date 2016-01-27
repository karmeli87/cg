#version 150

uniform mat4  cProjectionMatrix;
uniform mat4  cModelviewMatrix;

uniform vec3 origin;
in vec4 in_Position;
in vec3 vertexNormal;
in vec2 vertTexCoord;
out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

void main()
{
  TexCoords = vertTexCoord;
  mat4 move = mat4(1.0f);
  move[3].xyz=origin;
  gl_Position = cProjectionMatrix*cModelviewMatrix  * move  *in_Position;
  FragPos = ( move  *in_Position).xyz;
  Normal = vertexNormal;
}