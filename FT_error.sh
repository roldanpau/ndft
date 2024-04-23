# Compute global FT error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make FT_error

# SM1
./FT_error 1 7 > FT_error.res
gnuplot FT_error.plt
mv FT_error.tex $IMGDIR

# SM2
./FT_error 2 7 > FT_error_SM2.res
gnuplot FT_error_SM2.plt
mv FT_error_SM2.tex $IMGDIR
