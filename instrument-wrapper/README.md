

## Java Instrument Wrapper



## Quick Start

```shell
#build
sh build.sh
```



```shell
# load test javaagent
java -Djava.library.path=./ -agentpath:./libinstrument_wrapper.so=testagent.jar -version

# load javaagent
java -Djava.library.path=./ -agentpath:./libinstrument_wrapper.so=%{javaagent}% ...
```

