#!/bin/bash
cd /tmp/carrillo/prodimages/$1/
htmltemplates/changeRun.sh $1
cd Sides
/tmp/carrillo/prodimages/$1/htmltemplates/rot.sh
cd /tmp/carrillo/$1
firefox MainIndex.html
#scp -r prodimages/$1 webrpc@webcms.ba.infn.it:public_html/efficiency/$1
