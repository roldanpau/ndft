make
for nit in 1 4 16 64 256 1024
do
		for tor in 3 3.5 4 4.5 5
	do
		./explore $tor 1000 $nit > explore_$tor.res
	done
	gnuplot "explore.plt"
	mv explore.eps paper/images/explore_$nit.eps
	
	# Remove result files
	for tor in 3 3.5 4 4.5 5
	do
		rm explore_$tor.res
	done
done
