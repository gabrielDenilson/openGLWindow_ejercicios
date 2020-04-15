#version 330

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float miMix;

uniform sampler2D mi_textura_0;
uniform sampler2D mi_textura_1;

void main(){
	FragColor = mix(texture(mi_textura_0, TexCoord), texture(mi_textura_1, TexCoord), miMix);

}