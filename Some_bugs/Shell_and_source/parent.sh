#!/bin/bash

Hello="?????"


echo -e "\nwaiting child no soure"
./child_no_source.sh
echo $Hello


echo -e "\nwaiting child has soure"
source ./child_has_source.sh
echo $Hello


echo -e "\nwaiting child no soure"
./child_no_source.sh
echo $Hello


echo -e "\nDone :v"