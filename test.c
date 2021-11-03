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
  int i, count=0;

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
count++;
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
printf("%i, %i, [%lf,%lf]..[%lf,%lf] -- %lf (%i)\n",i,j,p[s1][0],p[s1][1],p[s2][0],p[s2][1],shortest,count);
      }
    }
  }
}
printf("%i, %i (%i)\n",i,j,count);
printf("shortest distance is %lf\n",shortest);

  return 0;
}

/*
output with 10,000 points.
The main thing to note is how early we encounter the smallest pair.
the smallest pair is found at test 2836.
only 12 times (typical for any sample) is the distance formula used.
The total number of tests (most of them requiring one subtraction and
one compare) is 14,771, vs the brute force 50,005,000.  Starting with
the sort O(n logn) which makes it all possible, we add O(n) for the win.

0, 1, [0.247656,9341.782756]..[0.545628,6930.373228] -- 2411.409546 (1)
0, 2, [0.247656,9341.782756]..[1.123327,7231.590225] -- 2110.192712 (2)
0, 5, [0.247656,9341.782756]..[3.038175,8969.324450] -- 372.468759 (5)
0, 26, [0.247656,9341.782756]..[28.551172,9057.993714] -- 285.196965 (26)
0, 28, [0.247656,9341.782756]..[30.387569,9354.873175] -- 32.859907 (28)
1, 13, [0.545628,6930.373228]..[11.530588,6954.763559] -- 26.749908 (41)
19, 30, [16.527827,808.993365]..[35.221217,792.128030] -- 25.177019 (436)
48, 64, [52.061541,6497.539378]..[68.837044,6503.896608] -- 17.939674 (1142)
90, 97, [99.154105,4982.430489]..[108.080213,4967.190670] -- 17.661469 (1829)
111, 112, [127.104696,3683.977214]..[127.993592,3694.102457] -- 10.164186 (2127)
165, 169, [180.318906,7356.878412]..[184.441832,7365.552335] -- 9.603929 (2753)
175, 176, [189.574662,6528.241054]..[189.592390,6528.021469] -- 0.220299 (2836)
9999, 9999 (14771)
shortest distance is 0.220299

real	0m0.033s

time for 10,000,000 points is just over 12 seconds.
*/


/*
  qsort(a, 10, sizeof(int), comp);
for(i=0;i<10;i++) { printf("%i  ",a[i]); }
printf("\n");
*/
