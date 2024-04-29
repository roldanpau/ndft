PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion

# SM1
./phase_port_SM 1 0 7.5 100 1000 1 > phase_port_SM.res
./diffusion 1 1 3.14 > diffusion.res
gnuplot diffusion.plt
mv diffusion.png $IMGDIR

# SM2
./phase_port_SM 2 0 7 100 1000 1 > phase_port_SM2.res
./diffusion 2 1 3.14 > diffusion_SM2.res
gnuplot diffusion_SM2.plt
mv diffusion_SM2.png $IMGDIR

