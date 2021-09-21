for i in $(seq 1000) ; do
  while true
  do
  	if ! ln file file.lock > "/dev/null" 2>&1; then
    	sleep 0.001
    else
      break
    fi
  done
  lastnumber=$(cat file | tail -n 1)
  ((lastnumber++))
  echo "$lastnumber" >> file
  rm file.lock
done

