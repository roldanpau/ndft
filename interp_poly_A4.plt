#set out "interp_poly_A4.eps"
#set term post eps color

set key top left
set xlabel "Action level I"
set ylabel "Fourier coefficient A_4"
plot "A4_scaled.dat" w p pt 3 ps 3, \
"interp_poly_A4" w l t "polynomial interpolation"

set term pop
set out
