set term tikz
set out "curves.tex"

set xlabel '$\phi^\prime$'
set ylabel '$I^\prime$'
plot [0:8] \
"curve_2_interp" w lp t "$I=1$",\
"curve_3_interp" w lp t "$I=2$",\
"curve_4_interp" w lp t "$I=3$",\
"curve_5_interp" w lp t "$I=4$",\
"curve_6_interp" w lp t "$I=5$",\
"curve_7_interp" w lp t "$I=6$",\
"curve_8_interp" w lp t "$I=7$"

unset out 
unset term
