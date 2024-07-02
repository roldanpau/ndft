# This file is only used to schematically represent the inner map as an
# integrable twist map. The image generated is only used in the slides of the
# talk.

set term tikz
set out "twist.tex"

set xlabel '$\phi$'
set ylabel '$I$'
plot [0:2*pi] [0:52]\
10 w l lc 1 not,\
20 w l lc 1 not,\
30 w l lc 1 not,\
40 w l lc 1 not,\
50 w l lc 1 not,\
5 w l lc 1 not,\
15 w l lc 1 not,\
25 w l lc 1 not,\
35 w l lc 1 not,\
45 w l lc 1 not

unset out 
unset term
