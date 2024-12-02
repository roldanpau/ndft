PAPERDIR=~/research/ndft-paper
IMGDIR=$PAPERDIR/images

make twist

# SM1
./twist 1 > twist.res

# SM2
./twist 2 > twist_SM2.res

gnuplot twist.gpi
mv twist.eps twist_SM2.eps $IMGDIR
