set term tikz
set out "check_FourierTaylor.tex"

plot [0:pi] \
"curve_2_interp" w p pt 1 lc 1 not, \
"curve_3_interp" w p pt 1 lc 1 not, \
"curve_4_interp" w p pt 1 lc 1 not, \
"curve_5_interp" w p pt 1 lc 1 not, \
"curve_6_interp" w p pt 1 lc 1 not, \
"curve_7_interp" w p pt 1 lc 1 not, \
"curve_8_interp" w p pt 1 lc 1 not, \
"newcurve_2_interp" w p pt 1 lc 2 not, \
"newcurve_3_interp" w p pt 1 lc 2 not, \
"newcurve_4_interp" w p pt 1 lc 2 not, \
"newcurve_5_interp" w p pt 1 lc 2 not, \
"newcurve_6_interp" w p pt 1 lc 2 not, \
"newcurve_7_interp" w p pt 1 lc 2 not, \
"newcurve_8_interp" w p pt 1 lc 2 not, \
"SM_I_0.5.dat" with lines lt 1 lc 2 not, \
"SM_I_1.0.dat" with lines lt 1 lc 1 not, \
"SM_I_1.5.dat" with lines lt 1 lc 2 not, \
"SM_I_2.0.dat" with lines lt 1 lc 1 not, \
"SM_I_2.5.dat" with lines lt 1 lc 2 not, \
"SM_I_3.0.dat" with lines lt 1 lc 1 not, \
"SM_I_3.5.dat" with lines lt 1 lc 2 not, \
"SM_I_4.0.dat" with lines lt 1 lc 1 not, \
"SM_I_4.5.dat" with lines lt 1 lc 2 not, \
"SM_I_5.0.dat" with lines lt 1 lc 1 not, \
"SM_I_5.5.dat" with lines lt 1 lc 2 not, \
"SM_I_6.0.dat" with lines lt 1 lc 1 not, \
"SM_I_6.5.dat" with lines lt 1 lc 2 not, \
"SM_I_7.0.dat" with lines lt 1 lc 1 not

unset out
unset term
