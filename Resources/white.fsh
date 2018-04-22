varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
     vec4 c = texture2D(CC_Texture0, v_texCoord);
     gl_FragColor.xyz = vec3(c.r + c.g + c.b);
     gl_FragColor.w = c.w;
}