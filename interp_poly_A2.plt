#set out "interp_poly_A2.eps"
#set term post eps color

set key top left
set xlabel "I"
set ylabel "A_2"
plot "A2.res" w p pt 3 ps 3, \
"interp_poly_A2_M2" w l t "polynomial extrapolation of deg 2", \
"interp_poly_A2_M3" w l t "polynomial extrapolation of deg 3"

set term pop
set out
