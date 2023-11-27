set out "diffusion.eps"
set term post eps color

set xlabel "phi"
set ylabel "I"

plot [0:pi] [1.5:7] "phase_port_SM.res" u 2:1 pt 7 ps 0.05 not, \
"diffusion.res" u 2:1 w l not, \
"< awk '{if($3 == \"IM\") print}' diffusion.res" u 2:1 w p pt 3 t "inner map iterate", \
"< awk '{if($3 == \"SM\") print}' diffusion.res" u 2:1 w p pt 5 t "scattering map iterate"

set term pop
set out

