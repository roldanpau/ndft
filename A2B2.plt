set out "A2B2.eps"
set term post eps color

set key top left
set xlabel "I"
set ylabel "A_2, B_2"
plot "A2.res" w lp t "A_2", \
     "B2.res" w lp t "B_2"

set term pop
set out
