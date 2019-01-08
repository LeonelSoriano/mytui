if [ -f test ];
then
    echo "exite"
else
    echo "No, no existe Make"
    make
fi
#--log-file="valgrind.log"
valgrind --leak-check=full --show-leak-kinds=all -v  ./mytui
