#set out "interp_poly_B2.eps"
#set term post eps color

set key top left
set xlabel "Action level I"
set ylabel "Fourier coefficient B_2"
plot "B2_scaled.dat" w p pt 3 ps 3, \
"interp_poly_B2" w l t "polynomial interpolation"

set term pop
set out
