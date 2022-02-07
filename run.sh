#!/bin/bash


cmake -S . -B ./out/build && cd ./out/build && make && ./test_window
