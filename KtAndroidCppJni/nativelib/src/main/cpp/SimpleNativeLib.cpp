#include "SimpleNativeLib.h"
#include <thread>
#include <chrono>

// 簡單乘法實作
int math_operation_multiply(int a, int b) {
    return a * b;
}

// 加法並透過 callback 回傳結果
void math_operation_add(int a, int b, TestCallback callback) {
    int result = a + b;

    if (callback) {
        callback(result);
    }
}

// 使用結構進行加法，並透過 callback 回傳結果
void math_operation_add_struct(AddParams params, TestCallback callback) {
    int result = params.a + params.b;

    if (callback) {
        callback(result);
    }
}

//-----------------------------------

// 定義全域變數初始值
int global_variable = 42;

// 取得全域變數的值
int get_global_variable() {
    return global_variable;
}

// 設定全域變數的值
void set_global_variable(int value) {
    global_variable = value;
}

//-----------------------------------

// 延遲後更新傳入結構體的值
void update_value_after_delay(UpdateData* data) {
    // 要設定的新值
    int new_value = 42;

    // 延遲秒數
    int delay_seconds = 2;

    std::this_thread::sleep_for(std::chrono::seconds(delay_seconds));

    data->value = new_value;
}

//-----------------------------------

// 基本數學運算函數
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) return 0;
    return a / b;
}

// 初始化 math_operations 結構：指向對應的數學函數
void init_math_operations(MathOperations* math_ops) {
    if (math_ops) {
        math_ops->add = add;
        math_ops->subtract = subtract;
        math_ops->multiply = multiply;
        math_ops->divide = divide;
    }
}