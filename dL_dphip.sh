make
./dL_dphip > dL_dphip.res
gnuplot dL_dphip.plt
mv dL_dphip.eps paper/images/
rm dL_dphip.res
