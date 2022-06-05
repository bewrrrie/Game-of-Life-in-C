if [ ! -e gol ]; then
    echo "Compiling executable binary..."
    cd src
    make compile
    cp gol ../
    cd ..
    echo "Compiled executable \"gol\"."
fi

if [ $# -lt 1 ]; then
    ./gol < samples/gosper_gun.txt
else
    ./gol < $1
fi
