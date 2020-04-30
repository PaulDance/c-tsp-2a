#! /bin/bash

bankExec="./cmake-build-debug/bank"
name="Ronflex"
n=100

echo "Generating $n transactions of +1 euros in parallel on $name's account"
i=0

while [[ "$i" -lt "$n" ]]; do
    "$bankExec" "$name" 1 &#>/dev/null 2>&1 &
    i=$(($i + 1))
done

wait

echo "$name should now have $n euros"
"$bankExec" "$name" 0

rm -f "$name"
