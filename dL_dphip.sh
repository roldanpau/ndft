PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make dL_dphip

# SM1
./dL_dphip 1 > dL_dphip.res
gnuplot dL_dphip.plt
mv dL_dphip.tex $IMGDIR

# SM2
./dL_dphip 2 > dL_dphip_SM2.res
gnuplot dL_dphip_SM2.plt
mv dL_dphip_SM2.tex $IMGDIR

