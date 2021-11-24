# java-native-agent

## QuickStart

```shell
# build
sh build

# test
java -Xbootclasspath/a:lib/instrument.jar -agentpath:lib/libnativeagent.so=jar/agent.jar -version
```

