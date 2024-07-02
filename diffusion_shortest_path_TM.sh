PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion_shortest_path_TM

#./phase_port_SM 1 0 7.5 100 1000 1 > phase_port_SM.res
#./diffusion_shortest_path 1 3.14 5 0 > diffusion_shortest_path.res
./diffusion_shortest_path_TM 1 1.5 7 1.5 > diffusion_shortest_path_TM.res
gnuplot diffusion_shortest_path_TM.plt
mv diffusion_shortest_path_TM.png $IMGDIR
