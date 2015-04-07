.PHONY: all clean update_data
HOST = ondracka@anselm.it4i.cz:HfO2/

FIGURES = c-HfO2.pdf m-HfO2.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

update_data:
	scp $(HOST)cubic/wyckoff/20000k_9Rk_mBJ/20000k_9Rk_mBJ.epsilon cubic.epsilon
	scp $(HOST)cubic/wyckoff/20000k_9Rk_mBJ/20000k_9Rk_mBJ.epsilon_br cubic.epsilon_br
	scp $(HOST)amorphous/am-HfO2-96at-fastcool/27k_9Rk_mBJ/64k_9Rk_mBJ_5Emax/64k_9Rk_mBJ_5Emax.epsilon amorphous.epsilon
	scp $(HOST)monoclinic/ruh/1000k_9Rk_mBJ/1000k_9Rk_mBJ.epsilon monoclinic.epsilon

clean:
	rm -f *~ $(FIGURES)
