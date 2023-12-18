make
# Resonance 5:7
# Remember to modify phase_port_SM.plt!!
./phase_port_SM 1000 10000 1 > phase_port_SM.res
gnuplot phase_port_SM.plt
mv phase_port_SM.eps paper/images/phase_port_SM_1_res57.eps
rm phase_port_SM.res
