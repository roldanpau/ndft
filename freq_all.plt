set term tikz
set out "freq_all.tex"

set xlabel '$I$'
set ylabel '$\nu$'

pi=3.14159265358979323844
plot 'freq_all.res' u ($1):(2*pi*$4/$3) w lp not

unset out
unset term
