#!/bin/bash -l
#$ -S /bin/bash
#$ -N $2
echo "Nombre de lives : "
../samples_files/corewar -v -3 $1 $2 | grep 'Player 1 (helltrain) is said to be alive' | wc -l
echo ""
echo "dernier cycle :"
../samples_files/corewar -v -1 $1 $2 | grep 'It is now cycle' | tail -n 1
