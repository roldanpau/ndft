#set out "interp_omega.eps"
#set term post eps color

set key top left
set xlabel "I"
set ylabel "omega"
plot "omega_all.res" w p pt 3 ps 3, \
"interp_poly_omega_M2" w l t "polynomial extrapolation of deg 2", \
"interp_poly_omega_M3" w l t "polynomial extrapolation of deg 3"

set term pop
set out
