#!/bin/bash
/afs/cern.ch/user/c/carrillo/public/for_All/cafDynamic//html/prepProdImages.sh $1 $2
cd $3 #this is the location of the project to analyze with seg2D2.py
eval `scramv1 ru -sh`
cd /tmp/carrillo/prodimages/$1/
export rootfiles=`ls *.root | wc -l`
if [[ $rootfiles -eq 0 ]]
then
   echo There is not root file produced skiping production of images.
   ls /tmp/carrillo/prodimages/$1/
   exit 0
fi
cmsRun seg2D2.py
htmltemplates/changeRun.sh $1 $2
cd Sides
/tmp/carrillo/prodimages/$1/htmltemplates/rot.sh
cd /tmp/carrillo/
export datasetpath=`echo $2 | sed -e "s|/|_|g"`
echo "coping to destiny carrillo@CMSRPC402B20:/var/www/html/efficiency/$datasetpath/"
scp -r prodimages/$1 carrillo@CMSRPC402B20:/var/www/html/efficiency/$datasetpath/
