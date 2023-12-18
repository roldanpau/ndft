set out "A4B4.eps"
set term post eps color

set key top left
set xlabel "I"
set ylabel "A_4, B_4"
plot "A4.res" w lp t "A_4", \
     "B4.res" w lp t "B_4"

set term pop
set out
