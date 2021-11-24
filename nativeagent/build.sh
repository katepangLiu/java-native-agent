# instrument.jar
echo "build instrument.jar"
cd java/
rm -rf classes/ && mkdir classes
javac -d classes/ com/pang/nativeagent/instrument/*.java
cd classes/
jar cf instrument.jar com/pang/nativeagent/instrument/*.class
javah com.pang.nativeagent.instrument.InstrumentationImpl
cd ../..
rm -rf lib && mkdir lib
mv java/classes/instrument.jar lib/
rm -rf gen_headers && mkdir gen_headers
mv java/classes/com_pang_nativeagent_instrument_InstrumentationImpl.h gen_headers/

# example agent.jar
echo "build agent.jar"
cd java/
javac  -d classes/ com/pang/nativeagent/example/*.java
cd classes
jar cfm agent.jar ../com/pang/nativeagent/example/MANIFEST.MF com/pang/nativeagent/example/*.class

cd ../..
rm -rf jar && mkdir jar
mv java/classes/agent.jar jar/

# libnativeagent.so
echo "build libnativeagent.so"
cd native/
rm -rf build && mkdir build
cd build && cmake .. && make
cd ../..

mv native/build/libnativeagent.so lib/
