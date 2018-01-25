#!/bin/bash

# build_kernel.sh - A simple shell script to build the kernel 
# Author: Sridhar pavithrapu
# Date: 1/24/2018

clear


# URL for kernel image for downloading
KERNEL_DOWNLOAD_URL=https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.14.15.tar.xz 

# Updating all the packages to the latest version 
sudo apt-get update

# Downloading all the required dependencies
sudo apt-get install git make fakeroot libelf-dev build-essential ncurses-dev xz-utils libssl-dev bc

# Downloading the latest kernel image
echo -e "Downloading the kernel image\n"

wget $KERNEL_DOWNLOAD_URL


# Untar the kernel source file
linux_kernel_tar_file=`echo $KERNEL_DOWNLOAD_URL | awk -F "/" '{print $NF}'`
linux_kernel_version=`echo $linux_kernel_tar_file | awk -F "-" '{print $2}' | awk -F ".tar" '{print $1}'`

echo -e "Untaring linux kernel image\n"
tar -xf $linux_kernel_tar_file

linux_folder_name=`echo $linux_kernel_tar_file | awk -F ".tar" '{print $1}'`

cd $linux_folder_name 

# Configuring the linux kernel
cp /boot/config-`uname -r` .config
 
make menuconfig

# Building the kernel
make -j`nproc --all`

echo -e "Installing all kernel modules\n"

# Installing the kernel modules
make -j`nproc --all` modules_install

echo -e "Installing kernel\n"

make -j`nproc --all` install

echo -e "Updating grub and initramfs"

update-initramfs -c -k $linux_kernel_version
update-grub
update-grub2
