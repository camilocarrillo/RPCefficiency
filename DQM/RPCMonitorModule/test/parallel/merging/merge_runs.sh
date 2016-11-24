#/bin/bash


for run in `cat $1`
do 
    echo $run
    mkdir $run
    cat parameters_template.txt | sed  -e "s|-run-|$run|g" > $run/parameters_$run.txt
    cd $run 
    ../justmerge.sh parameters_$run.txt > /tmp/carrillo/log_merge_$run.txt &
    cd ../
    echo "run $run submited"
done
