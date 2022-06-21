@echo off
C:/msys64/msys2_shell.cmd -defterm -here -no-start -clang64 -c "compile_cmake_project.sh && cd build && ./main.exe"
