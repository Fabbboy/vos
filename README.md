# V-OS
[![Build develop branch](https://github.com/Fabbboy/vos/actions/workflows/makefile.yml/badge.svg?branch=develop)](https://github.com/Fabbboy/vos/actions/workflows/makefile.yml)

## Description

This project is a work-in-progress operating system written in C and Assembly. It utilizes the Multiboot2 specification and Grub bootloader. The main goal of this project is to create a lightweight and efficient operating system that can be used for educational purposes, experimentation, and further development.

## Features

- Write to IOPorts
- Write to Serial Port
- Basic string manipulation

## Getting Started

### Installation

1. Clone the repository: `git clone https://github.com/fabbboy/vos.git`
2. Navigate to the project directory: `cd vos`
3. Install deps using `sh install.sh`

### Usage

1. Run `make` to build the project
2. Run `make run` to run the project in QEMU

## Development

### Built With

- GRUB
- Make
- C/ASM
- QEMU
- BOCHS


### Roadmap

- GDT/IDT
- Paging
- Allocator
