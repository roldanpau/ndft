PAPERDIR=~/mat-nuvol/research/ndft-paper

make
# Resonance 2:3
./phase_port_SM 1 4 500 10000 1 > resonance23.res
gnuplot resonance23.plt
mv resonance23.png $PAPERDIR/images/
rm resonance23.res
