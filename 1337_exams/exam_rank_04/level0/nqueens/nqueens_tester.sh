#!/bin/bash

declare -A expected
expected[4]=2
expected[5]=10
expected[6]=4
expected[7]=40
expected[8]=92
expected[9]=352
expected[10]=724
expected[11]=2680
expected[12]=14200
expected[13]=73712

for i in {4..13}; do
    output_lines=$(./a.out "$i" | wc -l)

    if [ "$output_lines" -eq "${expected[$i]}" ]; then
        echo "✅ $i → OK ($output_lines lines)"
    else
        echo "❌ $i → KO (got $output_lines, expected ${expected[$i]})"
    fi
done
