#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D depth;
uniform sampler2D terrain;

// Output fragment color
out vec4 finalColor;

void main()
{
	float d = texture2D(depth, fragTexCoord).r;
	float t = texture2D(terrain, fragTexCoord).r;
	
	float dist = abs(d-t);
	
	finalColor.a = 1;
	
	//finalColor.rgb = vec3(t + 0.5);
	finalColor.rgb = vec3(dist);
}