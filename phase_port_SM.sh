make
#./phase_port_SM 100 1000 1 > phase_port_SM_1.res
#gnuplot phase_port_SM.plt
#mv phase_port_SM.eps paper/images/phase_port_SM_1.eps

# Resonance 2:3
# Remember to modify phase_port_SM.plt!!
./phase_port_SM 1000 10000 0.1 > phase_port_SM.res
gnuplot phase_port_SM.plt
mv phase_port_SM.eps paper/images/phase_port_SM_0.1_res23.eps
rm phase_port_SM.res

# Resonance 5:7
# Remember to modify phase_port_SM.plt!!
#./phase_port_SM 1000 10000 0.1 > phase_port_SM.res
#gnuplot phase_port_SM.plt
#mv phase_port_SM.eps paper/images/phase_port_SM_0.1_res57.eps
#rm phase_port_SM.res

#./phase_port_SM 100 1000 1 > phase_port_SM.res
#gnuplot phase_port_SM.plt
#mv phase_port_SM.eps paper/images/phase_port_SM_qualit.eps
