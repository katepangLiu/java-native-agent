# java-native-agent

## QuickStart

```shell
cd nativeagent

# build, it will generate lib/instrument.jar lib/libnativeagent.so , and agent.jar, the simplest example agent.
sh build.sh

# test
java -Xbootclasspath/a:lib/instrument.jar -agentpath:lib/libnativeagent.so=jar/agent.jar -version
```
