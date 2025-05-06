# Compute global T error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make T_newerror

# SM1
./T_newerror 1 7 > T_newerror.res
#gnuplot T_newerror.plt
#mv T_newerror.tex $IMGDIR

# SM1
./T_newerror 2 7 > T_newerror_SM2.res
#gnuplot T_newerror_SM2.plt
#mv T_newerror_SM2.tex $IMGDIR
