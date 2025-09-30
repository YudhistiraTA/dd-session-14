![Example](example.gif)

# Build

Use the provided `build.sh` file
```sh
chmod +x ./build.sh
./build.sh
./main
```
or manually compile using gcc
```sh
gcc -Wall -Werror -O3 main.c arena.c display.c -o main
./main
```