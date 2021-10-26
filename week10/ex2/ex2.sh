mkdir week01
mkdir week10
echo "Nikita" >> week01/file.txt
link week01/file.txt week10/_ex2.txt
ls -i week01/file.txt
find ./ -inum 5324330 >> ex2.txt
find week10/ -inum 5324330 -exec rm {} \;  
