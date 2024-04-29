set term tikz
set out "dL_dphip_SM2.tex"

set xlabel '$\phi^\prime$'
set ylabel '$I$'

set dgrid3d 101,101 qnorm 1
set contour base
set cntrparam levels 15

set view 73,350

set xrange [0:pi]

splot "dL_dphip_SM2.res" u 2:1:3 with lines not

unset out
unset term
