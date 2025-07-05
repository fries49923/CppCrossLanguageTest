#pragma once

#ifndef SIMPLE_NATIVE_LIB_HPP
#define SIMPLE_NATIVE_LIB_HPP

#ifdef _WIN32
// Windows平台導出符號
#define DllExport __declspec(dllexport) 
#else
#define DllExport
#define __stdcall
#endif

#ifdef __cplusplus
// 避免C++編譯器改變符號名稱，保持C ABI
extern "C" {
#endif

// 定義加法參數的結構
typedef struct {
    int a;
    int b;
} AddParams;

// 宣告乘法函數
DllExport int math_operation_multiply(int a, int b);

// 定義回呼(callback)函數型態，回傳整數結果
typedef void(* TestCallback)(int result);

// 宣告加法函數（使用 callback 傳回結果）
DllExport void math_operation_add(int a, int b, TestCallback callback);

// 宣告使用結構參數的加法函數
DllExport void math_operation_add_struct(AddParams params, TestCallback callback);

//-----------------------------------

// 宣告全域變數
extern int global_variable;

// 提供存取全域變數的函數
DllExport int get_global_variable();
DllExport void set_global_variable(int value);

//-----------------------------------

// 定義用來更新的資料結構
typedef struct {
    int value;
} UpdateData;

// 宣告延遲更新值的函數
DllExport void update_value_after_delay(UpdateData* data);

//-----------------------------------

// 定義包含數學運算的函式指標結構
typedef struct {
    int(* add)(int a, int b);
    int(* subtract)(int a, int b);
    int(* multiply)(int a, int b);
    int(* divide)(int a, int b);
} MathOperations;

// 數學運算的單獨函數宣告
DllExport int add(int a, int b);
DllExport int subtract(int a, int b);
DllExport int multiply(int a, int b);
DllExport int divide(int a, int b);

// 初始化 math_operations 結構
DllExport void init_math_operations(MathOperations* math_ops);

#ifdef __cplusplus
}
#endif

#endif