#set out "dLstar.eps"
#set term post eps color

set xlabel "I"
set ylabel "phi\'"

set view 89,90

splot \
"dL_I_2.res" with lines lt 1 not, \
"dL_I_2.5.res" with lines lt 1 not, \
"dL_I_3.res" with lines lt 1 not, \
"dL_I_3.5.res" with lines lt 1 not, \
"dL_I_4.res" with lines lt 1 not, \
"dL_I_4.5.res" with lines lt 1 not, \
"dL_I_5.res" with lines lt 1 not, \
"dL_I_5.5.res" with lines lt 1 not, \
"dL_I_6.res" with lines lt 1 not

#set term pop
#set out
