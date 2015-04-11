#!/bin/bash

PATCHES=(dwm-6.1-ignorewindows.diff dwm-6.1-push.diff  dwm-6.0-bstack.diff dwm-6.1-bottommargin.diff)
PATCHES_DIR="../dwm-patches"
CONFIG_DIR="../dwm-config"

if [[ -d "dwm" ]] ; then
 echo "Cleaning and updating to the last revision"
 cd dwm

 git reset HEAD --hard

 git clean -fd

 git pull

else
    echo 'Downloading latest dwm from git'

    git clone git://git.suckless.org/dwm
    
    rc=$?
    if [[ $rc != 0 ]] ; then
	echo 'Git failed!'
	exit 1
    fi
    
    cd dwm
fi

if [[ ! -d "$PATCHES_DIR" ]] ; then
 echo "dwm patches directory doesn't exists!"
 exit 1;
fi

echo 'Applying patches'

for patch in ${PATCHES[*]}; do
    echo "-----------Applying patch '$patch'"
    patch -p1 < "$PATCHES_DIR/$patch" 
    rc=$?
    if [[ $rc != 0 ]] ; then
	echo "Applying '$patch' failed!"
	exit 1
    fi
    
done

if [[ ! -d "$CONFIG_DIR" ]] ; then
 echo "patches directory doesn't exists!"
 exit 1;
fi

echo "Copying config files.."
cp "$CONFIG_DIR"/* ./
rc=$?
if [[ $rc != 0 ]] ; then
    echo "An error while copying files from '$CONFIG_DIR' has occured!"
    exit 1
fi

echo "Done!"

exit 0
