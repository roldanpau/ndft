set term tikz
set out "T_error.tex"

#set title "Error in the phi component"

set xlabel '$N$'
set ylabel '$L$'
set zlabel '$\epsilon_\phi$'

set hidden3d

set xtics 2			# increments of 2
set ytics 0,1,6

set view 59,73,1,1
#splot "T_error.res" using 1:2:3 every :2::1 with lp palette not
splot [2:10] "T_error.res" using 1:2:3 with lp palette not

unset out
unset term
