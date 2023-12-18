set out "dL_dphip.eps"
set term post eps color

# OLD commands
#set view map
#unset key
#unset surface

# NEW commands
set dgrid3d 101,101 qnorm 1
set contour base
set cntrparam levels 15

set view 73,350

set xlabel "phi\'"
set ylabel "I"

set xrange [0:pi]

splot "dL_dphip.res" u 2:1:3 with lines not

set term pop
set out
