#!/bin/bash
for run in `cat $1`
do
echo $run
cp ~/efficiency/timing/CMSSW_8_0_1/src/DQM/RPCMonitorModule/test/ /tmp/carrillo/$run -rf 
cd /tmp/carrillo/$run/
cat seg2D2_template.py | sed -e "s|-run-|$run|g" > seg2D2_$run.py
cmsRun seg2D2_$run.py &
cd -
done
