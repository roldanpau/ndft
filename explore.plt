set out "explore.eps"
set term post eps color

set xlabel "phi"
set ylabel "I"

set key right bottom

set xrange [0:pi]
set yrange [2:6]
plot \
"explore_3.res" u 2:1 w p pt 3 t "I_0=3", \
"explore_3.5.res" u 2:1 w p pt 3 t "I_0=3.5", \
"explore_4.res" u 2:1 w p pt 3 t "I_0=4", \
"explore_4.5.res" u 2:1 w p pt 3 t "I_0=4.5", \
"explore_5.res" u 2:1 w p pt 3 t "I_0=5"

set term pop
set out 

