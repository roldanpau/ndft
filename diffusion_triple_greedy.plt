set term png size 800,600
set out "diffusion_triple_greedy.png"

set xlabel '$\phi$'
set ylabel '$I$'

plot [0:pi] \
"diffusion_triple_greedy.res" u 2:1 w l not, \
"< awk '{if($3 == \"IM\") print}' diffusion_triple_greedy.res" u 2:1 w p \
pt 3 lc 7 t "IM iterate", \
"< awk '{if($3 == \"SM1\") print}' diffusion_triple_greedy.res" u 2:1 w p \
pt 5 lc 6 t "SM1 iterate", \
"< awk '{if($3 == \"SM2\") print}' diffusion_triple_greedy.res" u 2:1 w p \
pt 5 lc 8 t "SM2 iterate"

unset out
unset term
