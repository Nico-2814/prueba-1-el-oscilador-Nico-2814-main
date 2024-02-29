algorithm = 'VERLET'

set term png size 1280, 480
set output "energy_".algorithm.".png"

set xlabel 't'
set ylabel 'E'

set key outside right center

set xrange[0:50]
set yrange[0:18000]

plot "../results/evolution_".algorithm.".txt" u 1:4 w l t 'Em(t)',\
	"../results/evolution_".algorithm.".txt" u 1:2 w l t 'Ec(t)',\
	"../results/evolution_".algorithm.".txt" u 1:3 w l t 'Ep(t)'
