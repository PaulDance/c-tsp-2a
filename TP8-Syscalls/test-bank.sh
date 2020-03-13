#! /bin/bash

bankExecLoc="./cmake-build-debug/bank"
bankInitLoc="./cmake-build-debug/bank-init-sem"
bankSem="/bank"
name=Ronflex
n=100

echo "Generating $n transactions of +1 euros in parallel on $name's account"

"$bankInitLoc" "$bankSem"
i=0

while [[ $i -lt $n ]]; do
    "$bankExecLoc" "$name" 1 &#>/dev/null 2>&1 &
    i=$(($i + 1))
done

wait

echo "$name should now have $n euros"
"$bankExecLoc" "$name" 0

rm -f "$name"
