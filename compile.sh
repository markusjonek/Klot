
args=("$@")

clang++ ${args[0]}.cpp -o ${args[0]} -I/Library/Frameworks/SDL2.frameworks/Headers -F/Library/Frameworks -framework SDL2

