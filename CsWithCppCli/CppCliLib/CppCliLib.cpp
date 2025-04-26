#include "pch.h"

#include <vcclr.h>
#include "CppCliLib.h"

using namespace System::Runtime::InteropServices;

namespace CppCliLib
{

	int SimpleNativeInterop::MathOperationMultiply(int a, int b)
	{
		return math_operation_multiply(a, b);
	}

	void SimpleNativeInterop::MathOperationAdd(int a, int b, ManagedCallback^ callback)
	{
		if (callback != nullptr)
		{
			GCHandle handle = GCHandle::Alloc(callback);
			IntPtr ptr = Marshal::GetFunctionPointerForDelegate(callback);

			TestCallback nativeCallback = static_cast<TestCallback>(ptr.ToPointer());
			math_operation_add(a, b, nativeCallback);

			handle.Free();
		}
	}

	void SimpleNativeInterop::MathOperationAddStruct(ManagedAddParams params, ManagedCallback^ callback)
	{
		if (callback != nullptr)
		{
			GCHandle handle = GCHandle::Alloc(callback);
			IntPtr ptr = Marshal::GetFunctionPointerForDelegate(callback);
			TestCallback nativeCallback = static_cast<TestCallback>(ptr.ToPointer());

			AddParams nativeParams{};
			nativeParams.a = params.A;
			nativeParams.b = params.B;

			math_operation_add_struct(nativeParams, nativeCallback);

			handle.Free();
		}
	}

	//-----------------------------------

	int SimpleNativeInterop::GetGlobalVariable()
	{
		return get_global_variable();
	}

	void SimpleNativeInterop::SetGlobalVariable(int value)
	{
		set_global_variable(value);
	}

	//-----------------------------------

	void SimpleNativeInterop::UpdateValueAfterDelay(ManagedUpdateData% data)
	{
		UpdateData nativeData{};
		nativeData.value = data.Value;

		update_value_after_delay(&nativeData);
		data.Value = nativeData.value;
	}

	//-----------------------------------

	MathOperationsInterop::MathOperationsInterop()
	{
		nativeOps = new MathOperations();
		init_math_operations(nativeOps);
	}

	int MathOperationsInterop::Add(int a, int b) {
		if (nativeOps->add != nullptr) {
			return nativeOps->add(a, b);
		}
		return 0;
	}

	int MathOperationsInterop::Subtract(int a, int b) {
		if (nativeOps->subtract != nullptr) {
			return nativeOps->subtract(a, b);
		}
		return 0;
	}

	int MathOperationsInterop::Multiply(int a, int b) {
		if (nativeOps->multiply != nullptr) {
			return nativeOps->multiply(a, b);
		}
		return 0;
	}

	int MathOperationsInterop::Divide(int a, int b) {
		if (nativeOps->divide != nullptr) {
			return nativeOps->divide(a, b);
		}
		return 0;
	}
}