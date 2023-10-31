set out "T_error.eps"
set term post eps color

set title "Error in the phi component"

set hidden3d

set xlabel "N (degree of Fourier expansion)"
set ylabel "M (degree of Taylor expansion)"
set zlabel "error"

set ytics 0,1,4

set view 59,73,1,1
splot "T_error.res" using 1:2:3 with lp palette not

set term pop
set out
