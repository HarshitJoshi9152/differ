rm ../build/* -f;
cd ../src;
make && echo "" && ./../build/differ ./../test/file1.txt ./../test/file2.txt;