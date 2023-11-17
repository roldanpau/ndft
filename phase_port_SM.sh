make
./phase_port_SM 100 1000 2 > phase_port_SM.res
gnuplot phase_port_SM.plt
mv phase_port_SM.eps paper/images/phase_port_SM_2.eps
./phase_port_SM 100 1000 0.1 > phase_port_SM.res
gnuplot phase_port_SM.plt
mv phase_port_SM.eps paper/images/phase_port_SM_0.1.eps
./phase_port_SM 100 1000 1 > phase_port_SM.res
gnuplot phase_port_SM.plt
mv phase_port_SM.eps paper/images/phase_port_SM_1.eps

