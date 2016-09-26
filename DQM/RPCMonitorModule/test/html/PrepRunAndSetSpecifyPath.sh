#!/bin/bash
echo Starting with PrepRunAndSetSpecifyPath
/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/prepProdImagesSpecifyPath.sh $1 $2 $4
cd $3 #this is the location of the project to analyze with seg2D2.py
echo label = $4
eval `scramv1 ru -sh`
cd /tmp/carrillo/prodimages/$1/
export rootfiles=`ls *.root | wc -l`
if [[ $rootfiles -eq 0 ]]
then
   echo There is not root file produced skiping production of images.
   ls /tmp/carrillo/prodimages/$1/
   exit 0
fi
cp /afs/cern.ch/user/c/carrillo/blacklist_roll/blacklist.dat .
cmsRun seg2D2.py
cp /afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic/html/gaussianResolutionMuonPaper.C .
cp sec*root secTMP.root
root -b gaussianResolutionMuonPaper.C
rm secTMP.root
htmltemplates/changeRun.sh $1 $2
cd Sides
/tmp/carrillo/prodimages/$1/htmltemplates/rot.sh
cd /tmp/carrillo/prodimages/$1/
cat rollYeff.txt | awk '{print $2" "$1}' | sort -nr > rollYeff_sorted.txt
cd /tmp/carrillo/
echo HERE IS DEFINED datsetpath
export datasetpath=`echo $2 | sed -e "s|/|_|g"`
echo datasetpath = $datasetpath

echo label = $label

export folderexist=`ssh carrillo@cmsrpc402b20 "ls -la -d /var/www/$4/$datasetpath/" | grep such | wc -l`
if [[ $rootfiles -eq 1 ]]
then
   echo The folder in cmsrpc402b20 does not exist creating folder
   ssh carrillo@cmsrpc402b20 "mkdir /var/www/$4/; mkdir /var/www/$4/$datasetpath/; chmod 777 /var/www/$4/$datasetpath/" 
   scp -r prodimages/$1 carrillo@CMSRPC402B20:/var/www/$4/$datasetpath/
   exit 0
else 
   echo "Assuming that the RIGHTS are correct coping to destiny carrillo@CMSRPC402B20:/var/www/$4/$datasetpath/"
   scp -r prodimages/$1 carrillo@CMSRPC402B20:/var/www/$4/$datasetpath/
fi
