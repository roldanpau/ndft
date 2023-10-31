#set out "phi_minus_phip.eps"
#set term post eps color

plot "phi_minus_phip.res" u 1:($2<0? $2+6.28 : $2) t "phi - phi'", \
"dL_dI_I_2.res" u 2:3

set term pop
set out
