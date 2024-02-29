set terminal gif animate delay 5 size 800, 600
set output 'position.gif'

set xlabel 'time'
set ylabel 'x'

set xrange [0:50]
set yrange [760:840]

# Set up loop to generate frames for each line
do for [i=1:499] {

plot "../results/evolution_EULER.txt" u 1:5 every ::1::i with lines lc 1 lw 2 t 'Euler',\
	 "../results/evolution_EULER.txt" u 1:5 every ::i::i with points ps 2 pt 6 lc 1 t '',\
	 "../results/evolution_VERLET.txt" u 1:5 every ::1::i with lines lc 2 lw 2 t 'Verlet',\
	 "../results/evolution_VERLET.txt" u 1:5 every ::i::i with points ps 2 pt 6 lc 2 t '',\
}
