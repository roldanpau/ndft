#set term tikz
#set out "check_FourierTaylor_I_1.tex"
set term png
set out "check_FourierTaylor_I_1.png"

set xrange [0:pi]
plot \
"curve_2_interp" w p pt 1 lc 1 not, \
"SM_I_1.dat" with lines lt 1 not

unset out
unset term
