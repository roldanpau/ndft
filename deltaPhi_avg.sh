cut -d ' ' -f 8 curve1_3_3_dom_0.res > phi_3_3
cut -d ' ' -f 8 curve1_3_3_rng_0.res > phip_3_3
paste phi_3_3 phip_3_3 > phi_phip_3_3
awk -f deltaPhi_avg.awk phi_phip_3_3
