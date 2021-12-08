package com.pang.nativeagent.example;

import com.pang.nativeagent.instrument.Instrumentation;

public class Agent {
    public static void premain(final String agentArgs, final Instrumentation instrumentation) {
        System.out.println("#Agent#======premain======");
    }
}
