for i in $(seq 1000) ; do 
    lastnumber=$(cat file | tail -n 1)
    ((lastnumber++))
    echo "$lastnumber" >> file
done
