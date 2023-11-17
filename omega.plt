set out "omega.eps"
set term post eps color

plot "omega.res" u 2:3 t "omega(I=2)", \
2.072696 with lines t "average omega"

set term pop
set out
