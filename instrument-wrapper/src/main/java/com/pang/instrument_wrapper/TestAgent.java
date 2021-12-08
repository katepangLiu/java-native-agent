package com.pang.instrument_wrapper;

import java.lang.instrument.Instrumentation;

public class TestAgent {
    public static void premain(final String agentArgs, final Instrumentation instrumentation) {
        System.out.println("javaagent.premain");
        System.out.println( InstrumentWrapper.stringFromJNI() );
    }
}