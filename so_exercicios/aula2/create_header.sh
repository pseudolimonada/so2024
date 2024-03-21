#!/bin/bash

touch $1.c
echo "// $3"  >> $1.c
echo "// Projet: $2" >> $1.c 
echo "// -------------------"  >> $1.c
