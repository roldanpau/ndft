set term tikz
set out "omega.tex"

set xlabel '$\phi^\prime$'
set ylabel '$\omega$'

# \omega(I=2) of the first SM
# Before plotting, call ./omega 1 2.0 > omega.res
plot [0:pi] "omega.res" u 2:3 t '$\omega(2, \phi^\prime)$', \
2.073006 with lines t '$\overline{\omega}(2)$'

# \omega(I=7) of the first SM
# Before plotting, call ./omega 1 7.0 > omega.res
#plot [0:pi] "omega.res" u 2:3 t '$\omega(7, \phi^\prime)$', \
#2.398588 with lines t '$\overline{\omega}(7)$'

unset out
unset term
