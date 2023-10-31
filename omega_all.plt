set out "omega_all.eps"
set term post eps color

set xlabel "I"
set ylabel "omega(I)"
plot "omega_all.res" w lp not

set term pop
set out

