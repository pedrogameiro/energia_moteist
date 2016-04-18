######################################
# Board specific
ARCH = msp430
MCU = msp430f5438a
MCU_FLAG = -mmcu=$(MCU)
F_CPU = 25000000L
FLASH_SIZE = 130048
UPLOAD_COMMAND = $(MSPDEBUG) $(VERBOSE_UPLOAD) tilib --force-reset "prog build/$(SKETCH_NAME).bin"
######################################
