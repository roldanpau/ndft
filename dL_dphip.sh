PAPERDIR=~/mat-nuvol/research/ndft-paper

make
./dL_dphip > dL_dphip.res
gnuplot dL_dphip.plt
mv dL_dphip.tex $PAPERDIR/images/
rm dL_dphip.res
