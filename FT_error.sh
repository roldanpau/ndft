# Compute global FT error over the global domain I\in[1,7]

make
./FT_error 7 > FT_error.res
gnuplot FT_error.plt
mv FT_error.eps paper/images
