load "plotdefs.plt"

set term png size 800,600
set out "diffusion_SM2.png"

set xlabel '$\phi$'
set ylabel '$I$'

plot [0:pi] "phase_port_SM2.res" u 2:1 ls PPSM2 not, \
"diffusion_SM2.res" u 2:1 w l ls PO not, \
"< awk '{if($3 == \"IM\") print}' diffusion_SM2.res" u 2:1 w p ls IM \
t "IM iterate", \
"< awk '{if($3 == \"SM\") print}' diffusion_SM2.res" u 2:1 w p ls SM2 \
t "SM2 iterate"

unset out
unset term
