# GitHub diesnot seem to host empty direcotries. 
# This will setup those directories in your working directory.
# There may be some other way, but I donot know at this point.

for i in 'lib' 'obj' 'bin'; do
	echo 'Setting Up' $i
	mkdir -p $i
done
