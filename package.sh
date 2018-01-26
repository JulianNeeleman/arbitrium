#!/usr/bin/env sh

g++ -E -nostdinc -Dinclude=#include -I. -Isystem_headers ${1} | grep -v '^# [0-9]' > submission.cpp
zip submission.zip submission.cpp
rm submission.cpp
