#set out "interp_poly_A4.eps"
#set term post eps color

set key top left
set xlabel "I"
set ylabel "A_4"
plot "A4.res" w p pt 3 ps 3, \
"interp_poly_A4_M2" w l t "polynomial extrapolation of deg 2", \
"interp_poly_A4_M3" w l t "polynomial extrapolation of deg 3", \
"interp_poly_A4_M4" w l t "polynomial extrapolation of deg 4"

set term pop
set out
