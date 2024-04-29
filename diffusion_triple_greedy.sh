PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion_triple_greedy

./phase_port_SM 1 0 7.5 100 1000 1 > phase_port_SM.res
./phase_port_SM 2 0 7 100 1000 1 > phase_port_SM2.res

./diffusion_triple_greedy 1 3.14 > diffusion_triple_greedy.res
gnuplot diffusion_triple_greedy.plt
mv diffusion_triple_greedy.png $IMGDIR
