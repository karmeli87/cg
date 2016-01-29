#version 150

uniform mat4  cProjectionMatrix;
uniform mat4  cModelviewMatrix;
uniform mat4 lightSpaceMatrix;

uniform vec3 origin;
in vec4 in_Position;
in vec3 vertexNormal;
in vec2 vertTexCoord;
out vec2 TexCoords;
out vec3 FragPos;
out vec4 projCoords;
out vec3 Normal;
out vec4 FragPosLightSpace;
uniform int shadowTest;

void main()
{
  mat4 move = mat4(1.0f);
  move[3].xyz=origin;
  if(shadowTest == 1){
      gl_Position = lightSpaceMatrix * cModelviewMatrix  * move  *in_Position;
      return;
  }
  TexCoords = vertTexCoord;
  gl_Position = cProjectionMatrix*cModelviewMatrix * move  *in_Position;
  projCoords = gl_Position;
  FragPosLightSpace = lightSpaceMatrix  * move  *in_Position;
  FragPos = (move* in_Position).xyz;
  Normal = vertexNormal;
}