set term png size 800,600
set out "resonance23.png"

set xlabel '$\phi$'
set ylabel '$I$'

set xrange [0:pi]

# Resonance 2:3 is located at I=2.452
I=2.452
# Resonance 5:7 is located at I=5.1505
#I=5.1505

set yrange [I-1:I+1]

#set arrow from 0,I to pi,I nohead 
plot "phase_port_SM_highres.res" u 2:1 pt 7 ps 0.05 not

unset out
unset term

