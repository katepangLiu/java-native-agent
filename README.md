# java-native-agent

## QuickStart

```shell
cd nativeagent

# build
sh build

# test
java -Xbootclasspath/a:lib/instrument.jar -agentpath:lib/libnativeagent.so=jar/agent.jar -version
```

