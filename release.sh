echo "Compiling to Linux..."

mkdir stellarthing-linux
mkdir stellarthing-linux/assets
cp -r assets/* stellarthing-linux/assets
env GOOS=linux GOARCH=amd64 go build -o stellarthing-linux/stellarthing
tar -czvf stellarthing-linux.tar.gz stellarthing-linux

echo "Compiling to Windows..."

mkdir stellarthing-windows
mkdir stellarthing-windows/assets
cp -r assets/* stellarthing-windows/assets
# i love windows
cp vendor/raylib.dll stellarthing-windows/raylib.dll
env GOOS=windows GOARCH=amd64 go build -o stellarthing-windows/stellarthing.exe
zip -r stellarthing-windows.zip stellarthing-windows

echo "Compiling completed."