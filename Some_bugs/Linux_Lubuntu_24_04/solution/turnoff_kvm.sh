#!/bin/bash

sudo rmmod kvm_intel  # if CPU Intel  or using `sudo modprobe -r kvm_intel`  
# sudo rmmod kvm_amd    # if CPU AMD
sudo rmmod kvm
