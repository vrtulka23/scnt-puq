#!/usr/bin/env bash

set -e

. settings.env
DIR_ROOT=$(pwd)

function clean_code {
    if [[ -d $DIR_BUILD ]]; then
	    rm -r $DIR_BUILD
    fi
}

function build_code {    
    if [[ ! -d $DIR_BUILD ]]; then
	    mkdir $DIR_BUILD
    fi
    cmake -DCODE_VERSION="${CODE_VERSION}" -B $DIR_BUILD
    cd $DIR_BUILD
    make -j 10
    cd $DIR_ROOT
}

function install_code {
    cd $DIR_BUILD
    make install
    cd $DIR_ROOT
}

function test_code {
    if [[ "${1}" == "" ]]; then
	    ./$DIR_BUILD/TestSolver
    else
        ./$DIR_BUILD/TestSolver --gtest_filter="${1}"
    fi
}

function run_code {
    ./$DIR_BUILD/$1
}

function grep_code {
    if [[ "${1}" != "" ]]; then
	    grep -Inr $1 ./src ./tests ./exec
    fi
}

function create_assets {
    if [[ ! -d $DIR_ASSETS ]]; then
	mkdir $DIR_ASSETS
    fi
    DIR_ROOT=$(pwd)
    # create a source code archive file with all submodules
    ARCHIVE_NAME=puq-$CODE_VERSION
    ARCHIVE_FILE=$DIR_ROOT/$DIR_ASSETS/$ARCHIVE_NAME.tar.gz
    git archive -o $ARCHIVE_FILE --prefix=$ARCHIVE_NAME/ HEAD
    tar -xzf $ARCHIVE_FILE -C $DIR_ROOT/$DIR_ASSETS
    for SUBMODULE in $(git config --file .gitmodules --get-regexp path | awk '{ print $2 }')
    do
	cd $SUBMODULE
	git archive -o $ARCHIVE_FILE --prefix=$ARCHIVE_NAME/$SUBMODULE/ HEAD
	tar -xzf $ARCHIVE_FILE -C $DIR_ROOT/$DIR_ASSETS
	cd $DIR_ROOT
    done
    cd $DIR_ROOT/$DIR_ASSETS
    tar -czf $ARCHIVE_FILE $ARCHIVE_NAME
    rm -r $ARCHIVE_NAME
    cd $DIR_ROOT
}

function show_help {
    echo "Physical Units and Quantities"
    echo ""
    echo "Options:"
    echo " -c|--clean          clean the build directory"
    echo " -b|--build          build code"
    echo " -i|--install        install puq"
    echo " -r|--run <example>  run an example code"
    echo " -t|--test [<test>]  run all/specific tests"
    echo " -g|--grep <expr>    find expression in a code"
    echo " -a|--assets         create assets"
    echo " -h|--help           show this help"
    echo ""
    echo "Examples:"
    echo "./setup.sh -c -b               clean and build the code"
    echo "./setup.sh -r DefaultSolver    run DefaultSolver example"
    echo "./setup.sh -t Output.Data      run 'Output.Data' test"
    echo "./setup.sh -g class            find 'class' in the code or test"
}

if [[ "${1}" == "" ]]; then
    show_help
fi
while [[ $# -gt 0 ]]; do
    case $1 in
	-c|--clean)
	    clean_code; shift;;
	-b|--build)
	    build_code; shift;;
	-i|--install)
	    install_code; shift;;
	-r|--run)
	    run_code $2; shift; shift;;
	-t|--test)
	    test_code $2; shift; shift;;
	-g|--grep)
	    grep_code $2; shift; shift;;
	-a|--assets)
	    create_assets; shift;;
	-h|--help)
	    show_help; shift;;
	-*|--*)
	    show_help; exit 1;;
	*)
	    show_help; shift;;
    esac
done
