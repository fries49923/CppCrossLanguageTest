package com.example.ktandroidcppjni

import android.util.Log
import androidx.lifecycle.ViewModel
import com.example.nativelib.AddCallback
import com.example.nativelib.AddParams
import com.example.nativelib.NativeLib
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow

class MyAddCallback : AddCallback {
    override fun onResult(result: Int) {
        Log.i("testRun", "MyAddCallback result：$result")
    }
}

class MainViewModel : ViewModel() {

    private val _showText = MutableStateFlow("")
    val showText = _showText.asStateFlow()

    private val nativeLib = NativeLib()

    init {
        _showText.value = nativeLib.stringFromJNI()
    }

    fun testRun() {

        // mathOperationMultiply
        val result = nativeLib.mathOperationMultiply(5, 10)
        Log.i("testRun", "5 * 10 = $result")

        // mathOperationAdd (使用匿名物件)
        nativeLib.mathOperationAdd(5, 6, object : AddCallback {
            override fun onResult(result: Int) {
                Log.i("testRun", "Callback result01: $result")
            }
        })

        // mathOperationAdd (不使用匿名物件)
        val callback = MyAddCallback()
        nativeLib.mathOperationAdd(6, 7, callback)

        // mathOperationAdd (轉成Lambda)
        nativeLib.mathOperationAddWithLambda(7, 8) { value ->
            Log.i("testRun", "Callback result03: $value")
        }

        // mathOperationAddStruct
        val paramsStruct = AddParams(a = 3, b = 4)
        nativeLib.mathOperationAddStructWithLambda(paramsStruct) { value ->
            Log.i("testRun", "Struct Callback result: $value")
        }

        //-----------------------------------

        // getGlobalVariable
        Log.i("testRun", "Current global variable: ${nativeLib.getGlobalVariable()}")

        // setGlobalVariable
        nativeLib.setGlobalVariable(100);
        Log.i("testRun", "Updated global variable: ${nativeLib.getGlobalVariable()}")

        //-----------------------------------

        // updateValueAfterDelay
        nativeLib.updateValueAsync { data ->
            Log.d("testRun", "updateValueAsync: = ${data.value}")
        }

        //-----------------------------------

        // MathOperations
        val a = 10;
        val b = 5;
        Log.i("testRun", "add: ${nativeLib.add(a, b)}")
        Log.i("testRun", "subtract: ${nativeLib.subtract(a, b)}")
        Log.i("testRun", "multiply: ${nativeLib.multiply(a, b)}")
        Log.i("testRun", "divide: ${nativeLib.divide(a, b)}")
    }

}