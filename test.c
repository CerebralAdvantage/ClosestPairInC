// gcc -o t test.c -lm
// closest pair algorithm (c)2021 James Huddle
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIG 10000
double  p[BIG][2];

// sorts an array of double arrays
int compa(const void *a,const void *b) {
  double p1[2],p2[2];
  p1[0] = *((double *) a); // we only convert the x-axis value
  p2[0] = *((double *) b); // because that's all we care about
  if(p1[0] < p2[0]) return -1;
  if(p1[0] > p2[0]) return 1;
  return 0;
}

// distance formula
double distance(double dx, double dy) {
  return sqrt( (dx*dx) + (dy*dy) );
}

int main() {
  FILE *f;
  int i, count=0;
  int j, s1, s2;
  double  dist, dx, dy, shortest = 100000000; // (any super big num)

// read point data from file
  f = fopen("newtk.dat","r");
  i=0;
  while(fscanf(f, "%lf\n", &p[i][0]) != EOF) {
    fscanf(f, "%lf\n", &p[i++][1]);
  }
  fclose(f);

// sort list by x-coordinate (that's what compa does)
  qsort(p, BIG, sizeof(double)*2, compa);

/*
   This compound loop *is* the algorithm.  It looks like a O(n^2)
   process, but the dx quick check converts it into a roughly O(n)
   process.  Imagine you're checking a list of 10,000 points.
   Now imagine you find the closest pair.  You're approx 175
   points into the outer (i) loop, and you compare that point with
   the next point (176) and the distance just happens to be the
   smallest distance.  Now, imagine going through the rest of the
   list.  EITHER dx or dy will be larger than the smallest distance.
   So you either do 1 subtract and compare (see // timesaver!) and dx
   is larger (so you're done with all the checks for that point) or you
   don't bail and you do one more subtract and compare. Logic dictates
   that you will only check ONE dy value (and bail, because it has to be
   larger than the smallest distance).  Since you have found the
   smallest distance, EITHER dx OR dy must be larger for each remaining
   point in the (i) loop.  This requires only 1 or 2 tests, hence the
   remaining tests have a time complexity of O(n).  And all the remaining
   tests consist of 1 or 2 subtract/compares per point.  So it screams.
*/

for(i=0;i<BIG-1;i++) {
  for(j=i+1;j<BIG;j++) {
//count++;
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
      } // found new shortest disance
    } // dy quick check
  } // inner loop
} // primary loop


//printf("%i, %i (%i)\n",i,j,count);
printf("shortest distance is %lf\n",shortest);

  return 0;
} // main

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
number of brute-force comparisons would be 100,000,000,000,000 (100 trillion)
*/

