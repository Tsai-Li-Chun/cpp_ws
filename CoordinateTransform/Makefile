# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：robot CoordinateTransform project
# ------------------------------------------------


############################################################################
#	target
######################################
target  = CoordinateTransform

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
CFLAGS = -std=c++11 -O0 -MMD -MP $(inc_path)

############################################################################
#	source code
######################################
c_sources = \
	src/test.cpp \
	src/MathTool.cpp \
	src/M5Manipulator.cpp \
	src/CoordinateTransformation.cpp

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
$(shell if [ ! -e 'build' ]; then mkdir -p build; fi)
all: $(target)
	@echo "target $< complete"
$(target): $(obj)
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
	rm -f *.o *.d $(target)
	rm -f $(obj_path)*.o $(obj_path)*.d
