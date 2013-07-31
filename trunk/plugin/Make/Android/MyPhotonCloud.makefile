#################################################################
#   ShiVa Extension Plugin Makefile for Android
#################################################################

ANDROID_NDK_ROOT    = C:/Games/sdks/AndroidSDK
TEMP_DIR       		= ../../Temp/Android
TEMP_DIR_ARM5       = $(TEMP_DIR)/arm5
TEMP_DIR_ARM7       = $(TEMP_DIR)/arm7
TEMP_DIR_X86        = $(TEMP_DIR)/x86
SRCROOT             = ../../Sources
S3DXROOT            = ../../Sources/S3DX
BUILT_PRODUCTS_DIR  = ../../Contents/Android
PRODUCT_NAME_ARM5   = MyPhotonCloud_Android.a
PRODUCT_NAME_ARM7   = MyPhotonCloud_Android_arm_v7a.a
PRODUCT_NAME_X86    = MyPhotonCloud_Android_x86_32.a

#################################################################
#  User data
#
USER_INCLUDE_PATH	= 
USER_LIBRARIES		= 
USER_FLAGS			= 

#################################################################
SOURCES				= Plugin.cpp myPhotonCloud.cpp 

#################################################################
#  Compiler executables
#
CC_ARM5      		= "$(ANDROID_NDK_ROOT)/toolchains/arm-linux-androideabi-4.6/prebuilt/windows/bin/arm-linux-androideabi-gcc"
CPP_ARM5     		= "$(ANDROID_NDK_ROOT)/toolchains/arm-linux-androideabi-4.6/prebuilt/windows/bin/arm-linux-androideabi-g++"
AR_ARM5  			= "$(ANDROID_NDK_ROOT)/toolchains/arm-linux-androideabi-4.6/prebuilt/windows/bin/arm-linux-androideabi-ar"

CC_ARM7      		= $(CC_ARM5)
CPP_ARM7     		= $(CPP_ARM5)
AR_ARM7  			= $(AR_ARM5)

CC_X86      		= "$(ANDROID_NDK_ROOT)/toolchains/x86-4.6/prebuilt/windows/bin/i686-linux-android-gcc"
CPP_X86     		= "$(ANDROID_NDK_ROOT)/toolchains/x86-4.6/prebuilt/windows/bin/i686-linux-android-g++"
AR_X86  			= "$(ANDROID_NDK_ROOT)/toolchains/x86-4.6/prebuilt/windows/bin/i686-linux-android-ar"

####################################################################"
#  Includes
#
SYSROOT_ARM5        = $(ANDROID_NDK_ROOT)/platforms/android-5/arch-arm
SYSROOT_ARM7        = $(SYSROOT_ARM5)
SYSROOT_X86         = $(ANDROID_NDK_ROOT)/platforms/android-9/arch-x86
SYSTEM_INCLUDES		= 

####################################################################"
#  Compiler flags
#
CFLAGS_Arch_ARM5 	= -march=armv5te -msoft-float
CFLAGS_Arch_ARM7 	= -march=armv7-a -mfloat-abi=softfp -mfpu=vfp
CFLAGS_Arch_X86 	= 
CFLAGS_Common		= -Os -Wno-unknown-pragmas -fPIC -fsigned-char -fno-strict-aliasing -fno-short-enums -fno-exceptions -D__ANDROID__ -DANDROID_NDK -DANDROID -DRELEASE -D_GNU_SOURCE -DHAVE_STDINT_H
CFLAGS_ARM5      	= --sysroot="$(SYSROOT_ARM5)" $(CFLAGS_Arch_ARM5) $(CFLAGS_Common) $(SYSTEM_INCLUDES) -I"$(SRCROOT)" -I$(SRCROOT)/Android -I$(S3DXROOT) -I"$(SYSROOT_ARM5)/usr/bin"
CFLAGS_ARM7      	= --sysroot="$(SYSROOT_ARM7)" $(CFLAGS_Arch_ARM7) $(CFLAGS_Common) $(SYSTEM_INCLUDES) -I"$(SRCROOT)" -I$(SRCROOT)/Android -I$(S3DXROOT) -I"$(SYSROOT_ARM7)/usr/bin"
CFLAGS_X86       	= --sysroot="$(SYSROOT_X86)"  $(CFLAGS_Arch_X86)  $(CFLAGS_Common) $(SYSTEM_INCLUDES) -I"$(SRCROOT)" -I$(SRCROOT)/Android -I$(S3DXROOT) -I"$(SYSROOT_X86)/usr/bin"
CPPFLAGS    		= -fno-rtti 


