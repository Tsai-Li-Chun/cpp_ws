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
target_clss  = cas_lab_safetysystem
target_adam  = adam5000_modbus

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
c_sources_clss = \
	src/cas_lab_safetysystem.cpp \
	src/cas_lab_safetysystem_classType.cpp \
	src/wise4060_HandShake.cpp
c_sources_adam = \
	src/ADAM5000_LowType.cpp \
	src/ADAM5000_HandShake.cpp

############################################################################
#	object file
######################################
obj_tmp_wise4060 = $(subst $(src_path), $(obj_path), $(c_sources_wise4060))
obj_wise4060     = $(patsubst %.cpp, %.o, $(obj_tmp_wise4060))
obj_tmp_deltaDRV = $(subst $(src_path), $(obj_path), $(c_sources_deltaDRV))
obj_deltaDRV     = $(patsubst %.cpp, %.o, $(obj_tmp_deltaDRV))
obj_tmp_clss = $(subst $(src_path), $(obj_path), $(c_sources_clss))
obj_clss     = $(patsubst %.cpp, %.o, $(obj_tmp_clss))
obj_tmp_adam = $(subst $(src_path), $(obj_path), $(c_sources_adam))
obj_adam     = $(patsubst %.cpp, %.o, $(obj_tmp_adam))

############################################################################
#	dependency file
######################################
dep_wise4060 = $(patsubst %.o, %.d, $(obj_wise4060))
dep_deltaDRV = $(patsubst %.o, %.d, $(obj_deltaDRV))
dep_clss = $(patsubst %.o, %.d, $(obj_clss))
dep_adam = $(patsubst %.o, %.d, $(obj_adam))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: wise4060 deltaDRV clss adam

wise4060: $(target_wise4060)
	@echo "target $< complete"
$(target_wise4060): $(obj_wise4060)
	g++ $^ -o $@ $(libs)

deltaDRV: $(target_deltaDRV)
	@echo "target $< complete"
$(target_deltaDRV): $(obj_deltaDRV)
	g++ $^ -o $@ $(libs)

clss: $(target_clss)
	@echo "target $< complete"
$(target_clss): $(obj_clss)
	g++ $^ -o $@ $(libs)

adam: $(target_adam)
	@echo "target $< complete"
$(target_adam): $(obj_adam)
	g++ $^ -o $@ $(libs)

############################################################################
# build the application
#######################################
-include $(dep_wise4060)
-include $(dep_deltaDRV)
-include $(dep_clss)
-include $(dep_adam)
${obj_path}%.o: ${src_path}%.cpp Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
