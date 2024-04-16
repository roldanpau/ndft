PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make phase_port_SM
#./phase_port_SM 100 1000 1 > phase_port_SM_1.res
#gnuplot phase_port_SM.plt
#mv phase_port_SM.eps paper/images/phase_port_SM_1.eps

# Resonance 2:3
# Remember to modify phase_port_SM.plt!!
#./phase_port_SM 1000 10000 0.1 > phase_port_SM.res
#gnuplot phase_port_SM.plt
#mv phase_port_SM.eps paper/images/phase_port_SM_0.1_res23.eps
#rm phase_port_SM.res

# Resonance 5:7
# Remember to modify phase_port_SM.plt!!
#./phase_port_SM 1000 10000 0.1 > phase_port_SM.res
#gnuplot phase_port_SM.plt
#mv phase_port_SM.eps paper/images/phase_port_SM_0.1_res57.eps
#rm phase_port_SM.res

# SM1
echo "Computing phase portrait of SM1..."
./phase_port_SM 1 0 7.5 100 1000 1 > phase_port_SM.res
gnuplot phase_port_SM.plt
mv phase_port_SM.png $IMGDIR
echo "Done!"

# SM2
echo "Computing phase portrait of SM2..."
#./phase_port_SM 2 0 7 100 1000 1 > phase_port_SM2.res
./phase_port_SM 2 0 6 100 1000 1 > phase_port_SM2.res
gnuplot phase_port_SM2.plt
mv phase_port_SM2.png $IMGDIR
echo "Done!"