####################################################################"
#  Objects
#
OBJECTS  			= \
	$(patsubst %.c,%.o,$(filter %.c,$(SOURCES))) \
	$(patsubst %.cc,%.o,$(filter %.cc,$(SOURCES))) \
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES)))

OBJECTS_ABS_ARM5	= $(addprefix $(TEMP_DIR_ARM5)/,$(OBJECTS))
OBJECTS_ABS_ARM7	= $(addprefix $(TEMP_DIR_ARM7)/,$(OBJECTS))
OBJECTS_ABS_X86 	= $(addprefix $(TEMP_DIR_X86)/,$(OBJECTS))
PRODUCT_ABS_ARM5    = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME_ARM5)
PRODUCT_ABS_ARM7    = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME_ARM7)
PRODUCT_ABS_X86     = $(BUILT_PRODUCTS_DIR)/$(PRODUCT_NAME_X86)

####################################################################"
#  Rules
#

$(TEMP_DIR_ARM5)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC_ARM5) $(CFLAGS_ARM5) -c $< -o $@

$(TEMP_DIR_ARM5)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_ARM5) $(CFLAGS_ARM5) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_ARM7)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC_ARM7) $(CFLAGS_ARM7) -c $< -o $@

$(TEMP_DIR_ARM7)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_ARM7) $(CFLAGS_ARM7) $(CPPFLAGS) -c $< -o $@

$(TEMP_DIR_X86)/%.o: $(SRCROOT)/%.c
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CC_X86) $(CFLAGS_X86) -c $< -o $@

$(TEMP_DIR_X86)/%.o: $(SRCROOT)/%.cpp
	@mkdir -p `dirname $@`
	@echo Compiling $<
	@$(CPP_X86) $(CFLAGS_X86) $(CPPFLAGS) -c $< -o $@

####################################################################"
#  Targets
#
all: $(PRODUCT_ABS_ARM5) $(PRODUCT_ABS_ARM7) $(PRODUCT_ABS_X86) 

$(PRODUCT_ABS_ARM5): $(OBJECTS_ABS_ARM5)
	@echo Creating ARM5 archive
	@mkdir -p $(BUILT_PRODUCTS_DIR)
	@$(AR_ARM5) rcs $(PRODUCT_ABS_ARM5) $(OBJECTS_ABS_ARM5)

$(PRODUCT_ABS_ARM7): $(OBJECTS_ABS_ARM7)
	@echo Creating ARM7 archive
	@mkdir -p $(BUILT_PRODUCTS_DIR)
	@$(AR_ARM7) rcs $(PRODUCT_ABS_ARM7) $(OBJECTS_ABS_ARM7)

$(PRODUCT_ABS_X86): $(OBJECTS_ABS_X86)
	@echo Creating X86 archive
	@mkdir -p $(BUILT_PRODUCTS_DIR)
	@$(AR_X86) rcs $(PRODUCT_ABS_X86) $(OBJECTS_ABS_X86)

clean:
	@echo Cleaning
	@rm -f $(PRODUCT_ABS_ARM5) $(OBJECTS_ABS_ARM5) $(PRODUCT_ABS_ARM7) $(OBJECTS_ABS_ARM7) $(PRODUCT_ABS_X86) $(OBJECTS_ABS_X86)

####################################################################"
