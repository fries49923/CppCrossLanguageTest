#include <iostream>
#include "SimpleNativeLib.h"

// 定義一個 callback function
void test_callback(int result) {
    std::cout << "Callback result: " << result << std::endl;
}

int main() {
    int a = 5;
    int b = 3;

    // 測試乘法
    std::cout << "multiply: " << multiply(a, b) << std::endl;

    // 測試加法 + callback
    math_operation_add(a, b, test_callback);

    // 測試用 struct 加法 + callback
    AddParams params = {a, b};
    math_operation_add_struct(params, test_callback);

    // 測試全域變數 get/set
    std::cout << "Global Variable: " << get_global_variable() << std::endl;
    set_global_variable(100);
    std::cout << "Updated Global Variable: " << get_global_variable() << std::endl;

    // 測試延遲更新 data
    UpdateData data = {0};
    update_value_after_delay(&data);
    std::cout << "Updated Data Value: " << data.value << std::endl;

    // 測試 MathOperations
    MathOperations math_ops;
    init_math_operations(&math_ops);

    std::cout << "Add: " << math_ops.add(a, b) << std::endl;
    std::cout << "Subtract: " << math_ops.subtract(a, b) << std::endl;
    std::cout << "Multiply: " << math_ops.multiply(a, b) << std::endl;
    std::cout << "Divide: " << math_ops.divide(a, b) << std::endl;

    return 0;
}