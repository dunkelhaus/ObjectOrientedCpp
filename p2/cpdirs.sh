#!/bin/bash

ERROR="usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
if [[ -z "$1" ]] && [[ -z "$2" ]] && [[ -z "$3" ]];
then
  echo $ERROR
  exit

elif [[ -z "$2" ]] && [[ -z "$3" ]];
then
  echo $ERROR
  exit

elif [[ -z "$3" ]];
then
  echo $ERROR
  exit
fi

if [[ ! -d $1 ]];
then
  echo $ERROR
  exit

elif [[ ! -d $2 ]];
then
  echo $ERROR
  exit

elif [[ ! -d $3 ]];
then
  mkdir $3
fi

for j in $( ls $1 );
do
  if [[ ! -d "$1/$i" ]];
  then
    cp $1/$j $3
  fi
done

for a in $( ls $2 );
do
  if [[ ! -d "$2/$a" ]];
  then
    cp $2/$a $3
  fi
done

for i in $( ls $1 );
do
  if [[ ! -d "$1/$i" ]];
  then
    for k in $( ls $2 );
    do
      if [[ ! -d "$2/$k" ]];
      then
        if [[ $k = $i ]];
        then
          if [[ "$2/$k" -ot "$1/$i" ]];
          then
            cp $1/$i $3
            break
          elif [[ "$1/$i" -ot "$2/$k" ]];
          then
            cp $2/$k $3
            break
          fi
        else
          cp $1/$i $3
        fi
      fi
    done
  fi
done


