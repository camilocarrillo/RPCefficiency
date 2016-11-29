#/bin/bash
#call as $./merge_runs.sh runslist.txt 2016H v1

for run in `cat $1`
do 
    echo $run
    FILENAME="/eos/user/c/carrillo/efficiency/_RPCMonitor_$2-$3_RAW/$run/efficiency-$run.root"
    echo checking $FILENAME
    if [ -e "$FILENAME" ]
    then
        echo "merge done skiping run $run"
    else
        echo "eff file not found, processing run $run"
	mkdir $run
	cat parameters_template.txt | sed  -e "s|-era-|$2|g" -e "s|-version-|$3|g" -e "s|-run-|$run|g" > $run/parameters_$run.txt
	cd $run 
	../justmerge.sh parameters_$run.txt > /tmp/carrillo/log_merge_$run.txt &
	cd ../
	echo "run $run submited"
    fi
done
