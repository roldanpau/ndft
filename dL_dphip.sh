PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images_SM2

make
./dL_dphip > dL_dphip.res
gnuplot dL_dphip.plt
mv dL_dphip.tex $IMGDIR
rm dL_dphip.res
