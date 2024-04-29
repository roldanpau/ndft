load "plotdefs.plt"

set term png size 800,600
set out "diffusion_shortest_path.png"

set xlabel '$\phi$'
set ylabel '$I$'

plot [0:pi] \
"phase_port_SM.res" u 2:1 ls PPSM1 not, \
"phase_port_SM2.res" u 2:1 ls PPSM2 not, \
"diffusion_shortest_path.res" u 2:1 w l ls PO not, \
"< awk '{if($3 == \"IM\") print}' diffusion_shortest_path.res" u 2:1 w p \
ls IM t "IM iterate", \
"< awk '{if($3 == \"SM1\") print}' diffusion_shortest_path.res" u 2:1 w p \
ls SM1 t "SM1 iterate", \
"< awk '{if($3 == \"SM2\") print}' diffusion_shortest_path.res" u 2:1 w p \
ls SM2 t "SM2 iterate"

unset out
unset term
