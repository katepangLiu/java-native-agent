package com.pang.instrument_wrapper;

public class InstrumentWrapper {

    static {
        System.loadLibrary("instrument_wrapper");
    }

    protected InstrumentWrapper() {
    }

    // Native methods
    protected native static String stringFromJNI();
}
