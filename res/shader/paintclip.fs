#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform sampler2D zpaint;
uniform sampler2D zterrain;

void main()
{
	float zp = texture2D(zpaint, fragTexCoord).r;
	float zt = texture2D(zterrain, fragTexCoord).r;
	float dist = zt-zp;
	
	float b = (pow(zp, 50) + pow(zt, 50)) / 2;
	
	finalColor = texture2D(texture0, fragTexCoord);
	if (zp > zt || zp > 1)
	{
		finalColor.a = 0.1;
	}
}