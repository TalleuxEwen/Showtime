sudo apt-get install pulseaudio libasound-dev libjack-dev

mkdir -p build
cd build
cmake ..
make
mv Showtime ../
cd ..

./Showtime
