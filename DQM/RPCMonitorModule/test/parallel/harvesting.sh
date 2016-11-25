#!/bin/bash
for run in `cat $1`
do
    echo $run
    rm /tmp/carrillo/$run/ -rf
    cp ../../test/ /tmp/carrillo/$run -rf 
    cd /tmp/carrillo/$run/
    cat seg2D2_template.py | sed -e "s|-run-|$run|g" > seg2D2_$run.py
    cmsRun seg2D2_$run.py &
    cd -
done
