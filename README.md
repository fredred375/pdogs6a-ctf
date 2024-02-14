# DevOps CTF

## READ THIS BEFORE YOU PROCEED
This repository contains the source code of executables used in this CTF, please avoid them if you want to have the full experience.

## Introduction

As a DevOps developer at PDOGS, a significant part of your work will involve managing Linux servers.

In this entry task, we would like you to gain a fundamental understanding of working in a Linux environment by completing the following tasks.

## Setup and Rules


1. VM download link [here](https://drive.google.com/drive/folders/18MYaLvGEFTmPxtCeQvgs9xfQAThCs6-D?usp=sharing)
   * It is recommended to use QEMU or Virtualbox as your hypervisor for this challenge.

| Tested OS | Windows 11 | MacOS M1 | MacOS M2 | Linux x86_64 |
|----|:---:|:---:|:---:|:---:|
| QEMU | ✅ | ✅ | ✅ | ✅ |
| Virtualbox | ✅ |    |    |    |
   * Two virtual disk formats are provided, `qcow2` for QEMU and `vdi` for Virtualbox, other formats like `vmdk` can be converted yourself.
   * The operating system we are working with is Ubuntu Server 22.04.
   * User: `pdoge`, password: `pd6a`
   * While solving `P3` you might find out network interfaces are down, in this case please check the output of `ip a` and edit `/etc/netplan/00-installer-config.yaml` accordingly. After `sudo netplan apply` or a reboot, the machine should work correctly. Below is a working configuration for the network interface `enp0s3`.  ![](https://hackmd.io/_uploads/SyKzGLl_h.png)
   * The following is a working sample command for QEMU that will work on M2 Macbook Pro tested by `wsa`.

     ```bash
         qemu-system-x86_64 -nographic -m 4096 \
             -drive if=virtio,file=pd6a.qcow2,cache=none,format=qcow2 \
             -netdev user,id=net0\
             -nic vmnet-bridged,ifname=en0
     ```
2. SHA 256 file checksums will also be provided for file correctness and integrity checks.
3. All problems are CTFs, please follow problem descriptions and hints to retrieve the flag.
4. Hacky methods like reverse engineering or brute force searches are prohibited, as this defeats the purpose of this entry task.
5. Discussion are allowed but should be minimized with the same reasoning, please message `fredred` or `jtc` for hints instead.
6. All the flags except for the bonus question are in the form `PDOGS{P<id>_<content>}`, `<id>` being the problem number (1-1, 1-2, 2, ...).
7. It is recommended to have snapshots of the VM in case of your own destructive operations.
8. For all the binaries (executables) provided, please keep them at their original folder as moving them might cause unexpected behaviors.
9. After capturing a flag, register and submit your flag at [ctf.fredred.tw](http://ctf.fredred.tw) using a recognizable username and an [ntu.im](http://ntu.im) email account. We will accept submission until Monday, July 3rd 2023, 12:00:00 a.m. GMT+8 (Taipei Standard Time).

## Problems

### P1 (2 flags)

There are a couple files under `p1/`. Are you able to view the content of the files under `p1/`?

### P2

The original user `pdoge` feels lonely being the only user.  Create a new account with superuser privileges to make `pdoge` feel less isolated.

### P3

From the terminal of your local computer, connect to the VM using `ssh`.

Bonus (no flag) : Can you `ssh` into the VM without typing a password?

### P4 (2 flags)

`gary` wants to share a folder named `pdogs6a/` under `p4/` with everyone so that he can host a pseudo-chat room. In order to achieve this, everyone should have full access to the folder. However, `gary` would not like the chat rooms to be deleted or renamed by anyone but the chat room's owner.

### P5

There is information stored within the file `flag.jpg` under `p5/`.  Try to retrieve the flag from the file.

### P6

`pdoge` wants to host a web page that returns `Hello world from PDOGE!` when accessed. Please help `pdoge` achieve his goal. It is recommended to use `Nginx` as the web server.

### P7 (2 flags)

There is a horrendous monster lurking in `p7/`, try to kill him.

### P8 (2 flags)

`timi` has a lot of weird folders and files sitting under `p8/`. Among all these files, there are some that takes over 100 MB of disk space. Please help `timi` delete them and release his precious disk space. However, be sure to not touch the other files, they are very important to `timi`.

### P9 (2 flags)

`fredred` is praying to the almighty [doge](https://zh.wikipedia.org/zh-tw/Doge) god. Unfortunately, doge cannot hear him. Please help `fredred` get his message to doge. For convenience, doge would like to hear


1. His prayer
2. His confession

### P10 (2 flags)

`jtc` is holding two flags at `/p10` but is not willing to tell you. Talk to her and try to get the hidden flags.

### Bonus (2 flags)

Our beloved `wsa` deployed a PostgreSQL Docker container on our VM to store his precious flag, but forgot how to login to the database. Please login to the containerized database and retrieve his precious flag for him. `wsa` said that the flag stored is in the form `PDOGS{wsa-2_<content>}`, with `<content>` being a string with 17 characters that starts with the capital letter `R` , ends with the capital letter `L`, only containing alphanumerics and underlines.

## Deliverables

A simple report on how you retrieved each flag followed with some explanations.
