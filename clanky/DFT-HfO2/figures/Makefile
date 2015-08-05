.PHONY: all clean update_data
HOST = ondracka@salomon.it4i.cz:HfO2/

FIGURES = c-HfO2.pdf t-HfO2.pdf m-HfO2.pdf am-HfO2.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

update_data:
	scp $(HOST)cubic/holec-PBE/20000k_9Rk_mBJ/20000k_9Rk_mBJ.epsilon cubic.tmp
	head -n 1000 cubic.tmp > cubic.epsilon
	rm cubic.tmp
	scp $(HOST)amorphous/am-HfO2-96at-fastcool/27k_9Rk_mBJ/64k_9Rk_mBJ_5Emax/64k_9Rk_mBJ_5Emax.epsilon amorphous.tmp
	head -n 1000 amorphous.tmp > amorphous.epsilon
	rm amorphous.tmp
	scp $(HOST)monoclinic/holec-PBE/5000k_9Rk_mBJ/5000k_9Rk_mBJ.epsilon monoclinic.tmp
	head -n 1000 monoclinic.tmp > monoclinic.epsilon
	rm monoclinic.tmp
	scp $(HOST)tetragonal/holec-PBE/5000k_9Rk_mBJ/5000k_9Rk_mBJ.epsilon tetragonal.tmp
	head -n 1000 tetragonal.tmp > tetragonal.epsilon
	rm tetragonal.tmp

clean:
	rm -f *~ $(FIGURES)
