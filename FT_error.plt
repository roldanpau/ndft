set out "FT_error.eps"
set term post eps color

set title "Error in the I component"

set hidden3d

set xlabel "N (degree of Fourier expansion)"
set ylabel "L (degree of Taylor expansion)"
set zlabel "error"

set xtics 2			# increments of 2
set ytics 0,1,4

#set view 52,49,1,1
set view 59,73,1,1
#splot "FT_error.res" using 1:2:3 every :2::1 with lp palette not
splot [2:20] "FT_error.res" using 1:2:3 with lp palette not

set term pop
set out
