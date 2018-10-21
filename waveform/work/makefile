
flags := -Wall 
flags += --cc  
flags += --assert 
flags += --coverage 
#flags += --trace 
flags += --trace-fst
flags += -sv  
flist := ../sim/flist.f
top_name := tb

run:compile
	ln -s ../sim/flash.in 
	obj_dir/V$(top_name) | tee run_log.txt

compile:clean
	verilator $(flags) -f ../sim/flist.f --exe ../sim/sim_main.cpp | tee compile_log.txt
	make -j -C obj_dir -f V$(top_name).mk V$(top_name)  | tee -a compile_log.txt

wave:
	gtkwave ./simx.fst &

clean:
	rm obj_dir -rf
	rm -f flash.in
	rm -f compile_log.txt
	rm -f run_log.txt
	rm -f simx.fst
	rm -f simx.fst.hier
