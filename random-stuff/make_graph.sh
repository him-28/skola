#!/bin/bash

rm deconv_graph.gpi

echo "set terminal pdf enhanced font \"Helvetica,14\" linewidth 3 size 13cm,10cm" >> deconv_graph.gpi
echo "set locale \"cs_CZ.UTF-8\"" >> deconv_graph.gpi
echo "set encoding utf8" >> deconv_graph.gpi
echo "set xlabel \"Energy (eV)\"" >> deconv_graph.gpi
echo "set ylabel \"Epsilon_i\"" >> deconv_graph.gpi
echo "" >> deconv_graph.gpi
echo "plot [0:15]\\" >> deconv_graph.gpi
EPSFILE=$(find ../*.epsilon)	
echo "\"$EPSFILE\" u 1:3 t \"total\" w l,\\" >> deconv_graph.gpi

for i in $(find *.epsdec) 
do
	echo "\"$i\" w l,\\" >> deconv_graph.gpi
done

sed -i '$s/..$//' deconv_graph.gpi

gnuplot deconv_graph.gpi > graph.pdf
evince graph.pdf
