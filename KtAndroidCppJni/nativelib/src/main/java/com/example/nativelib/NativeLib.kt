package com.example.nativelib

interface AddCallback {
    fun onResult(result: Int)
}

data class AddParams(val a: Int, val b: Int)

class NativeLib {

    /**
     * A native method that is implemented by the 'nativelib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    //-----------------------------------

    external fun mathOperationMultiply(a: Int, b: Int): Int

    external fun mathOperationAdd(a: Int, b: Int, callback: AddCallback)
    fun mathOperationAddWithLambda(a: Int, b: Int, onResult: (Int) -> Unit) {
        mathOperationAdd(a, b, object : AddCallback {
            override fun onResult(result: Int) {
                onResult(result)
            }
        })
    }

    external fun mathOperationAddStruct(params: AddParams, callback: AddCallback)
    fun mathOperationAddStructWithLambda(params: AddParams, onResult: (Int) -> Unit) {
        mathOperationAddStruct(params, object : AddCallback {
            override fun onResult(result: Int) {
                onResult(result)
            }
        })
    }

    //-----------------------------------

    external fun getGlobalVariable(): Int

    external fun setGlobalVariable(value: Int)

    //-----------------------------------

    // 與cpp底層略有不同，主要考慮語言特性
    external fun updateValueAsync(callback: UpdateCallback)
    fun updateValueAsync(onResult: (UpdateData) -> Unit) {
        updateValueAsync(object : UpdateCallback {
            override fun onResult(data: UpdateData) {
                onResult(data)
            }
        })
    }

    //-----------------------------------

    external fun add(a: Int, b: Int): Int

    external fun subtract(a: Int, b: Int): Int

    external fun multiply(a: Int, b: Int): Int

    external fun divide(a: Int, b: Int): Int

    //-----------------------------------

    companion object {
        // Used to load the 'nativelib' library on application startup.
        init {
            System.loadLibrary("nativelib")
        }
    }
}