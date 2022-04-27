################################################################################
#
# Copyright (c) 2017 Mbaas Development GmbH. All rights reserved.
#
################################################################################

APPLANGA_FRAMEWORK_DIR=$0

get_script_dir () {

     SOURCE="${BASH_SOURCE[0]}"
     # While $SOURCE is a symlink, resolve it
     while [ -h "$SOURCE" ]; do
          APPLANGA_FRAMEWORK_DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
          SOURCE="$( readlink "$SOURCE" )"
          # If $SOURCE was a relative symlink (so no "/" as prefix, need to resolve it relative to the symlink base directory
          [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
     done
     APPLANGA_FRAMEWORK_DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
}

get_script_dir

echo "Applanga SDK Path: $APPLANGA_FRAMEWORK_DIR"
APPLANGA_FRAMEWORK_BUNDLEID=$(plutil -extract CFBundleShortVersionString xml1 -o - $APPLANGA_FRAMEWORK_DIR/Info.plist | sed -n "s/.*<string>\(.*\)<\/string>.*/\1/p")
echo "Applanga SDK Version: $APPLANGA_FRAMEWORK_BUNDLEID"

# if it's a xcframework project we retrieve the bundle id differently
if [ "$APPLANGA_FRAMEWORK_BUNDLEID" == "" ] || [ "${APPLANGA_FRAMEWORK_DIR: -11}" == "xcframework" ]; then
     APPLANGA_FRAMEWORK_BUNDLEID=$(plutil -extract CFBundleShortVersionString xml1 -o - $APPLANGA_FRAMEWORK_DIR/ios-arm64_armv7/Applanga.framework/Info.plist | sed -n "s/.*<string>\(.*\)<\/string>.*/\1/p")
fi

# check for python

PYTHON_CMD=
if [ -x "$(command -v python3)" ]; then
    # python found
    PYTHON_CMD=python3
elif [ -x "$(command -v python)" ]; then
    #python3 found
    PYTHON_CMD=python
elif [ -x "$(command -v python2)" ]; then
    # python2 found
    PYTHON_CMD=python2
else
    # python and python3 not found
    echo ""
    echo "ERROR:"
    echo "Python not found. Please install python 2.7 or python 3.5 or higher on your system."
    exit 1
fi
PYTHON_VERSION_STRING=$($PYTHON_CMD --version 2>&1)
# print python cmd and version
echo "$PYTHON_CMD --version: $PYTHON_VERSION_STRING"


PYTHON_MAJOR_VERSION=$($PYTHON_CMD -c"import sys; print(sys.version_info.major)")
if [ ! $PYTHON_MAJOR_VERSION -eq 2 ] && [ ! $PYTHON_MAJOR_VERSION -eq 3 ]; then
    echo ""
    echo "ERROR:"
    echo "Python version not supported. Please install python 2.7 or python 3.5 or higher on your system."
    exit 1
fi

APPLANGA_DOWNLOAD_SCRIPTPATH=/tmp/Applanga-Scripts/${APPLANGA_FRAMEWORK_BUNDLEID}/settingsfile_update.py
if [ ! -f "${APPLANGA_DOWNLOAD_SCRIPTPATH}" ]; then
     mkdir -p /tmp/Applanga-Scripts/${APPLANGA_FRAMEWORK_BUNDLEID}
     curl -o "${APPLANGA_DOWNLOAD_SCRIPTPATH}" "https://raw.githubusercontent.com/applanga/sdk-ios/${APPLANGA_FRAMEWORK_BUNDLEID}/settingsfile_update.py"
fi

$PYTHON_CMD "${APPLANGA_DOWNLOAD_SCRIPTPATH}" "$1"