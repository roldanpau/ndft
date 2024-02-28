# Compute global FT error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images_SM2

make
./FT_error 7 > FT_error.res
gnuplot FT_error.plt
mv FT_error.tex $IMGDIR
