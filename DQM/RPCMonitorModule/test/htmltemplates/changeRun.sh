sed "s|-RUN-|$1 $2|g" htmltemplates/indexBarrel.html > indexBarrel.html
sed "s|-RUN-|$1 $2|g" htmltemplates/indexDistro.html > indexDistro.html
sed "s|-RUN-|$1 $2|g" htmltemplates/tmpindex.html > tmpindex.html
sed "s|-RUN-|$1 $2|g" htmltemplates/indexEndCap.html > indexEndCap.html
sed "s|-RUN-|$1 $2|g" htmltemplates/indexDistroEndCap.html > indexDistroEndCap.html
sed "s|-RUN-|$1 $2|g" htmltemplates/tmpindexEndCap.html > tmpindexEndCap.html
sed "s|-RUN-|$1 $2|g" htmltemplates/quality.html > quality.html
sed "s|-RUN-|$1 $2|g" htmltemplates/resolution.html > resolution.html
sed "s|-RUN-|$1 $2|g" htmltemplates/azimutal.html > azimutal.html
sed "s|-RUN-|$1 $2|g" htmltemplates/azimutalbarrel.html > azimutalbarrel.html
sed "s|-RUN-|$1 $2|g" htmltemplates/cls.html > cls.html
sed "s|-RUN-|$1 $2|g" htmltemplates/ang.html > ang.html
sed "s|-RUN-|$1 $2|g" htmltemplates/indexcutendcap.html > indexcutendcap.html
echo $LOCALRT >> info.txt

export casa=`echo $PWD`
cd $LOCALRT 
showtags >> $casa/info.txt
cd $casa

export effBarrel=`cat rollYeff.txt | grep effBarrel | awk '{print $2}'`
export errBarrel=`cat rollYeff.txt | grep effBarrel | awk '{print $3}'`

export effEndCapP=`cat rollYeff.txt | grep effEndCapP | awk '{print $2}'`
export errEndCapP=`cat rollYeff.txt | grep effEndCapP | awk '{print $3}'`

export effEndCapN=`cat rollYeff.txt | grep effEndCapN | awk '{print $2}'`
export errEndCapN=`cat rollYeff.txt | grep effEndCapN | awk '{print $3}'`

cat rollYeff.txt | grep -v eff | awk '{print $2" "$1}' | sort -n > rollYeff_sorted.txt
cat rollYeff_good.txt | grep -v eff | awk '{print $2" "$1}' | sort -n > rollYeff_sorted_good.txt

sed -e "s|-RUN-|$1 $2|g" -e "s|-effBarrel-|$effBarrel|g" -e "s|-errBarrel-|$errBarrel|g" -e "s|-effEndCapP-|$effEndCapP|g" -e "s|-errEndCapP-|$errEndCapP|g" -e "s|-effEndCapN-|$effEndCapN|g" -e "s|-errEndCapN-|$errEndCapN|g" htmltemplates/MainIndex.html > MainIndex.html
sed -e "s|-RUN-|$1 $2|g" -e "s|-effBarrel-|$effBarrel|g" -e "s|-errBarrel-|$errBarrel|g" -e "s|-effEndCapP-|$effEndCapP|g" -e "s|-errEndCapP-|$errEndCapP|g" -e "s|-effEndCapN-|$effEndCapN|g" -e "s|-errEndCapN-|$errEndCapN|g" htmltemplates/index.html > index.html
sed -e "s|-RUN-|$1 $2|g" -e "s|-effBarrel-|$effBarrel|g" -e "s|-errBarrel-|$errBarrel|g" -e "s|-effEndCapP-|$effEndCapP|g" -e "s|-errEndCapP-|$errEndCapP|g" -e "s|-effEndCapN-|$effEndCapN|g" -e "s|-errEndCapN-|$errEndCapN|g" htmltemplates/muonpaper.html > muonpaper.html

mkdir disks/
cp htmltemplates/RE*.html disks/
echo rotating disksimages
#source htmltemplates/rotateall.sh
