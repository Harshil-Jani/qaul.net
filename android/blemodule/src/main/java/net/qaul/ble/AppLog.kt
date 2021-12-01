package net.qaul.ble

import android.util.Log

object AppLog {
    fun e(TAG: String, msg: String?) {
        if (BuildConfig.DEBUG) {
            Log.e(TAG, msg!!)
        }
    }

    fun i(TAG: String?, msg: String?) {
        if (BuildConfig.DEBUG) Log.i(TAG, msg!!)
    }

    fun d(TAG: String, msg: String) {
        if (BuildConfig.DEBUG) {
            Log.d(TAG, msg)
        }
    }

    fun v(TAG: String?, msg: String?) {
        if (BuildConfig.DEBUG) Log.v(TAG, msg!!)
    }
}