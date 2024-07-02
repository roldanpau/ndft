set term tikz
set out "curves.tex"

set xlabel '$\phi$'
set ylabel '$I$'
plot [0:2*pi] [0:8.5]\
1 w l lc 1 not,\
2 w l lc 2 not,\
3 w l lc 3 not,\
4 w l lc 4 not,\
5 w l lc 5 not,\
6 w l lc 6 not,\
7 w l lc 7 not,\
"curve_2_interp" w lp lc 1 not,\
"curve_3_interp" w lp lc 2 not,\
"curve_4_interp" w lp lc 3 not,\
"curve_5_interp" w lp lc 4 not,\
"curve_6_interp" w lp lc 5 not,\
"curve_7_interp" w lp lc 6 not,\
"curve_8_interp" w lp lc 7 not

unset out 
unset term
