package com.protonmail.ch.openpgp;

import android.app.Application;
import android.test.ApplicationTestCase;
import android.util.Log;

/**
 * <a href="http://d.android.com/tools/testing/testing_android.html">Testing Fundamentals</a>
 */
public class ApplicationTest extends ApplicationTestCase<Application> {
    public ApplicationTest() {
        super(Application.class);
    }


    public void test_getAppName() {
        String appName = getContext().getString(R.string.app_name);
        assertNotNull(appName);
        assertEquals("OpenPGP", appName);
    }



}