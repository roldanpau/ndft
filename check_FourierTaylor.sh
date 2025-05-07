# check_FourierTaylor.sh: Plot image of the numerical SM versus SSM.
#
# This script is used both for N=L=2, and N=4, L=5. Before calling this script,
# make sure to set degrees N,L in SM_given_I.c. Also, make sure to modify last
# line of this script.

PAPERDIR=~/research/ndft-paper

make SM_given_I

for i in `seq 0 0.5 7`
do
	./SM_given_I $i > SM_I_$i.dat
	sort -g -k 1,1 SM_I_$i.dat > SM_I_$i.dat.new
	mv SM_I_$i.dat.new SM_I_$i.dat
done

gnuplot check_FourierTaylor.plt
mv check_FourierTaylor.tex $PAPERDIR/images/check_FourierTaylor_N2_M2.tex
#mv check_FourierTaylor.tex $PAPERDIR/images/check_FourierTaylor_N4_M5.tex
