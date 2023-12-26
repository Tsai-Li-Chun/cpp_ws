# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target_wise4060  = wise4060_modbus
target_deltaDRV  = deltaDRV_modbus

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
		   -I/usr/local/include/modbus
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
c_sources_wise4060 = \
	src/wise4060_test.cpp \
	src/wise4060_HandShake.cpp
c_sources_deltaDRV = \
	src/deltaDRV_test.cpp \
	src/deltaDRV_modbus_HandShake.cpp


############################################################################
#	object file
######################################
obj_tmp_wise4060 = $(subst $(src_path), $(obj_path), $(c_sources_wise4060))
obj_wise4060     = $(patsubst %.cpp, %.o, $(obj_tmp_wise4060))
obj_tmp_deltaDRV = $(subst $(src_path), $(obj_path), $(c_sources_deltaDRV))
obj_deltaDRV     = $(patsubst %.cpp, %.o, $(obj_tmp_deltaDRV))

############################################################################
#	dependency file
######################################
dep_wise4060 = $(patsubst %.o, %.d, $(obj_wise4060))
dep_deltaDRV = $(patsubst %.o, %.d, $(obj_deltaDRV))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: wise4060 deltaDRV

wise4060: $(target_wise4060)
	@echo "target $< complete"
$(target_wise4060): $(obj_wise4060)
	g++ $^ -o $@ $(libs)

deltaDRV: $(target_deltaDRV)
	@echo "target $< complete"
$(target_deltaDRV): $(obj_deltaDRV)
	g++ $^ -o $@ $(libs)

############################################################################
# build the application
#######################################
-include $(dep_wise4060)
-include $(dep_deltaDRV)
${obj_path}%.o: ${src_path}%.cpp Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
