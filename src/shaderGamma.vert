//
// Simple passthrough vertex shader
//
//attribute vec3 in_Position;                  // (x,y,z)
//attribute vec4 in_Colour;                    // (r,g,b,a)
//attribute vec2 in_TextureCoord;              // (u,v)
//attribute vec3 in_Normal;                  // (x,y,z)     unused in this shader.	

varying vec3 normal;
varying vec4 color;
varying vec3 position;
varying vec2 texCoord;

void main()
{
    //gl_Position = gl_ModelViewMatrix*gl_Vertex;
    position = ftransform().xyz;
    gl_Position = ftransform();
    color = vec4(1.0,1.0,1.0,1.0);
    
    //if((gl_Color.r > 0.0001) && (gl_Color.g > 0.0001) && (gl_Color.b > 0.0001))
    //{
    //	color = gl_Color;
    //}
    
    texCoord = (gl_TextureMatrix[0]*gl_MultiTexCoord0).xy;
    //texCoord = gl_MultiTexCoord0.xy;
    normal = normalize(gl_NormalMatrix*gl_Normal);
}
