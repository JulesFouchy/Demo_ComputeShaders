#version 430

in vec2 vTexCoords;
uniform sampler2D u_TextureSlot;

void main() {
	vec2 uv = vTexCoords;
	vec4 col = texture(u_TextureSlot, uv);
	gl_FragColor.r = col.r * 0.393 + col.g * 0.769 + col.b * 0.189;
    gl_FragColor.g = col.r * 0.349 + col.g * 0.686 + col.b * 0.168;
    gl_FragColor.b = col.r * 0.272 + col.g * 0.534 + col.b * 0.131;
	gl_FragColor.a = col.a;
}