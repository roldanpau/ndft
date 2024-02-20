set term tikz
set out "omega.tex"

set xlabel '$\phi^\prime$'
set ylabel '$\omega$'

plot [0:pi] "omega.res" u 2:3 t '$\omega(2, \phi^\prime)$', \
2.072993 with lines t '$\overline{\omega}(2)$'

unset out
unset term
