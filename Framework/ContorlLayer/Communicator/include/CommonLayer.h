#pragma once
#ifndef __COMMONLAYER_H
#define __COMMONLAYER_H
#include "..\..\Signal\Sender.hxx"
#include "..\..\Controler\include\VolumeRenderController.h"
#include "..\..\Controler\include\ImageFilterContorller.h"
#include "..\..\Controler\include\RoutePlanningContorller.h"

// @param sender: an sender object that programmer need to new this object.
//                also the end you will got the object act as an target function object;
// @param signal: sender's private property that act as an signal;
// @param receiver: target control lay object;
// @param method: function witch is the target control lay object;
// before call this macro , 
// step 1: new an Singnal object witch is a 'Sender<...>';
// step 2: new control lay object; 
// step 3: call sender excute functional.
// e.g:
// <--@		class TestFunc1
// <--@		{
// <--@		public:
// <--@			void FuncOfA(int parm)
// <--@			{
// <--@				parm *= 10;
// <--@				printf("enter FuncOfA parm = %d\n", parm);
// <--@			}
// <--@		};
// <--@
// <--@		class TestFunc2
// <--@		{
// <--@		public:
// <--@			void FuncOfB(int parm)
// <--@			{
// <--@				parm *= 5;
// <--@				printf("enter FuncOfB parm = %d\n", parm);
// <--@			}
// <--@		};
// <--@
// <--@		class TestFunc3
// <--@		{
// <--@		public:
// <--@			void FuncOfC(int parm, float p)
// <--@			{
// <--@				parm *= 20;
// <--@				p *= 100.0;
// <--@				printf("enter FuncOfC parm = %d\n, %f", parm, p);
// <--@			}
// <--@		};
// <--@
// <--@		class TestFunc4
// <--@		{
// <--@		public:
// <--@			void FuncOfD(int& parm)
// <--@			{
// <--@				parm *= 1000;
// <--@				printf("enter FuncOfD parm = %d\n", parm);
// <--@			}
// <--@		};
// <--@
// <--@		TestFunc1* pFunc1 = new TestFunc1;
// <--@		TestFunc2* pFunc2 = new TestFunc2;
// <--@		TestFunc3* pFunc3 = new TestFunc3;
// <--@		TestFunc4* pFunc4 = new TestFunc4;
// <--@		Sender<int>* pSignal = new Sender<int>;
// <--@		Sender<int, float>* pSignal0 = new Sender<int, float>;
// <--@		Sender<int&>* pSignal4 = new TestSignal<int&>;
// <--@
// <--@		Connect(pSignal, ValueChanged, pFunc1, &TestFunc1::FuncOfA);
// <--@		Connect(pSignal, ValueChanged, pFunc2, &TestFunc2::FuncOfB);
// <--@		Connect(pSignal0, ValueChanged, pFunc3, &TestFunc3::FuncOfC);
// <--@		Connect(pSignal4, ValueChanged, pFunc4, &TestFunc4::FuncOfD);
// <--@
// <--@		int a = 1;
// <--@		int b = 2;
// <--@		float c = 0.3f;
// <--@		pSignal->Excute(a);
// <--@		pSignal->Excute(b);
// <--@		pSignal0->Excute(b, c);
// <--@		pSignal4->Excute(a);
// <--@
// <--@		delete pSignal;
// <--@		delete pSignal0;
// <--@		delete pSignal4;
// <--@


#define Connect(sender, signal, receiver, method) ((sender)->signal.Bind(receiver, method))



#endif // !__COMMONLAYER_H
