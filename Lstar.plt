set term tikz
set out "Lstar.tex"

set xlabel '$\phi^\prime$'
set ylabel '$I$'

# NEW commands
set dgrid3d 101,101 qnorm 1
set contour base
set cntrparam levels 15

splot "Lstar.res" u 2:1:3 with lines t ' '

unset out 
unset term
