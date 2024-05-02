PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion_stoch

# SM1
./phase_port_SM 1 0 7.5 100 1000 1 > phase_port_SM.res
./diffusion_stoch 1 3.5 3.14 > diffusion_stoch.res
gnuplot diffusion_stoch.plt
mv diffusion_stoch.png $IMGDIR

# SM2
./phase_port_SM 2 0 7 100 1000 1 > phase_port_SM2.res
./diffusion_stoch 2 3.5 3.14 > diffusion_stoch_SM2.res
gnuplot diffusion_stoch_SM2.plt
mv diffusion_stoch_SM2.png $IMGDIR

