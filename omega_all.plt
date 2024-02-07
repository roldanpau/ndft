set term tikz
set out "omega_all.tex"

set xlabel '$I$'
set ylabel '$\omega(I)$'

plot "omega_all.res" w lp not

unset out
unset term
