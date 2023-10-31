#!/bin/bash

# sort.sh: 
#
# The continuation procedure generates many heteroclinic connections that are
# not sorted.
#
# This script parses the output of the continuation procedure (files like
# 'cont_3_3.res_curve1') and sorts them according to increasing (numerical)
# value of the given column.
#
# For instance, column=12 corresponds to angle \phi_2 of the unstable point.
# Column=6 corresponds to angle \phi_2 of the stable point.


if [ $# -lt 3 ]
then
   echo "Usage: $0 first_tor last_tor sort_column"
  exit 1
fi 

for i in `seq $1 $2`
do
     for j in `seq $1 $2`
     do
	file=$(printf "cont_%s_%s.res_curve1" $i $j)
	sortedfile=$(printf "cont_%s_%s.res_curve1_sorted%s" $i $j $3)
	env LC_ALL=C sort -g -k $3,$3 -u $file > $sortedfile
     done
done
