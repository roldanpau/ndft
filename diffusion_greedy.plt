load "plotdefs.plt"

set term png size 800,600
set out "diffusion_greedy.png"

set xlabel '$\phi$'
set ylabel '$I$'

plot [0:pi] "phase_port_SM.res" u 2:1 ls PPSM1 not, \
"diffusion_greedy.res" u 2:1 w l ls PO not, \
"< awk '{if($3 == \"IM\") print}' diffusion_greedy.res" u 2:1 w p ls IM \
t "IM iterate", \
"< awk '{if($3 == \"SM\") print}' diffusion_greedy.res" u 2:1 w p ls SM1 \
t "SM1 iterate"

unset out
unset term
