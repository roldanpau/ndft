set term tikz
set out "check_FourierTaylor.tex"

plot \
"curve_2_interp" w p pt 1 lc 1 not, \
"curve_3_interp" w p pt 1 lc 1 not, \
"curve_4_interp" w p pt 1 lc 1 not, \
"curve_5_interp" w p pt 1 lc 1 not, \
"curve_6_interp" w p pt 1 lc 1 not, \
"curve_7_interp" w p pt 1 lc 1 not, \
"curve_8_interp" w p pt 1 lc 1 not, \
"SM_I_1.dat" with lines lt 1 not, \
"SM_I_2.dat" with lines lt 1 not, \
"SM_I_3.dat" with lines lt 1 not, \
"SM_I_4.dat" with lines lt 1 not, \
"SM_I_5.dat" with lines lt 1 not, \
"SM_I_6.dat" with lines lt 1 not, \
"SM_I_7.dat" with lines lt 1 not

unset out
unset term
