#/bin/bash

# ------------------------------------------------------------------------------#
# TI Energia MoteIST board
# This script will install the MoteIST board in the TI Energia. This is done by
# the use of the Energia sketchbook directory.
#
# More info:
# http://leme.tagus.ist.utl.pt/gems/PmWiki/index.php/Projects/MoteIST
# https://github.com/pedrogameiro/energia_moteist
# http://www.energia.nu/
# ------------------------------------------------------------------------------#


# ************************* PLEASE EDIT ********************************#
# The directory where TI Energia is installed. Please change
# the value of this variable to your specific installation directory.
ENERGIA_INSTALL_DIR=          
# Your sketchbook directory. Defaults to $HOME/sketchbook, and can be 
# configured in the File->Preferences TI Energia Menu.
SKETCHBOOK_DIR=
#***********************************************************************#

# The MRM memory mapping file. The MRM will *not* work unless 
# this file is copied into the TI Energia install directory.
MEMORY_X_DIR="hardware/tools/msp430/msp430/lib/ldscripts/msp430f5438a"
MEMORY_X="$MEMORY_X_DIR/memory.x"

cd "$SKETCHBOOK_DIR"
git clone https://github.com/pedrogameiro/energia_moteist "$PWD"
cp -v mrm_memory.x "$ENERGIA_INSTALL_DIR"/"$MEMORY_X"
