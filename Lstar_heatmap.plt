#set out "Lstar.eps"
#set term post eps color

plot "Lstar.res" u 2:1:3 pt 5 ps 2 lc palette not

set term pop
set out
