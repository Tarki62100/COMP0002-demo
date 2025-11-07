# Compile all .c files and run
clang *.c -o program.exe
if ($LASTEXITCODE -eq 0) {
    ./program.exe | java -jar drawapp-4.5.jar
}
