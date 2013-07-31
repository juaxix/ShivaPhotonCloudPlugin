#################################################################
#   ShiVa Extension Plugin Makefile for Flash
#################################################################

TEMP_DIR       		= ../../Temp/Flash
SRCROOT             = ../../Sources
S3DXROOT            = ../../Sources/S3DX
FLEXROOT            = @@FLEXRoot@@
SCC_HOST            = @@SCCHost@@
SCC_TARGET          = @@SCCTarget@@
BUILT_PRODUCTS_DIR  = ../../Contents/Flash
PRODUCT_TITLE  		= MyPlugin_Flash
PRODUCT_NAME        = $(PRODUCT_TITLE).swc

#################################################################
SOURCES             = Flash/Bridge.cpp Plugin.cpp

#################################################################
#  Compiler executables
#
CC                  = $(SCC_HOST)/usr/bin/llvm-gcc.exe
CPP                 = $(SCC_HOST)/usr/bin/llvm-g++.exe
LLVMLINK            = $(SCC_HOST)/usr/bin/llvm-link.exe
LLC                 = $(SCC_HOST)/usr/bin/llc.exe
COMPC               = $(FLEXROOT)/bin/compc.exe
SED                 = sed.exe

####################################################################"
#  Compiler flags
#
LLVMFLAGS           = -U_WIN32 -UWIN32 -UWINNT -U__WINNT__ -U__WIN32 -U__WIN32__ -U__MINGW32__ -U__i386 -U_X86_ -Ui386 -U__i486__ -U__i386__ -U__i486 -emit-llvm -fomit-frame-pointer -fno-unwind-tables -ffunction-sections -fno-builtin -Wall -Wno-unknown-pragmas -Wno-unused -Wno-strict-aliasing -m32 -U__cdecl 
COMMONFLAGS         = $(LLVMFLAGS) -Os -Wno-unknown-pragmas -fsigned-char -fno-exceptions -D__FLASH__ -DS3DX_DISCRETE_STRING_POOL -D_GNU_SOURCE -DHAVE_STDINT_H -I$(SRCROOT)/Flash -I$(S3DXROOT)
CFLAGS              = -std=c99
CPPFLAGS            = -std=c++98 -fno-exceptions -fno-rtti
LLCFLAGS            = -march=AS3 -O3
LLVMLINKFLAGS       = $(SCC_TARGET)/lib/libc.bc
COMPCFLAGS    		= -debug=false -optimize -strict -external-library-path+=$(SCC_TARGET)/lib/librt.swc

####################################################################"
#  Objects
#
OBJECTS  			= \
	$(patsubst %.c,%.o,$(filter %.c,$(SOURCES))) \
	$(patsubst %.cc,%.o,$(filter %.cc,$(SOURCES))) \
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SOURCES)))

OBJECTS_ABS			= $(addprefix $(TEMP_DIR)/,$(OBJECTS))
BC_ABS				= $(TEMP_DIR)/$(PRODUCT_TITLE).bc
AS_ABS				= $(TEMP_DIR)/$(PRODUCT_TITLE).as
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
	@echo Converting to bytecode
	@$(LLVMLINK) $(OBJECTS_ABS) $(LLVMLINKFLAGS) -o $(BC_ABS)
	@echo Converting to AS3
	@$(LLC) $(LLCFLAGS) $(BC_ABS) -o $(AS_ABS)
	@$(SED) -i 's/GeneratedProgram/$(PRODUCT_TITLE)/g' $(AS_ABS)
	@echo Compiling AS3
	@$(COMPC) $(COMPCFLAGS) -include-sources $(AS_ABS) -output $(PRODUCT_ABS)


clean:
	@echo Cleaning
	@rm -f $(PRODUCT_ABS) $(OBJECTS_ABS) $(BC_ABS) $(AS_ABS)

####################################################################"
