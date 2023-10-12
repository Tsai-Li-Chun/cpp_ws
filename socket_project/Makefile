# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target_s = server
target_c = client

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
c_sources_s	= \
	$(src_path)main_server.cpp
c_sources_c	= \
	$(src_path)main_client.cpp

############################################################################
#	object file
######################################
obj_tmp_s	= $(subst $(src_path), $(obj_path), $(c_sources_s))
obj_s		= $(patsubst %.cpp, %.o, $(obj_tmp_s))
obj_tmp_c	= $(subst $(src_path), $(obj_path), $(c_sources_c))
obj_c		= $(patsubst %.cpp, %.o, $(obj_tmp_c))

############################################################################
#	dependency file
######################################
dep     = $(patsubst %.o, %.d, $(obj))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: ser cli
ser: $(target_s)
	@echo "target $< complete"
$(target_s): $(obj_s)
	g++ $^ -o $@ $(libs)

cli: $(target_c)
	@echo "target $< complete"
$(target_c): $(obj_c)
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
	rm -f *.o *.d $(target_s) $(target_c)
	rm -f $(obj_path)*.o $(obj_path)*.d
