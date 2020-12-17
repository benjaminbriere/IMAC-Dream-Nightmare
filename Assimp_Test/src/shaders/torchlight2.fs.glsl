#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;
//uniform sampler2D uTexture2;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;



vec3 blinnPhong(vec3 position_vs, vec3 normal_vs){

	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(uLightPos_vs - vPosition_vs);
	vec3 Vector = (w_zero + w_i);
  vec3 halfVector = vec3( float(Vector.x)/2. , float(Vector.y)/2., float(Vector.z)/2.);


	return (uLightIntensity / (uKd * uKd)) * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

void main() {

		vec3 viewDirection = -vPosition_vs;
		vec3 E = normalize(viewDirection);

    vec4 color = texture(uTexture, vTexCoords);
    //vec4 color2 = texture(uTexture2, vTexCoords);
    //fFragColor = blinnPhong(vPosition_vs, normalize(vNormal_vs));

		vec3 lightDir = -E;
    float cosTheta = clamp(dot( vec3(0.0,0.0,-1.0), lightDir),0.0,1.0);
		if(cosTheta>0.8){
			float cosTheta2 = clamp(dot( E, normalize(vNormal_vs) ),0.0,1.0);

			float dist = length(vPosition_vs)*0.01f;
			float att = cosTheta2 / (0.75f + 0.2f * dist + 10.f * dist * dist);


			//vec3 blinn = blinnPhong(vPosition_vs, normalize(vNormal_vs));
			fFragColor = vec3(att * color.x, att * color.y, att * color.z);
		}
		else{
			fFragColor = vec3(0);
		}



}
