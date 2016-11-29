#!/bin/bash

echo Config file $1
if [ -f "$1" ]
then
   file_name=$1
else
echo "File \"$1\" does not exist."
exit 0
fi

export castorpad=`awk 'NR==1' $1 | sed -e "s|:||g"`
export padtorun=`awk 'NR==2' $1 | sed -e "s|:||g"`
export step=`awk 'NR==3' $1 | sed -e "s|:||g"`
export queue=`awk 'NR==4' $1 | sed -e "s|:||g"`
export key=`awk 'NR==5' $1 | sed -e "s|:||g"`


if [[ -f $castorpad/$key.root ]]
then
   echo "the merging is done"
   exit 0 
else
   echo "File $castorpad/$key.root does not exist, exectuing merging."
fi


export wd=`pwd`

~carrillo/public/for_All/cafDynamic/mergingDynamic/genmergeLocalDynamic.sh $1
source corraBatchLocal #submiting merging jobs

export expectedInCastorLocal=`cat corraBatchLocal | wc -l`
export filestomerge=`ls $castorpad | grep $key | wc -l`

echo Merging $filestomerge in $expectedInCastorLocal files.

sleep 10
export numrun=`bjobs | grep RUN | grep $queue | wc -l`
export numpend=`bjobs | grep PEND | grep $queue | wc -l`
export filesInCastorLocal=`ls $castorpad | grep Local | wc -l`

i=0;

until [[ $numrun -eq 0 && $numpend -eq 0 || $expectedInCastorLocal -eq $filesInCastorLocal ]]
        do
        export numrun=`bjobs | grep RUN | grep $queue | wc -l`
        export numpend=`bjobs | grep PEND | grep $queue | wc -l`
	export filesInCastorLocal=`ls $castorpad | grep Local | wc -l`        
        warn2=$(($numrun+$numpend+$filesInCastorLocal-$expectedInCastorLocal))
        sleep 10
        let "i=$i+1"
        let "t=i*10"
        echo t=$t s jobs: \| run=$numrun \| pend=$numpend \| in Castor=$filesInCastorLocal of $expectedInCastorLocal \| warn2=$warn2 \|
	~carrillo/public/for_All/cafDynamic/htmline.sh $t $numrun $numpend $filesInCastorLocal $expectedInCastorLocal $warn2 Justmerge$key > ~/public/report/$key.html
        sleep 10
        done

export foldersInCastorLocal=`ls $castorpad | grep Local | wc -l`
if [[ $foldersInCastorLocal -eq 0 ]]
then
   echo There was a problem in the merging, run in interactive mode.
   ls $castorpad
   exit 0
fi

echo Submiting Last Merging for $key for $filesInCastorLocal files
sleep 10
echo "hadding in $castorpad all Local*.root -> $key.root"
rm $castorpad/$key.*.root
hadd -f $castorpad/$key.root $castorpad/Local*.root
echo "$key is done, time=$t, files=$filestomerge, warning=($warn2), host=$HOST" > finbash.txt
cat finbash.txt
rm finbash.txt
~carrillo/public/for_All/cafDynamic/htmline.sh $t 0 0 $filesInCastorLocal $expectedInCastorLocal $warn2 Finished$key$filestomerge > ~/public/report/$key.html

exit 0;
