set out "phase_port_SM.eps"
set term post eps color

set xlabel "phi"
set ylabel "I"

set xrange [0:pi]
plot "phase_port_SM.res" u 2:1 pt 7 ps 0.1 not

set term pop
set out

