set out "explore.eps"
set term post eps color

set xlabel "phi"
set ylabel "I"

set yrange [3:5]
plot "explore.res" u 2:1 w p not


set term pop
set out 

