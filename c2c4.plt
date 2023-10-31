set out "c2.eps"
set term post eps color

set key top left
set xlabel "Action level I"
set ylabel "Fourier coefficients"
plot \
"A2.dat" w lp pt 1 ps 3 t "a2", \
"B2.dat" w lp pt 2 ps 3 t "b2"

set term pop
set out

pause -1

set out "c4.eps"
set term post eps color

plot \
"A4.dat" w lp pt 1 ps 3 t "a4", \
"B4.dat" w lp pt 2 ps 3 t "b4"

set term pop
set out
