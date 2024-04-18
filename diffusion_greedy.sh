PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion_greedy

# SM1
./phase_port_SM 1 0 7.5 100 1000 1 > phase_port_SM.res
./diffusion_greedy 1 1 3.14 > diffusion_greedy.res
gnuplot diffusion_greedy.plt
mv diffusion_greedy.png $IMGDIR

# SM2
./phase_port_SM 2 0 6 100 1000 1 > phase_port_SM2.res
./diffusion_greedy 2 1 3.14 > diffusion_greedy_SM2.res
gnuplot diffusion_greedy_SM2.plt
mv diffusion_greedy_SM2.png $IMGDIR

