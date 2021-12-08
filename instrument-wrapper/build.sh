mvn clean package

rm -rf build && mkdir build && cd build
cmake ../src/main/native/ && make
cd ..

package=instrument_wrapper
rm -rf ${package}  && mkdir ${package}
mv target/testagent.jar ${package}/
mv build/libinstrument_wrapper.so ${package}/
zip ${package}.zip ${package}/*
