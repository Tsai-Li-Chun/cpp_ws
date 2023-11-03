# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target_w = shared_memory_write
target_r = shared_memory_read

############################################################################
#	project file paths
#######################################
# source code file paths
src_path = src/
# headle file paths
inc_path = -Iinc/
# object file paths
obj_path = build/

#######################################
# link script & libraries
#######################################
# libraries

############################################################################
#	building variables
######################################
# optimization
opt = -O0

############################################################################
#	compile gcc flags
#######################################
# Generate dependency information
CFLAGS = -std=c++11 -MMD -MP $(opt) $(inc_path)

############################################################################
#	source code
######################################
c_sources_w	= \
	$(src_path)shared_memory_write.cpp \
	$(src_path)shm_controller.cpp
c_sources_r	= \
	$(src_path)shared_memory_read.cpp \
	$(src_path)shm_controller.cpp

############################################################################
#	object file
######################################
obj_tmp_w	= $(subst $(src_path), $(obj_path), $(c_sources_w))
obj_w		= $(patsubst %.cpp, %.o, $(obj_tmp_w))
obj_tmp_r	= $(subst $(src_path), $(obj_path), $(c_sources_r))
obj_r		= $(patsubst %.cpp, %.o, $(obj_tmp_r))

############################################################################
#	dependency file
######################################
dep     = $(patsubst %.o, %.d, $(obj))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: write read
write: $(target_w)
	@echo "target $< complete"
$(target_w): $(obj_w)
	g++ $^ -o $@ $(libs)

read: $(target_r)
	@echo "target $< complete"
$(target_r): $(obj_r)
	g++ $^ -o $@ $(libs)

############################################################################
# build the application
#######################################
-include $(dep)
${obj_path}%.o: ${src_path}%.cpp Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target_w) $(target_r)
	rm -f $(obj_path)*.o $(obj_path)*.d
