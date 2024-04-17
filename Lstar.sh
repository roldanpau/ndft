PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make Lstar

# SM1
./Lstar 1 > Lstar.res
gnuplot Lstar.plt
mv Lstar.tex $IMGDIR

# SM2
./Lstar 2 > Lstar_SM2.res
gnuplot Lstar_SM2.plt
mv Lstar_SM2.tex $IMGDIR
