#set out "interp_poly_A2.eps"
#set term post eps color

set key top left
set xlabel "Action level I"
set ylabel "Fourier coefficient A_2"
plot "A2.res" w p pt 3 ps 3, \
"interp_poly_A2" w l t "polynomial interpolation"

set term pop
set out
