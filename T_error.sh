# Compute global T error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make T_error

# SM1
./T_error 1 7 > T_error.res
gnuplot T_error.plt
mv T_error.tex $IMGDIR

# SM1
./T_error 2 7 > T_error_SM2.res
gnuplot T_error_SM2.plt
mv T_error_SM2.tex $IMGDIR
