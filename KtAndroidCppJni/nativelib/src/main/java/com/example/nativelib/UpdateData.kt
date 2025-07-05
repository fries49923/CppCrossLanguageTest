package com.example.nativelib

data class UpdateData(val value: Int)

interface UpdateCallback {
    fun onResult(data: UpdateData)
}