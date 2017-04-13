#/bin/bash

# ------------------------------------------------------------------------------#
# TI Energia MoteIST board
# This script will install the MoteIST board in the TI Energia. This is done by
# the use of the Energia sketchbook directory.
#
# ** Please set variables bellow before executing this script. **
#
# More info:
# http://leme.tagus.ist.utl.pt/gems/PmWiki/index.php/Projects/MoteIST
# https://github.com/pedrogameiro/energia_moteist
# http://www.energia.nu/
# ------------------------------------------------------------------------------#


echo 'TI Energia instalation directory:' >&2
echo '[$HOME/.opt/energia]>> ' >&2
read ENERGIA_INSTALL_DIR
[ "" = "${ENERGIA_INSTALL_DIR}" ] && ENERGIA_INSTALL_DIR=$HOME/.opt/energia

echo 'Your sketchbook directory. Can be configured in the File->Preferences TI Energia Menu:' >&2
echo '[$HOME/Energia]>> '
read SKETCHBOOK_DIR
[ "" = "${SKETCHBOOK_DIR}" ] && SKETCHBOOK_DIR=$HOME/Energia

#***********************************************************************#

# The MRM memory mapping file. The MRM will *not* work unless 
# this file is copied into the TI Energia install directory.
MEMORY_X_DIR="hardware/tools/msp430/msp430/lib/ldscripts/msp430f5438a"
MEMORY_X="$MEMORY_X_DIR/memory.x"
VERSION=v18

# Download 
cd "$SKETCHBOOK_DIR"
wget -O - https://github.com/pedrogameiro/energia_moteist/archive/"$VERSION".tar.gz | tar xzf -
mv -f energia_moteist-"$VERSION"/{*,.??*} "$PWD"
rmdir energia_moteist-"$VERSION"

cp -v mrm_memory.x "$ENERGIA_INSTALL_DIR"/"$MEMORY_X"
cp -v lib/* "$ENERGIA_INSTALL_DIR"/lib/

