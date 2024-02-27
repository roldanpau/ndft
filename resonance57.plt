#set term png size 800,600
#set out "resonance57.png"
set term post eps
set out "resonance57.eps"

set xlabel '$\phi$'
set ylabel '$I$'

set xrange [0:pi]
set yrange [4.65:5.65]

# Resonance 5:7 is located at I=5.1505
I=5.1505

set arrow from 0,I to pi,I nohead 
plot "resonance57.res" u 2:1 pt 7 ps 0.05 not

unset out
unset term

