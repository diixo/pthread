#!/bin/bash
set -e
lscpu 2>&1 | tee cpu-info.txt
