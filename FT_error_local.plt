set term tikz
set out "FT_error_local.tex"

#set title "Error in the I component"

set xlabel '$N$'
set ylabel '$L$'
set zlabel '$\epsilon_I$'

set hidden3d

set xtics 2			# increments of 2
set ytics 0,1,3

set view 59,73,1,1
#splot "FT_error_local.res" using 1:2:3 every :2::1 with lp palette not
splot [2:10] "FT_error_local.res" using 1:2:3 with lp palette not

unset out
unset term
