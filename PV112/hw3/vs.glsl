varying vec3 N;
varying vec3 v;
varying vec2 t;

void main(void)
{

   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);
	t = gl_MultiTexCoord0.st;

   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
