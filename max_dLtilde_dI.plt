set term tikz
set out "max_dLtilde_dI.tex"

set xlabel '$I$'

plot "omega_all.res" w lp not, "max_dLtilde_dI.res" w lp not

unset out
unset term

set term tikz
set out "max_dLtilde_dI_SM2.tex"

set xlabel '$I$'

plot "omega_all_SM2.res" w lp not, "max_dLtilde_dI_SM2.res" w lp not

unset out
unset term
