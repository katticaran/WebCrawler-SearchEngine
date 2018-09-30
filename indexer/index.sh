#!/bin/bash

DIR="../data/"
if [ "$#" -ne 2 ]; then
    echo "Invalid number of parameters"
echo "Usage: ./indexFileCompare.sh [file1] [file2]"
exit 1
fi

sort $DIR$1 > "$DIR""$1".sorted
sort $DIR$2 > "$DIR""$2".sorted
tr -d ' ' <"$DIR""$1".sorted >"$DIR""$1".trunc
tr -d ' ' <"$DIR""$2".sorted >"$DIR""$2".trunc

diff "$DIR""$1".trunc "$DIR""$2".trunc
if [ "$?" -ne 0 ]; then
    echo "Files are not Equivalent"
rm "$DIR""$1".sorted "$DIR""$2".sorted
rm "$DIR""$1".trunc "$DIR""$2".trunc
exit 1
fi

echo "Success! Files are Equivalent!"
rm "$DIR""$1".sorted "$DIR""$2".sorted
rm "$DIR""$1".trunc "$DIR""$2".trunc
