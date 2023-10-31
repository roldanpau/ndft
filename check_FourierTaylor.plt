#set out "check_FourierTaylor.eps"
#set term post eps color

plot \
"curve_3" w p pt 1 lc 1 t "data", \
"curve_4" w p pt 1 lc 1 not, \
"curve_5" w p pt 1 lc 1 not, \
"curve_6" w p pt 1 lc 1 not, \
"curve_7" w p pt 1 lc 1 not, \
"SM_I_2.dat" with lines lt 1 t "Fourier-Taylor approximation", \
"SM_I_2.5.dat" with lines lt 1 not, \
"SM_I_3.dat" with lines lt 1 not, \
"SM_I_3.5.dat" with lines lt 1 not, \
"SM_I_4.dat" with lines lt 1 not, \
"SM_I_4.5.dat" with lines lt 1 not, \
"SM_I_5.dat" with lines lt 1 not, \
"SM_I_5.5.dat" with lines lt 1 not, \
"SM_I_6.dat" with lines lt 1 not

set term pop
set out
