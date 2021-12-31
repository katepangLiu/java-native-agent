# Java Native Agent

[instrument-clone](instrument-clone/) is a clone of openjdk-8 instrument lib,  it can be built without build whole jdk.

[instrument-wrapper](instrument-wrapper/) is a wrapper of jdk instrument lib,  we can easily extend the java instrumentation in jvmti level with the wrapper, monitoring other jvmti event, such as ` JVMTI_EVENT_EXCEPTION` .