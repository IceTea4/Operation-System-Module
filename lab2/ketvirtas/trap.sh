#!/bin/sh
mytrap(){
	date
	id
}
mybreak(){
	echo "Programa nutraukta"
}
echo Pradzia
trap mytrap 0
trap mybreak 1 2 3 6 14 15
sleep 20
echo Pabaiga
