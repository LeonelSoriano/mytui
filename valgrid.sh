if [ -f test ];
then
    echo "exite"
else
    echo "No, no existe Make"
    make
fi
valgrind --leak-check=full --show-leak-kinds=all -v --log-file="valgrind.log" ./test
