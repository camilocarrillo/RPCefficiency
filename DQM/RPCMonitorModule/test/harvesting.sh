#!/bin/bash
#./harvesting.sh runslist.txt 2016H v1
for run in `cat $1`
do
    echo $run
    FILENAME="/eos/user/c/carrillo/efficiency/_RPCMonitor_$2-$3_RAW/$run/secefficiency-$run.root"
    echo checking $FILENAME
    if [ -e "$FILENAME" ]
    then
	echo "harvesting done skiping run $run"
    else
	echo "sec file not found, processing run $run"
	rm /tmp/carrillo/$run/ -rf
	cp ../test/ /tmp/carrillo/$run -rf 
	cd /tmp/carrillo/$run/
	cat seg2D2_template.py | sed -e "s|-version-|$3|g" -e "s|-era-|$2|g" -e "s|-run-|$run|g" > seg2D2_$run.py
	cmsRun seg2D2_$run.py 
	cd -
    fi
done
