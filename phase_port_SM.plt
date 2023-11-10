set out "phase_port_SM.eps"
set term post eps color

set xlabel "phi"
set ylabel "I"

plot "phase_port_SM.res" u 2:1 pt 7 ps 0.05 not

set term pop
set out

