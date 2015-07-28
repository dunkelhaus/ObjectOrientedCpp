#!/bin/bash

if [[ ! -d "$1" ]]
then
  echo 'usage: grepdir.sh directory pattern [-grep option]*'
exit
fi
if [[ ! "$#" -ge 2 ]]
then
  echo 'usage: grepdir.sh directory pattern [-grep option]*'
exit
fi

argument1="$1"
argument2="$2"
shift
shift
find $argument1 -type f -exec grep $argument2 {} "$@" \;

