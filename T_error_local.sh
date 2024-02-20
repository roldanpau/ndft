PAPERDIR=~/mat-nuvol/research/ndft-paper

make
./T_error 3 > T_error_local.res
gnuplot T_error_local.plt
mv T_error_local.tex $PAPERDIR/images
