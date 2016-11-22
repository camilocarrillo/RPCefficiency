#!/bin/bash
#don't exectute always $ . sub...
# . submit_run.sh 2016B 275 059

eoscms ls /store/data/Run$1/RPCMonitor/RAW/v2/000/$2/$3/00000/ > files

export folder=`echo /store/data/Run$1/RPCMonitor/RAW/v2/000/$2/$3/00000/`

mkdir _RPCMonitor_Run$1-v2_RAW/
mkdir _RPCMonitor_Run$1-v2_RAW/$2$3/
rm _RPCMonitor_Run$1-v2_RAW/$2$3/files-efficiency$2$3.txt
touch _RPCMonitor_Run$1-v2_RAW/$2$3/files-efficiency$2$3.txt

for file in `cat files`:
do 
    echo "$folder/$file" | sed -e "s|:||g" >> _RPCMonitor_Run$1-v2_RAW/$2$3/files-efficiency$2$3.txt
done

cat config_template.txt | sed -e "s|-run-|$2$3|g"> _RPCMonitor_Run$1-v2_RAW/$2$3/$2$3.txt
cd _RPCMonitor_Run$1-v2_RAW/$2$3/
~/parallel/submit.sh $2$3.txt


