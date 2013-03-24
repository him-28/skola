#include<stdio.h>
#include<math.h>
#include<stdlib.h>

/*unit Sipsol_u;

interface*/

/*type
 vector=array [1..7000] of double;
 pvector=^vector;
*/

typedef double vector[200000];   /*defined in sipsol.h file

/*
procedure Sipsol(n,nx,maxit:integer;var
at,al,ar,ab,b,x:pvector;alpha,eps:
                  Double);
*/

long int Sipsol(long int n, long int nx, long int maxint, vector at, vector al, vector ar,
           vector ab, vector *b, vector *x, double alpha, double eps)
{

/*************************************************************************/
/*     (c)  copyright  c. r. jesshope  22-8-77
*/
/*************************************************************************/
/*
*/
/*     subroutine to solve  ax=b  iteratively by a strongly
*/
/*     implicit procedure after h. l. stone
*/
/*
*/
/*     siam j. numer. anal.,5, p. 530, 1968
*/
/*
*/
/*************************************************************************/
/*     formal parameters
*/
/*     -----------------
*/
/*
*/
/*         n - dimension of the matrix
*/
/*         nx - number of points minus 1 in x axis direction
*/
/*         maxit - maximum number of iterations
*/
/*         at,al,ar,ab are vectors containing non-zero diagonals of
*/
/*          the matrix, it is assumed that the elements of main
diagonal */
/*          are equal to one
*/
/*         at - coefficient vector from pde discretisation  (top)
*/
/*         al - coefficient vector from pde discretisation  (left)
*/
/*         ar - coefficient vector from pde discretisation  (right)
*/
/*         ab - coefficient vector from pde discretisation  (bottom)
*/
/*         x - solution vector must contain trail solution on entry
*/
/*         b - right hand side of discretised equations
*/
/*         alpha - scalar contains iteration parameter from (0,1)
*/
/*         type pvector is ^vector, vector=array [1..n] of double
*/
/*
*/
/*************************************************************************/

/*
implementation

procedure Sipsol(n,nx,maxit:integer;var
at,al,ar,ab,b,x:pvector;alpha,eps:
                  Double);
*/


/*************************************************************************/
/*     (c)  copyright  c. r. jesshope  22-8-77
*/
/*************************************************************************/
/*
*/
/*     subroutine to invert  ax=b  iteratively by a strongly
*/
/*     implicit procedure after h. l. stone
*/
/*
*/
/*     siam j. numer. anal.,5, p530, 1968
*/
/*
*/
/*************************************************************************/
/*     formal parameters
*/
/*    -----------------
*/
/*
*/
/*         n - dimension of the matrix
*/
/*         nx - number of points minus 1 in x axis direction
*/
/*         maxit - maximum number of iterations
*/
/*         at,al,ar,ab are vectors containing non-zero diagonals of
*/
/*          the matrix, it is assumed that the elements of main
diagonal */
/*          are equal to one
*/
/*         at - coefficient vector from pde discretisation  (top)
*/
/*         al - coefficient vector from pde discretisation  (left)
*/
/*         ar - coefficient vector from pde discretisation  (right)
*/
/*         ab - coefficient vector from pde discretisation  (bottom)
*/
/*         x - solution vector must contain trail solution on entry
*/
/*         b - right hand side of discretised equations
*/
/*         alpha - scalar contains iteration parameter from (0,1)
*/
/*         type pvector is ^vector, vector=array [1..n] of real
*/
/*
*/
/*************************************************************************/
/*
var
 tu1,tu2,w:pvector;
 cymult:array [1..5] of Double;
 i,icy,j,k,n1,n2,n3,n4,n5:integer;
 atu1,atu2,tl1,tl2,tld:Double;
 anorm:double;
*/


  vector tu1, tu2, w;
  double cymult[6];
  long int i, icy, j, k, n1, n2, n3, n4, n5;
  double atu1, atu2, tl1, tl2, tld;
  double anorm;

/*************************************************************************/
/*     set up a cycle of scaling factors for the iteration cycle
*/
/*************************************************************************/
/*
begin
 new(tu1);new(tu2);new(w);
 cymult[1]:=1;
 cymult[2]:=0.99;
 cymult[3]:=0.9;
 cymult[4]:=0.5;
 cymult[5]:=0;
*/

 cymult[1]=1.0;
 cymult[2]=0.99;
 cymult[3]=0.9;
 cymult[4]=0.5;
 cymult[5]=0.0;

/*************************************************************************/
/*     compute loop bounds
*/
/*************************************************************************/
/*
 n1:=nx+1;
 n2:=nx+2;
 n3:=n-n1;
 n4:=n-nx;
 n5:=n-1;
*/

 n1=nx+1;
 n2=nx+2;
 n3=n-n1;
 n4=n-nx;
 n5=n-1;

/*************************************************************************/
/*     compute residuals overwriting b^
*/
/*************************************************************************/
/*
 b^[1]:=b^[1]-x^[1]-ar^[1]*x^[2]-ab^[1]*x^[n2];
 for i:=2 to n1 do
  b^[i]:=b^[i]-x^[i]-al^[i]*x^[i-1]-ar^[i]*x^[i+1]-ab^[i]*x^[i+n1];
 for i:=n2 to n3 do
  b^[i]:=b^[i]-x^[i]-at^[i]*x^[i-n1]-al^[i]*x^[i-1]-ar^[i]*x^[i+1]-
         ab^[i]*x^[i+n1];
 for i:=n4 to n5 do
  b^[i]:=b^[i]-x^[i]-at^[i]*x^[i-n1]-al^[i]*x^[i-1]-ar^[i]*x^[i+1];
 b^[n]:=b^[n]-x^[n]-at^[n]*x^[n3]-al^[n]*x^[n5];
*/

 (*b)[1]= (*b)[1]-(*x)[1]-ar[1]*(*x)[2]-ab[1]*(*x)[n2];
 for(i=2;i<=n1;i++) (*b)[i]=(*b)[i]-(*x)[i]-al[i]*(*x)[i-1]-ar[i]*(*x)[i+1]-ab[i]*(*x)[i+n1];
 for(i=n2;i<=n3;i++) (*b)[i]=(*b)[i]-(*x)[i]-at[i]*(*x)[i-n1]-al[i]*(*x)[i-1]-ar[i]*(*x)[i+1]-ab[i]*(*x)[i+n1];
 for(i=n4;i<=n5;i++) (*b)[i]=(*b)[i]-(*x)[i]-at[i]*(*x)[i-n1]-al[i]*(*x)[i-1]-ar[i]*(*x)[i+1];
 (*b)[n]=(*b)[n]-(*x)[n]-at[n]*(*x)[n3]-al[n]*(*x)[n5];

/*************************************************************************/
/*     calculate l2 and max norm
*/
/*************************************************************************/
/*
 k:=0;
 anorm:=0;
 for i:=1 to n do
  anorm:=anorm+sqr(b^[i]);
 anorm:=sqrt(anorm);
*/

 k=0;
 anorm=0.0;
 for(i=1;i<=n;i++) anorm=anorm+(*b)[i]*(*b)[i];
 anorm=sqrt(anorm);

/*************************************************************************/
/*     set up iteration loop.  maxnum is the maximum number of
*/
/*     iteration cycles to be tried
*/
/*************************************************************************/
/*
 while (anorm>eps) and (k<maxit) do
  begin
  k:=k+1;
  for icy:=1 to 5 do
   begin
    for i:=1 to n do
     w^[i]:=alpha*cymult[icy];
*/

 while((anorm>eps)&&(k<maxint))
 {
   k=k+1;
   for(icy=1;icy<=5;icy++)
   {
     for(i=1;i<=n;i++) w[i]=alpha*cymult[icy];

/*************************************************************************/
/*     forward loop  calculates the elements of l and u, the sparse
*/
/*     factorisation of a+e    i.e.  lu=(a+e)  and then inverts l
*/
/*     giving  w^=l**-1 b^
*/
/*************************************************************************/
/*
    tu1^[1]:=ar^[1];
    tu2^[1]:=ab^[1];
    w^[1]:=b^[1];
    for i:=2 to n1 do
     begin
      atu2:=w^[i]*tu2^[i-1];
      tl1:=al^[i]/(1.0+atu2);
      tld:=1.0/(1.0+tl1*(atu2-tu1^[i-1]));
      tu1^[i]:=ar^[i]*tld;
      tu2^[i]:=(ab^[i]-tl1*atu2)*tld;
      w^[i]:=(b^[i]-tl1*w^[i-1])*tld;
     end;
    for i:=n2 to n3 do
     begin
      atu1:=w^[i]*tu1^[i-n1];
      atu2:=w^[i]*tu2^[i-1];
      tl2:=at^[i]/(1.0+atu1);
      tl1:=al^[i]/(1.0+atu2);
      tld:=1.0/(1.0+tl1*(atu2-tu1^[i-1])+tl2*(atu1-tu2^[i-n1]));
      tu1^[i]:=(ar^[i]-tl2*atu1)*tld;
      tu2^[i]:=(ab^[i]-tl1*atu2)*tld;
      w^[i]:=(b^[i]-tl1*w^[i-1]-tl2*w^[i-n1])*tld;
     end;
    for i:=n4 to n5 do
     begin
      atu1:=w^[i]*tu1^[i-n1];
      tl2:=at^[i]/(1.0+atu1);
      tld:=1.0/(1.0+tl2*(atu1-tu2^[i-n1])-al^[i]*tu1^[i-1]);
      tu1^[i]:=(ar^[i]-tl2*atu1)*tld;
      w^[i]:=(b^[i]-al^[i]*w^[i-1]-tl2*w^[i-n1])*tld;
     end;
    atu1:=w^[i]*tu1^[n3];
    tl2:=at^[n]/(1.0+atu1);
    tld:=1.0/(1.0+tl2*(atu1-tu2^[n3])-al^[n]*tu1^[n5]);
    w^[n]:=(b^[n]-al^[n]*w^[n5]-tl2*w^[n3])*tld;
*/

    tu1[1]=ar[1];
    tu2[1]=ab[1];
    w[1]=(*b)[1];
    for(i=2;i<=n1;i++)
    {
      atu2=w[i]*tu2[i-1];
      tl1=al[i]/(1.0+atu2);
      tld=1.0/(1.0+tl1*(atu2-tu1[i-1]));
      tu1[i]=ar[i]*tld;
      tu2[i]=(ab[i]-tl1*atu2)*tld;
      w[i]=((*b)[i]-tl1*w[i-1])*tld;
    }
    for(i=n2;i<=n3;i++)
    {
      atu1=w[i]*tu1[i-n1];
      atu2=w[i]*tu2[i-1];
      tl2=at[i]/(1.0+atu1);
      tl1=al[i]/(1.0+atu2);
      tld=1.0/(1.0+tl1*(atu2-tu1[i-1])+tl2*(atu1-tu2[i-n1]));
      tu1[i]=(ar[i]-tl2*atu1)*tld;
      tu2[i]=(ab[i]-tl1*atu2)*tld;
      w[i]=((*b)[i]-tl1*w[i-1]-tl2*w[i-n1])*tld;
    }
    for(i=n4;i<=n5;i++)
    {
      atu1=w[i]*tu1[i-n1];
      tl2=at[i]/(1.0+atu1);
      tld=1.0/(1.0+tl2*(atu1-tu2[i-n1])-al[i]*tu1[i-1]);
      tu1[i]=(ar[i]-tl2*atu1)*tld;
      w[i]=((*b)[i]-al[i]*w[i-1]-tl2*w[i-n1])*tld;
    }
    atu1=w[i]*tu1[n3];
    tl2=at[n]/(1.0+atu1);
    tld=1.0/(1.0+tl2*(atu1-tu2[n3])-al[n]*tu1[n5]);
    w[n]=((*b)[n]-al[n]*w[n5]-tl2*w[n3])*tld;

/*************************************************************************/
/*     now backward loop  inverts u   i.e.  w^=u**-1 w^
*/
/*************************************************************************/
/*
    for i:=2 to n1 do
     begin
      j:=n+1-i;
      w^[j]:=w^[j]-tu1^[j]*w^[j+1];
     end;
    for i:=n2 to n do
     begin
      j:=n+1-i;
      w^[j]:=w^[j]-tu1^[j]*w^[j+1]-tu2^[j]*w^[j+n1];
     end;
*/

    for(i=2;i<=n1;i++)
    {
      j=n+1-i;
      w[j]=w[j]-tu1[j]*w[j+1];
    }
    for(i=n2;i<=n;i++)
    {
      j=n+1-i;
      w[j]=w[j]-tu1[j]*w[j+1]-tu2[j]*w[j+n1];
    }

/*************************************************************************/
/*     now update residuals
*/
/*************************************************************************/
/*
    b^[1]:=b^[1]-w^[1]-ar^[1]*w^[2]-ab^[1]*w^[n2];
    for i:=2 to n1 do
     b^[i]:=b^[i]-w^[i]-al^[i]*w^[i-1]-ar^[i]*w^[i+1]-ab^[i]*w^[i+n1];
    for i:=n2 to n3 do
     b^[i]:=b^[i]-w^[i]-at^[i]*w^[i-n1]-al^[i]*w^[i-1]-ar^[i]*w^[i+1]-
            ab^[i]*w^[i+n1];
    for i:=n4 to n5 do
     b^[i]:=b^[i]-w^[i]-at^[i]*w^[i-n1]-al^[i]*w^[i-1]-ar^[i]*w^[i+1];
    b^[n]:=b^[n]-w^[n]-at^[n]*w^[n3]-al^[n]*w^[n5];
*/

    (*b)[1]=(*b)[1]-w[1]-ar[1]*w[2]-at[1]*w[n2];
    for(i=2;i<=n1;i++) (*b)[i]=(*b)[i]-w[i]-al[i]*w[i-1]-ar[i]*w[i+1]-at[i]*w[i+n1];
    for(i=n2;i<=n3;i++) (*b)[i]=(*b)[i]-w[i]-ab[i]*w[i-n1]-al[i]*w[i-1]-ar[i]*w[i+1]-at[i]*w[i+n1];
    for(i=n4;i<=n5;i++) (*b)[i]=(*b)[i]-w[i]-ab[i]*w[i-n1]-al[i]*w[i-1]-ar[i]*w[i+1];
    (*b)[n]=(*b)[n]-w[n]-ab[n]*w[n3]-al[n]*w[n5];


/*************************************************************************/
/*     now update solution
*/
/*************************************************************************/
/*
    for i:=1 to n do
     x^[i]:=x^[i]+w^[i];
*/

    for(i=1;i<=n;i++) (*x)[i]=(*x)[i]+w[i];

/*************************************************************************/
/*     end of iteration
*/
/*************************************************************************/
/*
   end;  { for icy:=1 to 5 }
*/

   }     /* for icy = to 5 */

/*************************************************************************/
/*     end of iteration cycle
*/
/*
*/
/*     calculate l2 and max norm and check for convergence
*/
/*************************************************************************/
/*
  anorm:=0;
  for i:=1 to n do
   anorm:=anorm+sqr(b^[i]);
  anorm:=sqrt(anorm);

  writeln(' residuum ',anorm);

 end;  { while }
*/

  anorm=0;
  for(i=1;i<=n;i++) anorm=anorm+(*b)[i]*(*b)[i];
  anorm=sqrt(anorm);

  fprintf(stderr," residuum %.15f\n",anorm);

 }    /* while */

/*************************************************************************/
/*     have now achieved exit on accuracy or count
*/
/*************************************************************************/
/*
end;  { Sipsol }
*/

return k;
}     /* Sipsol */

/*
end.
*/
