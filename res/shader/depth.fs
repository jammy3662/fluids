#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in mat4 projection;

out vec4 finalColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

void main()
{
	float z_sampled = texture2D(texture0, fragTexCoord).r;
	float z_ndc = 2 * z_sampled - 1;
	float M44 = projection[3][3];
	float M43 = projection[3][2];
	float M34 = projection[2][3];
	float M33 = projection[2][2];
	float z_view = (z_ndc * M44 - M43) / (z_ndc * M34 - M33);
	
	finalColor = vec4(z_view);
}