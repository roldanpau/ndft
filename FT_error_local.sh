# Compute local FT error over the domain I\in[0,3]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images_SM2

make
./FT_error 3 > FT_error_local.res
gnuplot FT_error_local.plt
mv FT_error_local.tex $IMGDIR
