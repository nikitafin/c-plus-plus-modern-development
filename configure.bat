cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release -Bbuild -GNinja
cd build
cmake --build .
cmake --install . --prefix ..\
copy compile_commands.json ..\
