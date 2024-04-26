#version 330 core
in vec2 vTexCoords;
in vec3 vNormal_vs;
in vec3 vPosition_vs;

uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs; // Ne pas oublier de multiplier la direction de la lumière par la View Matrix avant envoi au shader.
uniform vec3 uLightIntensity;


out vec4 fFragColor;


vec3 blinnPhong(vec3 vNormal_vs, vec3 vPosition_vs, vec3 uLightIntensity, float uShininess, vec3 uKd, vec3 uKs){
    vec3 N = normalize(vNormal_vs);
    vec3 w0 = normalize(-vPosition_vs);

vec3 wi = vec3(0.0);
    wi = normalize(uLightDir_vs);
    vec3 Li = uLightIntensity;
    vec3 Kd = uKd;
    vec3 Ks = uKs;
    vec3 halfVector = (w0+wi)/2;
    float shininess = uShininess;
    vec3 color = Li * (Kd * max(dot(wi, N), 0.0) + Ks * pow(max(dot(halfVector, N), 0.0), shininess));
    return color;
}


void main()
{
    fFragColor = texture(uTexture, vTexCoords);
    vec4 texture = texture(uTexture, vTexCoords);

    vec3 light01 = blinnPhong(vNormal_vs, vPosition_vs, uLightIntensity, uShininess, uKd, uKs); 

    vec3 finalColor = texture.rgb * (light01);
    finalColor = clamp(finalColor, 0.0, 1.0); // Valeur entre 0 et 1

    vec3 lights = light01;
}
