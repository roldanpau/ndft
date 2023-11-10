make
for nit in 1 2 4 8 16 32 64 128 256 512 1024
do
	./explore 1000 $nit > explore.res
	gnuplot "explore.plt"
	mv explore.eps paper/images/explore_$nit.eps
done
