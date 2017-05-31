# path to snesdev root directory (for emulators, devkitsnes, PVSNESLIB)
export DEVKITSNES := /f/snesdev/trunk
#export DEVKITSNES := /z/vboxshared/snesdev/trunk

# path to devkitsnes root directory for compiler
export DEVKIT65XX := /f/snesdev//trunk/devkitsnes
#export DEVKIT65XX := /z/vboxshared/snesdev//trunk/devkitsnes

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKIT65XX)),)
$(error "Please set DEVKIT65XX in your environment. export DEVKIT65XX=<path to>devkit65XX")
endif

include $(DEVKIT65XX)/snes_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(shell basename $(CURDIR))
SOURCES		:=	.

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS	+=	$(INCLUDE) 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(PVSNESLIB)
LIBOBJS +:=	
 
export OUTPUT	:=	$(CURDIR)/$(TARGET)
 
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.asm)))

#---------------------------------------------------------------------------------
# Name of text file containing build number.
BUILD_NUMBER_FILE=buildnumber.txt
BUILD_INCLUD_FILE=buildnum.h
BUILD_MAIN_FILE=pgr2017intro.c
 
#---------------------------------------------------------------------------------

export OFILES	:=	$(BINFILES:.bin=.obj) $(CFILES:.c=.obj) $(SFILES:.asm=.obj)
 
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

GTITLE 		:= -ht"$(TARGET)"
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
all	:	bitmaps $(OUTPUT).sfc
	$(SNTOOLS) -hi! $(GTITLE) $(TARGET).sfc
	sed 's/://' <$(TARGET).sym >$(TARGET).tmp
	#cp $(TARGET).tmp $(TARGET)$$(date +'%y%m%d')"b"$$(cat $(BUILD_NUMBER_FILE))_ntsc.sym
	#mv $(TARGET).tmp $(TARGET)$$(date +'%y%m%d')"b"$$(cat $(BUILD_NUMBER_FILE))_pal.sym
	#cp $(TARGET).sfc $(TARGET)$$(date +'%y%m%d')"b"$$(cat $(BUILD_NUMBER_FILE))_ntsc.sfc
	cp $(TARGET).tmp $(TARGET)$$(date +'%y%m%d')_ntsc.sym
	mv $(TARGET).tmp $(TARGET)$$(date +'%y%m%d')_pal.sym
	cp $(TARGET).sfc $(TARGET)$$(date +'%y%m%d')_ntsc.sfc
	$(SNTOOLS) -hi! -hS! $(GTITLE) -hc03 $(TARGET).sfc
	#mv $(TARGET).sfc $(TARGET)$$(date +'%y%m%d')"b"$$(cat $(BUILD_NUMBER_FILE))_pal.sfc
	mv $(TARGET).sfc $(TARGET)$$(date +'%y%m%d')_pal.sfc
	@echo Generate new build number ... $(notdir $@)
	@if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi
	@echo $$(($$(cat $(BUILD_NUMBER_FILE)) + 1)) > $(BUILD_NUMBER_FILE)
	@echo "#define BUILDID \""$$(date +'%y%m%d')"b"$$(cat $(BUILD_NUMBER_FILE))\" > $(BUILD_INCLUD_FILE)
	@touch $(BUILD_MAIN_FILE)
	
clean:
	@echo clean ...
	@rm -f $(OFILES) $(TARGET).sfc  gfxs/*.pic gfxs/*.pal gfxs/*.map

#---------------------------------------------------------------------------------
gfxs/fonts.pic: gfxs/fonts.bmp
	@echo convert fonts with no tile reduction ... $(notdir $@)
	$(GFXCONV) -n -gs8 -po16 -pc16 -pe0 -mR! -m! $<
	
gfxs/stars.pic: gfxs/stars.bmp
	@echo convert starfield bitmap to graphics... $(notdir $@)
	$(GFXCONV) -po16 -pc16 -n -gs8 -pe1 -m $<

gfxs/logo.pic: gfxs/logo.bmp
	@echo convert logo bitmap to graphics with high priority ... $(notdir $@)
	$(GFXCONV) -po32 -pc16 -n -gs8 -pe2 -mp -m $<

gfxs/sprites.pic: gfxs/sprites.bmp
	@echo convert sprite 32px bitmap to graphics... $(notdir $@)
	$(GFXCONV) -po32 -gs32 -pc16 -pe0 -n $<

gfxs/firstone.pic: gfxs/firstone.bmp
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -po16 -pc16 -n -gs8 -pe2 -m $<

gfxs/lastone.pic: gfxs/lastone.bmp
	@echo first meeting bitmap ... $(notdir $@)
	$(GFXCONV) -po32 -pc16 -n -gs8 -pe2 -m $<
	
bitmaps : gfxs/fonts.pic gfxs/stars.pic gfxs/logo.pic gfxs/sprites.pic gfxs/firstone.pic gfxs/lastone.pic

#---------------------------------------------------------------------------------
$(OUTPUT).sfc	: $(OFILES)
