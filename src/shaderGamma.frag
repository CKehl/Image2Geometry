varying vec3 normal;
varying vec4 color;
varying vec3 position;
varying vec2 texCoord;
uniform sampler2D Texture0;

uniform float gamma;
uniform float contrast;
uniform float brightness;

vec3 Gamma(vec3 value)
{
  return clamp(vec3(pow(value.r, gamma),pow(value.g, gamma),pow(value.b, gamma)),0.0,1.0);
}

vec3 ContrastBrightness(vec3 value)
{
	return clamp(vec3((value.rgb-0.5)*contrast+0.5+brightness),0.0,1.0);
}

void main()
{
    //vec4 inColor = gl_FrontColor * texture2D(Texture0, texCoord);
    vec4 inColor = color * texture2D(Texture0, texCoord);
    //vec4 inColor = color;
    gl_FragColor = vec4(ContrastBrightness(Gamma(inColor.rgb)), inColor.a);
}
