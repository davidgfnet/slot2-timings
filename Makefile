# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS        ?= /opt/blocksds/core

# User config

NAME            := waitcnt-tool
GAME_TITLE      := WaitCNT testing tool
GAME_SUBTITLE   := davidgf
GAME_AUTHOR	    ?= davidgf.net

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile

