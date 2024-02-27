PAPERDIR=~/mat-nuvol/research/ndft-paper

make
# Resonance 5:7
./phase_port_SM 4 6 1000 10000 1 > resonance57.res
gnuplot resonance57.plt
#mv resonance57.eps $PAPERDIR/images/
mv resonance57.png $PAPERDIR/images/
rm resonance57.res
