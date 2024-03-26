# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target_xbot_HS  = xbot_HandShake

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
inc_path = -Iinc/
# object file paths
obj_path = build/

#######################################
# link script & libraries
#######################################
# libraries
libs = -L/usr/local/lib

############################################################################
#	compile gcc flags
#######################################
# Generate dependency information
CFLAGS = -std=c++11 $(OPT) -MMD -MP $(inc_path)

############################################################################
#	source code
######################################
c_sources_xbot_HS = \
	src/xbot_handshake.cpp

############################################################################
#	object file
######################################
obj_tmp_xbot_HS = $(subst $(src_path), $(obj_path), $(c_sources_xbot_HS))
obj_xbot_HS     = $(patsubst %.cpp, %.o, $(obj_tmp_xbot_HS))

############################################################################
#	dependency file
######################################
dep_xbot_HS = $(patsubst %.o, %.d, $(obj_xbot_HS))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: xbot_HS

xbot_HS: $(target_xbot_HS)
	@echo "target $< complete"
$(target_xbot_HS): $(obj_xbot_HS)
	g++ $^ -o $@ $(libs)

############################################################################
# build the application
#######################################
-include $(dep_xbot_HS)
${obj_path}%.o: ${src_path}%.cpp Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
