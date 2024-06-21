# Closest Pair - New algorithm
```
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
      } // found new shortest disance
    } // dy quick check
  } // inner loop
} // primary loop
```
```
O(n logn) to sort on one axis only
O(n) to find the closest pair
total = O(n logn)
Doubtful? Run test.c locally.
```
Ask me how.  Better yet, **hire** me!
