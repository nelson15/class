cd build

ctest -v
cp Testing/Temporary/LastTest.log Testing/Test.log
echo "Testing Complete. Log written to build/Testing/Test.log"
cd ..
