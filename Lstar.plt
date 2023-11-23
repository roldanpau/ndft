set out "Lstar.eps"
set term post eps color

# OLD commands
#set view map
#unset key
#unset surface

# NEW commands
set dgrid3d 101,101 qnorm 1
set contour base
set cntrparam levels 15

set xlabel "phi\'"
set ylabel "I"

splot "Lstar.res" u 2:1:3 with lines

set term pop
set out
