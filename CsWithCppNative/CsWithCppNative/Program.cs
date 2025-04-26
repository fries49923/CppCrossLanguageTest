using static CsWithCppNative.SimpleNativeInterop;

namespace CsWithCppNative
{
    public class Program
    {
        private static void OnAddResult(int result)
        {
            Console.WriteLine($"Callback result: {result}");
        }

        public static void Main(string[] args)
        {
            int result = MathOperationMultiply(5, 10);
            Console.WriteLine($"5 * 10 = {result}");

            var callback = new TestCallback(OnAddResult);

            MathOperationAdd(7, 8, callback);

            var paramsStruct = new AddParams
            {
                a = 3,
                b = 4
            };

            MathOperationAdd(paramsStruct, callback);

            //-----------------------------------

            Console.WriteLine($"Current global variable: {GetGlobalVariable()}");
            SetGlobalVariable(100);
            Console.WriteLine($"Updated global variable: {GetGlobalVariable()}");

            //-----------------------------------

            var data = new UpdateData
            {
                value = 0
            };

            Console.WriteLine("Initial value: " + data.value);
            UpdateValueAfterDelay(ref data);
            Console.WriteLine("Updated value: " + data.value);

            //-----------------------------------

            var mathOps = new MathOperations();
            InitMathOperations(ref mathOps);

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