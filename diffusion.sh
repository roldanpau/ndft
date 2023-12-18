make
./phase_port_SM 100 1000 1 > phase_port_SM.res
./diffusion 2 3.14 > diffusion.res
gnuplot diffusion.plt
mv diffusion.eps paper/images/
