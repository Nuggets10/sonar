#!/bin/bash
find "$(dirname "$(dirname "$0")")" -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) -exec astyle -n {} +
echo -e "\e[32mFormatting completed\e[0m"
