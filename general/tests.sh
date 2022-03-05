#!/bin/bash

cppcomp && gnome-terminal -- run-tests
# cppcomp Gen-[generator] && gnome-terminal -- run-tests [fast] [slow] "./Gen-[generator] --log 5 5"
# fast = optimization code
# slow = brute force code
# --log (at best, args 150,150)
# without log (at best, args 100)