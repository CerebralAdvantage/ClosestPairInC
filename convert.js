// snippet that converts a json array of point arrays to a simple list of
// real double values for simple reading into my C program

const fs = require('fs')
let i, p = [];

p = JSON.parse(fs.readFileSync("tk.json","utf8"))

fs.writeFileSync("newtk.dat","","utf8")

for(i=0;i<p.length;i++) {
  fs.appendFileSync("newtk.dat",
     p[i][0].toString()+"\n" +
     p[i][1].toString()+"\n");
}
