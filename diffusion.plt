set term png size 800,600
set out "diffusion.png"

set xlabel '$\phi$'
set ylabel '$I$'

plot [0:pi] "phase_port_SM.res" u 2:1 pt 7 ps 0.1 not, \
"diffusion.res" u 2:1 w l not, \
"< awk '{if($3 == \"IM\") print}' diffusion.res" u 2:1 w p pt 3 lc 7 \
t "inner map iterate", \
"< awk '{if($3 == \"SM\") print}' diffusion.res" u 2:1 w p pt 5 lc 6 \
t "scattering map iterate"

unset out
unset term
