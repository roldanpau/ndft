cut -d ' ' -f 4 curve1_3_3_dom_0.res > I_3_3
cut -d ' ' -f 4 curve1_3_3_rng_0.res > Ip_3_3
paste I_3_3 Ip_3_3 > I_Ip_3_3
awk -f deltaI_avg.awk I_Ip_3_3
