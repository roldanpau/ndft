# Compute local FT error over the domain I\in[1,4]

make
./FT_error 4 > FT_error_local.res
gnuplot FT_error_local.plt
mv FT_error_local.eps paper/images
