#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;

in vec2 texCoord;

in vec3 Normal;

uniform sampler2D tex0;
uniform sampler2D tex1;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;
in vec3 crntPos;
struct Material {
    vec3 diffuse; 
};
vec4 spotLight()
{
	// controls how big the area that is lit up is
	float outerCone = 0.40f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.90f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specular = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 halfwayVec = normalize(viewDirection + lightDirection);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * inten + ambient) + texture(tex1, texCoord).r * specular * inten) * lightColor;
}
void main()
{
    //Material mat; 
    //mat.diffuse = vec3(texture(tex0, texCoord));
    //vec3 finalColor = mat.diffuse * color; 
    //FragColor = vec4(finalColor, 1.0f);
	//FragColor = vec4(color, 1.0f);

	FragColor = spotLight();
	
}
