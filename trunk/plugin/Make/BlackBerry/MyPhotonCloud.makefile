#################################################################
#   ShiVa Extension Plugin Makefile for BlackBerry
#################################################################

TEMP_DIR       		= ../../Temp/BlackBerry
SRCROOT             = ../../Sources
S3DXROOT            = ../../Sources/S3DX
BUILT_PRODUCTS_DIR  = ../../Contents/BlackBerry
PRODUCT_NAME        = MyPhotonCloud_BlackBerry.a

#################################################################

export QNX_TARGET			= C:/Games/sdks/BlackBerry/bbk_2_0_1/target/qnx6
export QNX_TARGET_OVERRIDE	= C:/Games/sdks/BlackBerry/bbk_2_0_1/target/target-override
export QNX_HOST				= C:/Games/sdks/BlackBerry/bbk_2_0_1/host/win32/x86

#################################################################
SOURCES				= Plugin.cpp myPhotonCloud.cpp 

#################################################################
#  Compiler executables
#
CC      			= $(QNX_HOST)/usr/bin/qcc -Vgcc_ntoarmv7
CPP     			= $(QNX_HOST)/usr/bin/qcc -Vgcc_ntoarmv7
AR                  = $(QNX_HOST)/usr/bin/ntoarmv7-ar.exe
LD					= $(CPP)

####################################################################"
#  Compiler flags
#
USER_INCLUDE_PATH	= 
USER_LIBRARIES		= 
USER_FLAGS			= 
COMMONFLAGS			= -DNDEBUG -O2 -g0 -D__BLACKBERRY__ -D_QNX_SOURCE -DHAVE_STDINT_H -DHAVE_ALLOCA_H -W -fPIC -fno-strict-aliasing -fstack-protector-all -D_FORTIFY_SOURCE=2 -EL -DVARIANT_v7 -DVARIANT_le -DBUILDENV_qss $(USER_FLAGS) -I$(SRCROOT) -I$(SRCROOT)/BlackBerry -I$(S3DXROOT) -I$(QNX_TARGET)/usr/include -I$(QNX_TARGET)/usr/include/cpp/c -I$(QNX_TARGET_OVERRIDE)/usr/include $(USER_INCLUDE_PATH)
CFLAGS      		= $(COMMONFLAGS)
CPPFLAGS    		= $(COMMONFLAGS) -fno-rtti -fno-exceptions
LDFLAGS    			= $(USER_LIBRARIES)
ARFLAGS    			= $(USER_LIBRARIES)

####################################################################"
#  Objects
#
OBJECTS  			= \
	$(patsubst %.c,%.o,$(filter %.c,$(SOURCES))) \
	$(patsubst %.cc,%.o,$(filter %.cc,$(SOURCES))) \
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES)))

OBJECTS_ABS			= $(addprefix $(TEMP_DIR)/,$(OBJECTS))
PRODUCT_ABS         = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME)

####################################################################"
#  Rules
#

$(TEMP_DIR)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC) $(COMMONFLAGS) $(CFLAGS) -c $< -o $@

$(TEMP_DIR)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP) $(COMMONFLAGS) $(CPPFLAGS) -c $< -o $@

####################################################################"
#  Targets
#
all: $(PRODUCT_ABS) 

$(PRODUCT_ABS): $(OBJECTS_ABS)
	@mkdir -p $(BUILT_PRODUCTS_DIR)
	@echo Creating archive
	@$(AR) rcs $(PRODUCT_ABS) $(OBJECTS_ABS) $(ARFLAGS) 

clean:
	@echo Cleaning
	@rm -f $(PRODUCT_ABS) $(OBJECTS_ABS)

####################################################################"
