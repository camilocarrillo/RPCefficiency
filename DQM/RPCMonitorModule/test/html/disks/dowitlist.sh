for i in `cat $1`
do 
echo doing $i ...
cp ../$i/Profile_2D.png $i.png
done

