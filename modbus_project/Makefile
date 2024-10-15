# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：windows10
#	Brief	：c++ modbus project
# ------------------------------------------------


############################################################################
#	target
######################################
target_wise4060  = wise4060_modbus
target_deltaDRV  = deltaDRV_modbus
target_clss  = cas_lab_safetysystem
target_clst  = cas_lab_stand

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
inc_path = -Iinc/ -Iinc/lib_modbus_inc/
# object file paths
obj_path = build/

#######################################
# link script & libraries
#######################################
# libraries
# libs = -L/usr/local/lib -lmodbus
libs = -Llib/ -lmodbus -static

############################################################################
# C defines
#######################################
C_DEFS = -D__OS_WIN__

############################################################################
#	compile gcc flags
#######################################
# Generate dependency information
CFLAGS = -std=c++14 $(C_DEFS) $(OPT) -MMD -MP $(inc_path)

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
c_sources_clst = \
	src/cas_lab_Stand_test.cpp \
	src/cas_lab_StandController.cpp \
	src/deltaDRV_modbus_HandShake.cpp \
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
obj_tmp_clst = $(subst $(src_path), $(obj_path), $(c_sources_clst))
obj_clst     = $(patsubst %.cpp, %.o, $(obj_tmp_clst))

############################################################################
#	dependency file
######################################
dep_wise4060 = $(patsubst %.o, %.d, $(obj_wise4060))
dep_deltaDRV = $(patsubst %.o, %.d, $(obj_deltaDRV))
dep_clss = $(patsubst %.o, %.d, $(obj_clss))
dep_clst = $(patsubst %.o, %.d, $(obj_clst))

############################################################################
# default action: build all
######################################
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: wise4060 deltaDRV clss clst

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

clst: $(target_clst)
	@echo "target $< complete"
$(target_clst): $(obj_clst)
	g++ $^ -o $@ $(libs)

############################################################################
# build the application
#######################################
-include $(dep_wise4060)
-include $(dep_deltaDRV)
-include $(dep_clss)
-include $(dep_clst)
${obj_path}%.o: ${src_path}%.cpp Makefile
	g++ $(CFLAGS) -c $< -o $@


############################################################################
# .PHONY
#######################################
.PHONY: clean
clean:
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
