#set out "interp_poly_A0.eps"
#set term post eps color

set key top left
set xlabel "Action level I"
set ylabel "Fourier coefficient A_0"
plot "A0.res" w p pt 3 ps 3

set term pop
set out
