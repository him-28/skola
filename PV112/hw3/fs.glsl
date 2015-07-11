varying vec3 N;
varying vec3 v;
varying vec2 t;

uniform sampler2D rocks_color_tex;
uniform sampler2D rocks_normal_tex;

void main(void)
{

   vec3 Z = normalize(gl_NormalMatrix * vec3(0.0, 0.0, texture2D(rocks_normal_tex, t).z * 2.0 - 1.0));
   vec3 n = normalize(N);

   float cos_psi = dot(Z,n);

   vec3 N2;

   if(abs(cos_psi) < 0.001){

      float sin_psi = max(sqrt(1.0 - cos_psi * cos_psi), 1.0);  

      vec3 W = vec3(Z.y * n.z - n.y * Z.z, Z.z * n.x - n.z * Z.x, Z.x * n.y - n.x * Z.y);
      vec3 ZW = vec3(Z.y * W.z - W.y * Z.z, Z.z * W.x - W.z * Z.x, Z.x * W.y - W.x * Z.y);

      mat3 rot;
      rot[0] = vec3(cos_psi, sin_psi, 0.0f);
      rot[1] = vec3(-sin_psi, cos_psi, 0.0f); 
      rot[2] = vec3(0.0f, 0.0f, 1.0f);

      mat3 A;
      A[0] = Z;
      A[1] = -ZW;
      A[2] = W;

      mat3 B;
      B[0][0] = A[0][0];
      B[0][1] = A[1][0];
      B[0][2] = A[2][0];
      B[1][0] = A[0][1];
      B[1][1] = A[1][1];
      B[1][2] = A[2][1];
      B[2][0] = A[0][2];
      B[2][1] = A[1][2];
      B[2][2] = A[2][2];

      N2 = normalize(A * rot * B * gl_NormalMatrix * (texture2D(rocks_normal_tex, t).xyz * 2.0 - 1.0));
   }
   else
   {
      N2 = sign(cos_psi) * normalize(gl_NormalMatrix * (texture2D(rocks_normal_tex, t).xyz * 2.0 - 1.0));
   }

   vec3 L = normalize(gl_LightSource[0].position.xyz - v);

   vec4 I = gl_FrontLightProduct[0].diffuse * max(dot(N2,L), 0.0);
   I = clamp(I, 0.0, 1.0);
	vec4 rockColor = texture2D(rocks_color_tex, t);

   gl_FragColor = I * rockColor;
}
