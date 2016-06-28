.PHONY: all clean

FIGURES = gap-edge.pdf HMDSO.pdf TTIP.pdf coord.pdf Ef-all.pdf mBJ.pdf gap1.pdf gap2.pdf SiTiO2-dos.pdf gap-edge.pdf SiTiO2-n.pdf XRD.pdf IPR.pdf epsi-calc.pdf
LOC1 = ondracka@salomon.it4i.cz:scratch/

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ --export-area-drawing --file=$<

gap-edge.pdf: $(bash ls am-*.joint)

update_data_new:
	scp $(LOC1)SiTiO2-am-WIENrelax/0.0/64k_7.5Rk_mBJkol/64k_7.5Rk_mBJkol.joint am-0.0.joint
	scp $(LOC1)SiTiO2-am-WIENrelax/0.1875/64k_7.5Rk_mBJkol/64k_7.5Rk_mBJkol.joint am-0.1875.joint
	scp $(LOC1)SiTiO2-am-WIENrelax/0.34375/64k_7.5Rk_mBJkol/64k_7.5Rk_mBJkol.joint am-0.34375.joint
	scp $(LOC1)SiTiO2-am-WIENrelax/0.5/64k_7.5Rk_mBJkol/64k_7.5Rk_mBJkol.joint am-0.5.joint
	scp $(LOC1)SiTiO2-am-WIENrelax/0.65625/64k_7.5Rk_mBJkol/64k_7.5Rk_mBJkol.joint am-0.65625.joint

clean:
	rm -f *~ $(FIGURES) fit.log
