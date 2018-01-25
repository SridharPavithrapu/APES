#!/bin/bash

# system_information.sh - A simple shell script to get system information 
# Author: Sridhar pavithrapu
# Date: 1/24/2018

clear

INFOTXT=sysinfo.txt


echo "___________________________________________________________________________________" >> $INFOTXT

echo "**** Host Name Information ****" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT


echo "UserName : $(whoami) " >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "**** System and OS Information Details ****" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "System Information: " >> $INFOTXT

echo "Operating system : $(uname) " >> $INFOTXT

echo "Operating System Architecture: $(uname -m) " >> $INFOTXT

echo "Operating System Type: $(uname -a) " >> $INFOTXT

echo "Operating System Distribution: $(cat /etc/*-release | grep "\<DISTRIB_DESCRIPTION\>" ) " >> $INFOTXT

echo "Operating System Version: $(cat /etc/*-release | grep "\<VERSION\>" ) " >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "**** Kernel Information Details ****" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "Kernel Used: $(uname -r) " >> $INFOTXT

echo "Kernel Version: $(uname -a) " >> $INFOTXT

echo "Kernel GCC Version: $(cat /proc/version) " >> $INFOTXT

echo "Kernel Build Time: $(uname -v) " >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "**** CPU Information Details ****" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "CPU Information: $(lscpu) " >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "****File System Information Details ****" >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT

echo "File System Information: $(df -h) " >> $INFOTXT

echo "___________________________________________________________________________________" >> $INFOTXT


