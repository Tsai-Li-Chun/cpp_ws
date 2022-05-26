# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target  = modbus

############################################################################
#	building variables
######################################
# optimization
OPT = -O0

############################################################################
#	project file paths
#######################################
# source code file paths
src_path = src/
# headle file paths
inc_path = -Iinc/ \
		   $(shell pkg-config --cflags libmodbus)
# object file paths
obj_path = build/

#######################################
# link script & libraries
#######################################
# libraries
libs = $(shell pkg-config --libs libmodbus)

############################################################################
#	compile gcc flags
#######################################
# Generate dependency information
CFLAGS = -MMD -MP $(inc_path)

############################################################################
#	source code
######################################
c_sources = $(shell ls $(src_path)*.cpp)

############################################################################
#	object file
######################################
obj_tmp	= $(subst $(src_path), $(obj_path), $(c_sources))
obj     = $(patsubst %.cpp, %.o, $(obj_tmp))

############################################################################
#	dependency file
######################################
dep     = $(patsubst %.o, %.d, $(obj))

############################################################################
# default action: build all
######################################
all: $(target)
	@echo "target $< complete"
$(target): $(obj)
	g++ -o $@ $^ $(libs)

############################################################################
# build the application
#######################################
-include $(dep)
$(obj): $(c_sources) Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
