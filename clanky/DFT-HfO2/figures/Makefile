.PHONY: all clean update_data
H = ondracka@salomon.it4i.cz
HOST = "$H:HfO2"

FIGURES = c-HfO2.pdf t-HfO2.pdf m-HfO2.pdf am-HfO2.pdf m-EV.pdf JDOS.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

update_data:
	scp $(HOST)cubic/holec-PBE/20000k_9Rk_mBJ/20000k_9Rk_mBJ.epsilon cubic.tmp
	head -n 1000 cubic.tmp > cubic.epsilon
	rm cubic.tmp
	scp $(HOST)amorphous/am-HfO2-96at-fastcool/PBE_MSR1a/fine-relax/mBJ-relaxed2/mBJ-relaxed2.epsilon amorphous.tmp
	head -n 1000 amorphous.tmp > amorphous-fast.epsilon
	rm amorphous.tmp
	scp $(HOST)amorphous/am-try2/relaxed-wip/final-fit/mBJ/mBJ.epsilon amorphous.tmp
	head -n 1000 amorphous.tmp > amorphous-slow.epsilon
	rm amorphous.tmp
	scp $(HOST)monoclinic/holec-PBE/5000k_9Rk_mBJ/5000k_9Rk_mBJ.epsilon monoclinic.tmp
	head -n 1000 monoclinic.tmp > monoclinic.epsilon
	rm monoclinic.tmp
	scp $(HOST)tetragonal/holec-PBE/5000k_9Rk_mBJ/5000k_9Rk_mBJ.epsilon tetragonal.tmp
	head -n 1000 tetragonal.tmp > tetragonal.epsilon
	rm tetragonal.tmp
#  cat HfO2/amorphous/am-HfO2-96at-fastcool/PBE_MSR1a/fine-relax/mBJ-relaxed2/mBJ-relaxed2.scf* | grep \:VOL | tail -n1 | grep -o "[0-9]*\.[0-9]*"
	VFAST = 7652.52
	echo "(32*178.49+64*16)*1.602*6.7483/${VFAST}" | bc -l  | grep -o "[0-9]*\.[0-9]\{3\}" > V-fast.txt
	VSLOW = 7833.76
	echo "(32*178.49+64*16)*1.602*6.7483/${VSLOW}" | bc -l  | grep -o "[0-9]*\.[0-9]\{3\}" > V-slow.txt

clean:
	rm -f *~ $(FIGURES)
