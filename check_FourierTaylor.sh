PAPERDIR=~/mat-nuvol/research/ndft-paper

make SM_given_I

for i in {1..7}
do
	./SM_given_I $i > SM_I_$i.dat
	sort -g -k 1,1 SM_I_$i.dat > SM_I_$i.dat.new
	mv SM_I_$i.dat.new SM_I_$i.dat
done

gnuplot check_FourierTaylor.plt
mv check_FourierTaylor.tex $PAPERDIR/images
