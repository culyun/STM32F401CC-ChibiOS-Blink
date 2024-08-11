# List of all the board related files.
BOARDSRC = ./STM32F411CE_BLACKPILL/board.c

# Required include directories
BOARDINC = ./STM32F411CE_BLACKPILL

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
