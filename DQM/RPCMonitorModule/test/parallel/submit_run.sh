#!/bin/bash
#don't exectute always $ . sub...
# . submit_run.sh 2016B 275 059 v2

eoscms ls /store/data/Run$1/RPCMonitor/RAW/$4/000/$2/$3/00000/ > files

export folder=`echo /store/data/Run$1/RPCMonitor/RAW/$4/000/$2/$3/00000/`

mkdir -p _RPCMonitor_Run$1-$4_RAW/
mkdir -p _RPCMonitor_Run$1-$4_RAW/$2$3/
rm _RPCMonitor_Run$1-$4_RAW/$2$3/files-efficiency-$2$3.txt
touch _RPCMonitor_Run$1-$4_RAW/$2$3/files-efficiency-$2$3.txt

for file in `cat files`:
do 
    echo "$folder/$file" | sed -e "s|:||g" >> _RPCMonitor_Run$1-$4_RAW/$2$3/files-efficiency-$2$3.txt
done

cat config_template_2017.txt | sed -e "s|-version-|$4|g" -e "s|-era-|$1|g" -e "s|-run-|$2$3|g"> _RPCMonitor_Run$1-$4_RAW/$2$3/$2$3.txt
cd _RPCMonitor_Run$1-$4_RAW/$2$3/
~/parallel/submit.sh $2$3.txt > /tmp/carrillo/$2$3log.txt &
cd -

