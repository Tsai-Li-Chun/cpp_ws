# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：isPhoXiControlRunning
# ------------------------------------------------


############################################################################
#	target
######################################
target  = trigger_and_localization

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
# -I/opt/PhotoneoSDK/Localization/include/PhoXi_API/
inc_path = -Iinc/ \
		   -I/opt/Photoneo/PhoXiControl-1.11.1/API/include/ \
		   -I/opt/PhotoneoSDK/Localization/include/
# object file paths
obj_path = build/

#######################################
# link script & libraries
#######################################
# libraries
libs = -Wl,-rpath,/opt/Photoneo/PhoXiControl-1.11.1/API/lib:/opt/PhotoneoSDK/Localization/lib:/opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk:/opt/PhotoneoSDK/Localization/bin/3rdParty/gcc5.5.0:/opt/PhotoneoSDK/Localization/bin/3rdParty/Qt:/opt/PhotoneoSDK/Localization/bin/3rdParty/OpenSSL:/opt/PhotoneoSDK/Localization/bin/3rdParty/Keylok/lib:/opt/PhotoneoSDK/Localization/bin/3rdParty/Python:/opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV:/opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl:/opt/PhotoneoSDK/Localization/bin/3rdParty/YAML:/opt/PhotoneoSDK/Localization/bin/3rdParty/CUrl \
				  /opt/Photoneo/PhoXiControl-1.11.1/API/lib/libPhoXi_API_gcc9.3.0_Release.so \
				  /opt/PhotoneoSDK/Localization/lib/libPhoLocalization_SDK_gcc5.5.0_Release.so \
				  /opt/PhotoneoSDK/Localization/lib/libPhoXi_API_dynamic_gcc5.5.0_Release.so \
				  /opt/PhotoneoSDK/Localization/lib/libPhoLocalization_SDK_gcc5.5.0_Release.so.1.3.4 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkFiltersCore-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkFiltersExtraction-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/lib/libPhoLibrary_dynamic_Release.so \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/gcc5.5.0/libgcc_s.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkglew-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkpng-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Qt/libicui18n.so.56 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonSystem-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkIOPLY-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/gcc5.5.0/libstdc++.so.6 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenSSL/libcrypto.so.1.0.0 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Keylok/lib/libkfunc64.so \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkjpeg-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonCore-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkmetaio-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Qt/libicuuc.so.56 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Python/libpython2.7.so.1.0 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_calib3d.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Qt/libQt5Gui.so.5 \
				  /opt/PhotoneoSDK/Localization/lib/libPhoXi_API_dynamic_gcc5.5.0_Release.so.1.2.14 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkDICOMParser-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkIOImage-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkalglib-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonTransforms-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkFiltersStatistics-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkImagingCore-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_features.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkRenderingCore-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonMath-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkfreetype-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenSSL/libssl.so.1.0.0 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_registration.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_filters.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_common.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_imgcodecs.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_kdtree.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_sample_consensus.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonMisc-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkInteractionStyle-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_core.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/YAML/libyaml-cpp.so.0.6 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Qt/libQt5Core.so.5 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkRenderingOpenGL2-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_io.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkRenderingFreeType-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkIOLegacy-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtksys-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkIOGeometry-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/CUrl/libcurl.so \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_photo.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_io_ply.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkFiltersGeneral-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_octree.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkFiltersGeometry-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtktiff-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonColor-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Pcl/libpcl_search.so.1.8 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkImagingFourier-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonDataModel-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_flann.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkzlib-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_features2d.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonComputationalGeometry-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkCommonExecutionModel-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkImagingHybrid-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkIOCore-7.0.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/gcc5.5.0/libgomp.so.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_imgproc.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Qt/libicudata.so.56 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/OpenCV/libopencv_highgui.so.3.1 \
				  /opt/PhotoneoSDK/Localization/bin/3rdParty/Vtk/libvtkFiltersSources-7.0.so.1 -lrt

############################################################################
#	compile gcc flags
#######################################
# Generate dependency information
CFLAGS = -std=c++11 -O0 -MMD -MP $(inc_path)

############################################################################
#	source code
######################################
c_sources = \
	src/trigger_and_localization.cpp \

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
