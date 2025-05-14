set term png size 800,600
set out "phase_port_SM2.png"
#set term cairolatex png size 4.8,3.6
#set out "phase_port_SM2.tex"

#set xlabel '$\phi$'
#set ylabel '$I$'
set xlabel "phi"
set ylabel "I"

set xrange [0:pi]
#set yrange [0:7]

#set arrow from 0,I to pi,I nohead 
plot "phase_port_SM2.res" u 2:1 pt 7 ps 0.05 not

unset out
unset term

