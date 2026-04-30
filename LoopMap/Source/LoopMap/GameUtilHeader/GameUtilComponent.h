#pragma once
#include "CoreMinimal.h"

namespace GameUtil
{
	template<typename T>
	T* CreateComponent(
		AActor* Owner, //�ʼ� Ŭ����
		bool isChild = true, //���� ���� ����
		USceneComponent* InParent = nullptr, //���� ���۷���
		FName createName = NAME_None) //�̸�
	{
		static_assert(TIsDerivedFrom<T, USceneComponent>::IsDerived, "T is Not USceneComponent");
			if (!ensureMsgf(Owner, TEXT("CreateComponent Owner Null")))
			{
				return nullptr;
			}
		FName finalName = createName;
		if (finalName.IsNone())
		{
			//�ڵ����� �̸� ����
			finalName = MakeUniqueObjectName(Owner, T::StaticClass(),
				T::StaticClass()->GetFName());
		}
		T* NewComp = Owner->CreateDefaultSubobject<T>(finalName);
		if (!ensureMsgf(NewComp, TEXT("CreateComponent CreateDefaultSubobject Failed ")))
		{
			return nullptr;
		}
		if (isChild) //���� ���� ����
		{
			if (InParent == nullptr) //���� ���۷��� üũ
			{
				InParent = Owner->GetRootComponent();
			}
			if (ensureMsgf(InParent, TEXT("GetRootComponent Parent Null")))
			{
				NewComp->SetupAttachment(InParent);
			}
		}
		else
		{
			Owner->SetRootComponent(NewComp);
		}
		return NewComp;
	} //CreateComponent
	template<typename T>
	T* CreateRootComponet(
		AActor* Owner,
		FName createName = NAME_None)
	{
		T* t = CreateComponent<T>(Owner, false, nullptr, createName);
		return t;
	}
	template<typename T>
	T* CreateComponentWithLocation(
		AActor* Owner,
		FVector vec = FVector::ZeroVector,
		bool isChild = true,
		USceneComponent* InParent = nullptr,
		FName createName = NAME_None)
	{
		T* t = CreateComponent<T>(Owner, isChild, InParent, createName);
		if (ensureMsgf(t, TEXT("GetRootComponent Parent Null")))
		{
			t->SetRelativeLocation(vec);
		}
		return t;
	}
}