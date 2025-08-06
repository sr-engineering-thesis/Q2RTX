#!/bin/bash
g++ -std=c++17 convert.cpp `pkg-config --cflags --libs opencv4` -o convert
