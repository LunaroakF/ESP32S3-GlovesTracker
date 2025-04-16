@echo off
REM 设置要格式化的目录（当前目录为 .）
set "target_dir=src/"

REM 查找所有 .cpp 和 .h 文件并递归格式化
for /R "%target_dir%" %%f in (*.cpp *.h) do (
    echo Formatting %%f
    clang-format -i "%%f"
)

echo All done!
pause
