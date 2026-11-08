#!/bin/bash
find "$(dirname "$(dirname "$0")")" -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) -not -path "*/include/libs/*" -exec astyle --project -n {} +
echo -e "\e[32mFormatting completed\e[0m"
