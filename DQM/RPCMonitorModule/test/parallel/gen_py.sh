#!/bin/bash 
rm toSource
for i in `cat $1`
do 
    echo "cat $2 | sed -e 's|-file-|$i|g' > $i.py" >> toSource
    echo "cmsRun $i.py" >> corraAll
done
head toSource
echo .
echo .
echo .
tail toSource
