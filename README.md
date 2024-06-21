# Closest Pair - New algorithm
```
// pseudocode with p sorted on the x-axis:
for(i=0;i<BIG-1;i++) {
  for(j=i+1;j<BIG;j++) {
    dx = p[i][0]-p[j][0];
    if(dx < 0) dx = dx * -1;
    if(dx > shortest) { break; } // timesaver!
    dy = p[i][1]-p[j][1];
    if(dy < 0) dy = dy * -1;
    if(dy < shortest) {
      dist = distance(dx,dy);
      if(dist < shortest) { shortest = dist; } // found new shortest disance
    } // dy quick check
  } // inner loop
} // primary loop
return shortest;
```
```
O(n logn) to sort on one axis only
O(n) to find the closest pair
total = O(n logn)
Doubtful? Run test.c locally.
```
Ask me how.  Better yet, **hire** me!
