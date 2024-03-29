# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target_hantas_screwdriver = cas_hantas_screwdriver

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
inc_path = -Iinc/ -I../modbus_project/inc/ 
# object file paths
obj_path = build/

#######################################
# link script & libraries
#######################################
# libraries
libs = -L/usr/local/lib -lmodbus

############################################################################
#	compile gcc flags
#######################################
# Generate dependency information
CFLAGS = -std=c++11 $(OPT) -MMD -MP $(inc_path)

############################################################################
#	source code
######################################
c_sources_hantas_screwdriver = \
	src/hantas_screwdriver_controller.cpp

############################################################################
#	object file
######################################

# obj_tmp_hantas_screwdriver = \
# 	build/xbot_test.cpp \
# 	build/xbot_handshake.cpp \
# 	build/deltaDRV_modbus_HandShake.cpp
obj_tmp_hantas_screwdriver = $(subst $(src_path), $(obj_path), $(c_sources_hantas_screwdriver))
obj_hantas_screwdriver     = $(patsubst %.cpp, %.o, $(obj_tmp_hantas_screwdriver))

############################################################################
#	dependency file
######################################
dep_hantas_screwdriver = $(patsubst %.o, %.d, $(obj_hantas_screwdriver))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: hantas_screwdriver

hantas_screwdriver: $(target_hantas_screwdriver)
	@echo "target $< complete"
$(target_hantas_screwdriver): $(obj_hantas_screwdriver)
	g++ $^ -o $@ $(libs)

############################################################################
# build the application
#######################################
-include $(dep_hantas_screwdriver)
${obj_path}%.o: ${src_path}%.cpp Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
