#!/usr/bin/env sh

g++ -E -nostdinc -Dinclude=#include -I. -Isystem_headers arbitrium/apps/four_in_a_row.cpp | grep -v '^# [0-9]' > four_in_a_row.cpp
