#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIG 10000
double  p[BIG][2];

// gcc -o t test.c -lm
// closest pair algorithm (c)2021 James Huddle

//sorts an array of doubles
int compd(const void *a,const void *b) {
  double x,y;
  x = *((double *) a); y = *((double *) b);
  if(a-b < 0) return -1;
  if(a-b > 0) return 1;
  return 0;
}

// sorts an array of double arrays
int compa(const void *a,const void *b) {
  double p1[2],p2[2];
  p1[0] = *((double *) a); // we only convert the x-axis value
  p2[0] = *((double *) b); // because that's all we care about
  if(p1[0] < p2[0]) return -1;
  if(p1[0] > p2[0]) return 1;
  return 0;
}

int comp(const void *a,const void *b) {
  return *((int *) a) - *((int *) b);
}

// distance formula
double distance(double dx, double dy) {
  return sqrt( (dx*dx) + (dy*dy) );
}


int main() {
  FILE *f;
//  int a[10] = {3,12,4,9,77, 29,34,88,7,62};
  double fin = 1.0;
  int i;

  f = fopen("newtk.dat","r");
/*
Thanks, stackoverflow!
  n = 0;
  while (fscanf(fp, "%f", &fval[n++]) != EOF)
    ;
*/
  i=0;
  while(fscanf(f, "%lf\n", &p[i][0]) != EOF) {
    fscanf(f, "%lf\n", &p[i++][1]);
  }
  fclose(f);


  for(i=0;i<10;i++) {
    printf("%lf, %lf\n",p[i][0],p[i][1]);
  }

  qsort(p, BIG, sizeof(double)*2, compa);
  printf("\n\n--------\n\n");

/*
  for(i=0;i<10;i++) {
    printf("%lf, %lf\n",p[i][0],p[i][1]);
  }
*/

int j, s1, s2;
double  dist, dx, dy, shortest = 100000000; // (any super big num)
for(i=0;i<BIG-1;i++) {
  for(j=i+1;j<BIG;j++) {
    dx = p[i][0]-p[j][0];
    if(dx < 0) dx = dx * -1;
    if(dx > shortest) { break; } // timesaver!
    dy = p[i][1]-p[j][1];
    if(dy < 0) dy = dy * -1;
    if(dy < shortest) {
      dist = distance(dx,dy);
      if(dist < shortest) {
        s1 = i;
        s2 = j;
        shortest = dist;
printf("%i, %i, [%lf,%lf]..[%lf,%lf] -- %lf\n",i,j,p[s1][0],p[s1][1],p[s2][0],p[s2][1],shortest);
      }
    }
  }
}
printf("%i, %i\n",i,j);
printf("shortest distance is %lf\n",shortest);

  return 0;
}

/*
  qsort(a, 10, sizeof(int), comp);
for(i=0;i<10;i++) { printf("%i  ",a[i]); }
printf("\n");
*/
