cd $1
rm RE-* -rf
htmltemplates/changeRun.sh $1_MWGR_1_09
cd Sides
/tmp/carrillo/prodimages/$1/htmltemplates/rot.sh
cd /tmp/carrillo/prodimages/
scp -r $1 webrpc@webcms.ba.infn.it:public_html/efficiency/MWGR_1_09/

