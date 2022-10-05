/* -------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* -------------------------------------------------------- */
/* // Date     : 20/10/2013                                 */
/* // Code By  : Alvaro G. S. Barcellos                     */
/* -------------------------------------------------------- */

#define M_PI  3.14159265358979323846
#define cdr   1.414213562

int nx, ny;
double dx, dy, dz;
double di, fz;

/*
 * recebe numero de pontos (np), tres vetores de mediçoes ( p1 // p2 // p3 ) e  
 * calcula a maior inclinação absoluta compondo o vetor ( p4 ) com os resultados 
 * constantes externas:
 * di = distancia diagonal
 * dx = distancia em x
 * dy = distancia em y 
 */

int inclinat( int np, double * p1, double * p2, double * p3, double * p4) {

int  n;

double v0, max;

np--;

n = 0;

p4[n]=0.0;

while (++n < np) {
        
        max = -1;
        v0 = p2[n];

fprintf (stderr,"(%lf) ",v0);

	dz = abs(v0 - p1[n-1]) / di;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p1[n]) / dy;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p1[n+1]) / di;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p2[n-1]) / dx;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p2[n+1]) / dx;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p3[n-1]) / di;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p3[n]) / dy;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	dz = abs(v0 - p3[n+1]) / di;
fprintf (stderr,"%lf ",dz);
	if (max < dz) max = dz;

	p4[n] = max * fz;
fprintf (stderr,"[ %lf ]\n ",max);

}

p4[n] = 0.0;

return (n);
}


main (int argc, char * argv[])
{
 
 double zo, zp;

 double * pz, * pt;
 
 int i, j, k, m, n, ni, nj;

 char buff[1024];
 
 if (argc < 6) {
	 fprintf(stderr,
	" Use: inclinat nx ny dx dy fz zp < input > output\n"
	" nx ny numero de pontos em x e y\n"
	" dx dy tamanho relativo em x e y\n"
	" fz    fator relativo em z\n"
	" zp    rejeita valores menores que zp\n"
	" input  arquivo com 1 valor por linha, nx * ny valores\n"
	" output arquivo com 1 valor por linha, nx * ny valores\n"
	"        obs. os valores de bordas fixos com valor 0.0\n"
	);
		   
	return (1);
	}
 
nx = atoi(argv[1]);
ny = atoi(argv[2]);
dx = atof(argv[3]);
dy = atof(argv[4]);
fz = atof(argv[5]);
zp = atof(argv[6]);

pz = NULL;

if ((pz=(double*)(malloc(sizeof(double)*4*nx))) == NULL) {
	fprintf(stderr," no memory for 4 * nx ");
	return (1);
	}


m = 0;
ni = 0;
nj = 0;

pt = &pz[3 * nx];

di = sqrt (dx*dx+dy*dy);

{

// borders ??

	 for (k = 0; k < nx; k++) {
		 printf ("%6.4lf\n", 0.0);
		 }

while (!feof(stdin) && fgets(buff,1024,stdin)) {
	 
	 sscanf(buff,"%lf",&zo);

	 // clip values less than zp, just for sake.
	 
	 if (zo < zp) zo = zp;

	 pz[m] = zo; 
	 
	 m++;

	 if (++ni < nx) continue;

	 ni = 0;
	
	 if (++nj < 3) continue;

	 i = nj % 3;
	 j = (nj+1) % 3;
	 k = (nj+2) % 3;
	 m = i * nx;

	 fprintf (stderr,">> %d %d %d %d\n",i,j,k,m);

	 inclinat(nx, &pz[i*nx], &pz[j*nx], &pz[k*nx], pt);

	 for (k = 0; k < nx; k++) {
		 printf ("%6.4lf\n",pt[k]);
		 }
 	}
			 
// borders ??

	 for (k = 0; k < nx; k++) {
		 printf ("%6.4lf\n", 0.0);
		 }

// nj must be equal ny :)
	 
}

 return(0);
}


