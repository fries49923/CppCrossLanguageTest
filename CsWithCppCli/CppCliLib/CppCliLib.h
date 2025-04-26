#pragma once

#include "SimpleNativeLib.h"

using namespace System;

namespace CppCliLib
{
	public value struct ManagedAddParams
	{
		int A;
		int B;
	};

	public delegate void ManagedCallback(int result);

	public value struct ManagedUpdateData
	{
		int Value;
	};

	public ref class SimpleNativeInterop
	{
	public:
		static int MathOperationMultiply(int a, int b);
		static void MathOperationAdd(int a, int b, ManagedCallback^ callback);
		static void MathOperationAddStruct(ManagedAddParams param, ManagedCallback^ callback);

		//-----------------------------------

		static int GetGlobalVariable();
		static void SetGlobalVariable(int value);

		//-----------------------------------

		static void UpdateValueAfterDelay(ManagedUpdateData% data);

	};

	public ref class MathOperationsInterop
	{
	private:
		MathOperations* nativeOps;

	public:
		MathOperationsInterop();

		int Add(int a, int b);
		int Subtract(int a, int b);
		int Multiply(int a, int b);
		int Divide(int a, int b);
	};
}
