PAPERDIR=~/mat-nuvol/research/ndft-paper

make
# Resonance 2:3
./phase_port_SM 1000 10000 0.1 > phase_port_SM_highres.res
gnuplot resonance23.plt
mv resonance23.png paper/images/
#rm phase_port_SM.res
