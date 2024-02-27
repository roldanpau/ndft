PAPERDIR=~/mat-nuvol/research/ndft-paper

make
# Resonance 5:7
./phase_port_SM 5.4 5.8 500 5000 1 > resonance57.res
gnuplot resonance57.plt
mv resonance57.eps $PAPERDIR/images/
#mv resonance57.png $PAPERDIR/images/
rm resonance57.res
