attribute vec4 a_position;  //内置的默认坐标
attribute vec2 a_texCoord;  //内置的默认纹理坐标
attribute vec4 a_color;     //内置的默认颜色


varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    gl_Position = CC_PMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}