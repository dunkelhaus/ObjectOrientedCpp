#!/bin/bash

rm -rf Makefile

if [[ -z "$1" ]];
then
  echo Executable name required.
  echo usage: makemake.sh executable_name
  exit
fi

# rm -rf includeStatements
for i in $( ls );
do
  if [[ ${i: -4} == ".cpp" ]];
  then
    CPPFILES+=$i
    CPPFILES+=" "
    ((NUMFILES+=1))
    for j in $( sed -n -e '/^#/p' $i );
    do
      if [[ ${j:0:1} = \" ]];
      then
        TEMP=$j
        TEMP=${TEMP##\"}
        TEMP=${TEMP%%\"*}
        TEMP+=" "
        DEPENDENCIES+=$TEMP      
      fi
    done
  DEPENDENCIES+=" ; "
  fi
done

for k in $CPPFILES;
do
  TEMPO=$k
  TEMPO=${TEMPO%%.cpp*}
  TEMPO+=".o";
  OFILES+=$TEMPO
  OFILES+=" "
done

LINE1+=$1
LINE1+=" : "
LINE1+=$OFILES
LINE1+=" "
SPACES+="  "
LINE+=$SPACES

echo -e -n "$LINE1" > Makefile

FLAGS="\t"
FLAGS+="g++ -ansi -Wall -g "

LINE2="\n"
LINE2+=$FLAGS
LINE2+="-o "
LINE2+="$1 "

((NUM_ARGS=$#))

for a in $@;
do
  ((PARSER+=1))
  if [[ $PARSER != 1 ]];
  then
    PASSED_FLAGS+="$a "
  fi
done

LINE2+=$PASSED_FLAGS
LINE2+=$OFILES
LINE2+=" \n"

echo -e "$LINE2" >> Makefile

for z in $OFILES;
do
  LINE_X+=$z
  LINE_X+=" : "
  ((COUNTER+=1))
  for y in $CPPFILES;
  do
    ((COUNTER2+=1))
    if [[ (($COUNTER = $COUNTER2)) ]];
    then
      CURRENTCPP=$y
      LINE_X+=$CURRENTCPP
      LINE_X+=" "
      unset COUNTER2
      break
    fi
  done
  OIFS=$IFS
  IFS=';'
  for x in $DEPENDENCIES;
  do
    ((COUNTER3+=1))
    if [[ (($COUNTER = $COUNTER3)) ]];
    then
      CURRENTDEP=${x##" "}
      CURRENTDEP=${CURRENTDEP%%" "}
      CURRENTDEP="${CURRENTDEP%?}"
      LINE_X+=$CURRENTDEP
      unset COUNTER3
      break
    fi
  done
  IFS=$OIFS
  LINE_X+=" "
  LINE_X+="\n"
  LINE_X+=$FLAGS
  LINE_X+="-c $PASSED_FLAGS"
  LINE_X+=$CURRENTCPP
  LINE_X+="\n"
  LINE_X+="\n"
done

LINE_X+="clean : "
LINE_X+="\n"
LINE_X+="\t"
LINE_X+="rm -f "
LINE_X+=$1
LINE_X+=" "

for h in $CPPFILES;
do
  TEMPO2=$h
  TEMPO2=${TEMPO2%%.cpp*}
  TEMPO2+=".o "
  LINE_X+=$TEMPO2
  LINE_X+=" "
done

LINE_X+=" "

echo -e "$LINE_X" >> Makefile
