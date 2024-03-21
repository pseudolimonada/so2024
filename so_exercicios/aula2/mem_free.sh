#!/bin/bash

while :
do
echo `grep MemFree /proc/meminfo` : `date +%d/%m/%Y" "%H:%M:%S` |tee -a mem_free.log;
sleep 5;
done
