using CppCliLib;

namespace CsWithCppCli
{
    public class Program
    {
        private static void OnAddResult(int result)
        {
            Console.WriteLine($"Callback result: {result}");
        }

        public static void Main(string[] args)
        {
            int result = SimpleNativeInterop.MathOperationMultiply(5, 10);
            Console.WriteLine($"5 * 10 = {result}");

            SimpleNativeInterop.MathOperationAdd(7, 8, OnAddResult);

            var paramsStruct = new ManagedAddParams
            {
                A = 3,
                B = 4
            };

            SimpleNativeInterop.MathOperationAddStruct(paramsStruct, OnAddResult);

            //-----------------------------------

            Console.WriteLine($"Current global variable: {SimpleNativeInterop.GetGlobalVariable()}");
            SimpleNativeInterop.SetGlobalVariable(100);
            Console.WriteLine($"Updated global variable: {SimpleNativeInterop.GetGlobalVariable()}");

            //-----------------------------------

            var data = new ManagedUpdateData
            {
                Value = 0
            };

            Console.WriteLine("Initial value: " + data.Value);
            SimpleNativeInterop.UpdateValueAfterDelay(ref data);
            Console.WriteLine("Updated value: " + data.Value);

            //-----------------------------------

            var mathOps = new MathOperationsInterop();

            int a = 10;
            int b = 5;

            Console.WriteLine($"Add: {mathOps.Add(a, b)}");
            Console.WriteLine($"Subtract: {mathOps.Subtract(a, b)}");
            Console.WriteLine($"Multiply: {mathOps.Multiply(a, b)}");
            Console.WriteLine($"Divide: {mathOps.Divide(a, b)}");

            Console.ReadKey();
        }
    }
}