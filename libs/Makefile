# libs Makefile
include ../Makefile.common
LIBS+=libstm32stdlib.a
CFLAGSlib+=-c
all: libs
libs: $(LIBS)
$(LIBS):
	@echo -n "Building $@ ..."
	@cd $(STMLIB)/CMSIS && \
		$(CC) $(CFLAGSlib) \
			system_stm32f10x.c
	@cd $(STMLIB)/src && \
		$(CC) $(CFLAGSlib) \
			-D"assert_param(expr)=((void)0)" \
			-I../../CMSIS/Include \
			-I../../CMSIS/Device/ST/STM32F4xx/Include \
			-I../inc \
			*.c
# @cd $(STMLIB)/STM32_USB-FS-Device_Driver/src && \
# $(CC) $(CFLAGSlib) \
# -D"assert_param(expr)=((void)0)" \
# -I../../CMSIS/Include \
# -I../../CMSIS/Device/ST/STM32F10x/Include \
# -I../inc \
# *.c
	@$(AR) cr $(LIBDIR)/$@ \
		$(STMLIB)/CMSIS/system_stm32f10x.o \
		$(STMLIB)/src/*.o 
# $(STMLIB)/STM32_USB-FS-Device_Driver/src/*.o
	@echo "done."
.PHONY: libs clean tshow
clean:
	rm -f $(STMLIB)/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.o
	rm -f $(STMLIB)/STM32F4xx_StdPeriph_Driver/src/*.o
#	rm -f $(STMLIB)/STM32_USB-FS-Device_Driver/src/*.o
	rm -f $(LIBS)
tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"
