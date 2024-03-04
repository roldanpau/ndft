PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images_SM2

make
./phase_port_SM 0 7 100 1000 1 > phase_port_SM.res
./diffusion 1 3.14 > diffusion.res
gnuplot diffusion.plt
mv diffusion.png $IMGDIR
