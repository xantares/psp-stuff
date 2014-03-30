#!/bin/sh


if test $# -ge 1; then
  PIDLIST=`ps aux | grep $1 | cut -d " " -f 3`
#   echo "$PIDLIST"
  for PID in $PIDLIST; do
#     echo $PID
    kill -15 $PID
    kill -9 $PID
  done
else
  echo 'no input name'
fi
