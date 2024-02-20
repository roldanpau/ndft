# Compute global T error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper

make
./T_error 7 > T_error.res
gnuplot T_error.plt
mv T_error.tex $PAPERDIR/images
