rm -rf tmp
mkdir tmp
touch tmp/file1
touch tmp/file2
link tmp/file1 tmp/link1
link tmp/file1 tmp/link2
touch tmp/file3
link tmp/file3 tmp/link3
link tmp/file3 tmp/link4
link tmp/file3 tmp/link5
gcc ex4.c -o ex4 && ./ex4 > ex4.txt
