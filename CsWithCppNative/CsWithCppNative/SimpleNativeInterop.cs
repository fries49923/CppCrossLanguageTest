using System.Runtime.InteropServices;

namespace CsWithCppNative
{
    internal static class SimpleNativeInterop
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct AddParams
        {
            public int a;
            public int b;
        }

        [DllImport("CppNativeLib.dll",
            EntryPoint = "math_operation_multiply",
            CallingConvention = CallingConvention.StdCall)]
        public static extern int MathOperationMultiply(int a, int b);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void TestCallback(int result);

        [DllImport("CppNativeLib.dll",
            EntryPoint = "math_operation_add",
            CallingConvention = CallingConvention.StdCall)]
        public static extern void MathOperationAdd(int a, int b, TestCallback callback);

        [DllImport("CppNativeLib.dll",
            EntryPoint = "math_operation_add_struct",
            CallingConvention = CallingConvention.StdCall)]
        public static extern void MathOperationAdd(AddParams paramsStruct, TestCallback callback);

        //-----------------------------------

        [DllImport("CppNativeLib.dll",
            EntryPoint = "get_global_variable",
            CallingConvention = CallingConvention.StdCall)]
        public static extern int GetGlobalVariable();

        [DllImport("CppNativeLib.dll",
            EntryPoint = "set_global_variable",
            CallingConvention = CallingConvention.StdCall)]
        public static extern void SetGlobalVariable(int value);

        //-----------------------------------

        [StructLayout(LayoutKind.Sequential)]
        public struct UpdateData
        {
            public int value;
        }

        [DllImport("CppNativeLib.dll",
            EntryPoint = "update_value_after_delay",
            CallingConvention = CallingConvention.StdCall)]
        public static extern void UpdateValueAfterDelay(ref UpdateData data);

        //-----------------------------------

        public struct MathOperations
        {
            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate int DelegateAdd(int a, int b);
            public DelegateAdd Add;

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate int DelegateSubtract(int a, int b);
            public DelegateSubtract Subtract;

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate int DelegateMultiply(int a, int b);
            public DelegateMultiply Multiply;

            [UnmanagedFunctionPointer(CallingConvention.StdCall)]
            public delegate int DelegateDivide(int a, int b);
            public DelegateDivide Divide;
        }

        [DllImport("CppNativeLib.dll",
            EntryPoint = "init_math_operations",
            CallingConvention = CallingConvention.StdCall)]
        public static extern void InitMathOperations(ref MathOperations mathOps);
    }
}
