#!/bin/sh
# finder.sh - Finds files in a directory containing a search string
# Assignment 1 script

filesdir=$1
searchstr=$2

if [ $# -lt 2 ]; then
    echo "ERROR: Missing parameters."
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "ERROR: $filesdir is not a directory."
    exit 1
fi

numfiles=$(find "$filesdir" -type f | wc -l)
nummatches=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

echo "The number of files are ${numfiles} and the number of matching lines are ${nummatches}"
