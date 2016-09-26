#!/bin/bash
cd /tmp/carrillo/
mkdir prodimages
cd prodimages
if [ -d $1 ]
then
  rm $1 -rf
fi
mkdir $1
cd $1
export datasetpath=`echo $2 | sed -e "s|/|_|g"`
export label=`echo $3`
cp /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/htmltemplates/ -rf .

echo ==message== Downloading file from server..........................................................
wget http://cmsrpc402b20.cern.ch/$label/$datasetpath/$1/$label-$1.root
export exist=`ls -1 | grep $label-$1.root | wc -l`
echo ==message== exist value: $exist
if [[ $exist -eq 0 ]]
    then
    echo ==message== file not downloaded from server  
    echo ==message== trying to go with castor files
    export rootfiles=`nsls /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root | wc -l`
    if [[ $rootfiles -eq 0 ]]
	then
	echo ==message== There is not merged root file produced, trying to get Local.root
	export local=`nsls /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/Local.root | wc -l`
	if [[ $local -eq 0 ]]
	    then
	    echo ==message== Neither root file trying to merge LocalX-Y.root files 
	    export filesInCastorLocal=`nsls /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/ | grep Local | grep -v Local.root | wc -l`	
	    if [[ $filesInCastorLocal -eq 0 ]]
		then      	
		echo ==message== LocalX-Y files in castor not found
		exit 0
	    else
		echo ==message== There are $filesInCastorLocal LocalX-Y.root files submiting Last Merging in $label for $filesInCastorLocal files
		export castorpad=`echo /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/`
		export filesInCastorLocalfinal=`nsls $castorpad | grep Local.root | wc -l`
		
		nsls $castorpad | grep Local | grep -v Local.root > filesLocal-$label-$1
		
		for rootfile in `cat filesLocal-$label-$1`
		  do
		  echo ==message== $rootfile
		  rfcp $castorpad/$rootfile .
		done
		
		ls *.root > listoffilesLocalFinal-$label-$1.txt
		
		hadd Local.root Local*
		
		rfcp Local.root $castorpad
		
		rfcp $castorpad/Local.root $castorpad/$label-$1.root
		echo ==message== $castorpad
		nsls $castorpad
		rm Local*	
	    fi
	else
	    rfcp /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/Local.root /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root 
	fi
    fi
else
    echo ==message== I got the file uploading but castor is not working skipping the upload to castor .........
    #rfmkdir /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1
    #rfcp $label-$1.root /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root
    echo ==message== continuing with harvesting
    echo ==message== Temporary sleeping
fi

echo ==message== Castor does not work wgetgin the file
wget http://cmsrpc402b20.cern.ch/$label/$datasetpath/$1/$label-$1.root
#rfcp /castor/cern.ch/user/c/carrillo/$label/$datasetpath/$1/$label-$1.root .
sed -e "s|-RUN-|$1|g" -e "s|-label-|$label|g" /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/seg2D2label.py > seg2D2.py
