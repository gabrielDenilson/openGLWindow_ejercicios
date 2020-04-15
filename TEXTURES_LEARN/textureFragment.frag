#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D mi_textura_0;
uniform sampler2D mi_textura_1; // la segunda textura de la imagen

void main()
{
    //FragColor = texture(mi_textura_0, TexCoord); //para cpu en la textura
    //FragColor = texture(ourTexture, TexCoord); // mexcla en color del vertexShader en la imagen
    FragColor = mix(texture(mi_textura_0, TexCoord), texture(mi_textura_1, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);

} 