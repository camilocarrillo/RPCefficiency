for img in `ls *.png`
do
  convert -rotate 90 $img Rot$img
done

