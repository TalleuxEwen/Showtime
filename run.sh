sudo apt-get install pulseaudio libasound-dev libjack-dev

mkdir -p build
cd build
cmake ..
make
mv Showtime ../
cd ..

pacmd load-module module-null-sink sink_name=ShowTime_Virtual_Input sink_properties=device.description=ShowTime_Virtual_Input

./Showtime
