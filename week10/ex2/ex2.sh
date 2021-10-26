mkdir week01
mkdir week10
echo "Nikita" >> week01/file.txt
link week01/file.txt ./week10/_ex2.txt
ls -i week01/file.txt
var="$(stat -f '%i' ./week01/file.txt)"
find ./ -inum $var >> ex2.txt
find week10/ -inum $var -exec rm {} \;  
