#version 150

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D tex;
in vec2 fragTexCoord;
out vec4 out_color;

void main()
{
  out_color = texture(tex, fragTexCoord);
}