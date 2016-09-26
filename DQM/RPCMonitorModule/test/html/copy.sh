#!/bin/bash
cd /tmp/carrillo/prodimages
rm *.root
htmltemplates/changeRun.sh $1
cd Sides
../htmltemplates/rot.sh
cd /tmp/carrillo/prodimages/
rm RE-* -rf
cd /tmp/carrillo/
scp -r prodimages/ webrpc@webcms.ba.infn.it:public_html/efficiency/$1
