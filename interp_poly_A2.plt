set term tikz
set out "interp_poly_A2.tex"

set xlabel '$I$'
set ylabel '$A_2$'

set key top left
plot "A2.res" w p pt 3 ps 3 not, \
"interp_poly_A2_M4" w l t "polynomial extrapolation of deg 4", \
"interp_poly_A2_M5" w l t "polynomial extrapolation of deg 5"

unset out
unset term
