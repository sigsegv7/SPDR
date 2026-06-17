#!/bin/sh
#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause
#
# Description: Top-level OS build script
# Author: 	   Chloe M.
#

set -e

PROJECT_ROOT=$(pwd)
MAKE=make
DEPCHECK_PATH=$PROJECT_ROOT/artifacts/.depcheck
FONT_PATH=private/$SERVICE_PACK/base/fonts/Cyr_a8x8.psf
KERNEL_PATH=artifacts/stoskrnl.sys

#
# Check if a list of programs are installed on the system
#
# <@>: List of programs to check
#
check_deps() {
    for dep in $@; do
        printf "Checking if $dep is installed... "
        which $dep &>/dev/null
        if [ $? -ne 0 ]; then
            echo "no"
            echo "fatal: Please install $dep!"
            exit 1
        fi

        echo "yes"
    done
}

#
# Verify the build environment
#
build_verify() {
    if [ -z "${SPDR_ENV_EXPORTED}" ]
    then
        echo "fatal: Please run '. devel/build.env'"
        exit 1
    fi

    if [ -z "${SERVICE_PACK}" ]
    then
        echo "fatal: SERVICE_PACK not defined"
        echo "fatal: Please run '. devel/build.env'"
        exit 1
    fi

    # Make sure everything is installed
    if [ ! -f $DEPCHECK_PATH ]
    then
        check_deps  \
            git     \
            make    \
            gcc     \
            xorriso \
            rsync

        touch $DEPCHECK_PATH
    fi
}

#
# Begin the build process
#
build() {
    mkdir -p $BASE_DIR/system64

    # Build the host utilties
    pushd private/$SERVICE_PACK/host; \
        $MAKE
    popd

    pushd private/$SERVICE_PACK/spkg; \
        $MAKE
    popd

    pushd private/$SERVICE_PACK/stos; \
        $MAKE
    popd

    pushd private/$SERVICE_PACK/boot/; \
        $MAKE
    popd

    pushd private/$SERVICE_PACK/crt/;  \
        $MAKE
    popd

    pushd private/$SERVICE_PACK/ssm/;  \
        $MAKE
    popd
}

mkdir -p artifacts/

build_verify
build
