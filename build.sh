#!/bin/sh

ShowUsage()
{
    echo "Usage: $0 [OPT]"
    echo "  OPT: -r   Rebuild all demos!"
    echo "       -c   Clean all demos!"
    echo "       -h   Show this usage!"
}

Clean()
{
    echo "Clean All"
    [ -d "./build" ] && rm -rf build
    rm -f demo_*
}

Build()
{
    echo "Building..."
    [ ! -d "./build" ] && mkdir build
    cd build
    cmake ..
    [ -f Makefile ] && make && echo "Done!"
    echo
    echo "------ Demos ------"
    ls -l ../demo_*
}

if [ $# -gt 1 ]; then
    ShowUsage
    exit 0
fi

if [ $# -eq 1 ]; then
    case $1 in
        -r)
            Clean
            Build
            ;;
        -c)
            Clean
            ;;
        -h)
            ShowUsage
            ;;
        *)
            ShowUsage
            ;;
    esac
    exit 0
fi

Build
