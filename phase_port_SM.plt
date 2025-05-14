set term png size 800,600
set out "phase_port_SM.png"
#set term cairolatex png size 4.8,3.6
#set out "phase_port_SM.tex"

#set xlabel '$\phi$'
#set ylabel '$I$'
set xlabel "phi"
set ylabel "I"

set xrange [0:pi+0.5]
#set yrange [0:7]

# resonance 2:3
I3=2.4175
I4=6.5550
I7=5.0752
I10=4.3631
set arrow from 0,I3 to pi,I3 lc 7 lw 3 nohead 
set arrow from 0,I4 to pi,I4 lc 7 lw 3 nohead 
set arrow from 0,I7 to pi,I7 lc 7 lw 3 nohead 
set arrow from 0,I10 to pi,I10 lc 7 lw 3 nohead 
plot "phase_port_SM.res" u 2:1 pt 7 ps 0.05 not, \
"-" using 2:3:1 with labels not
"2:3 res." 3.34 2.4175
"3:4 res." 3.34 6.5550
"5:7 res." 3.34 5.0752
"7:10 res." 3.34 4.3631

unset out
unset term

