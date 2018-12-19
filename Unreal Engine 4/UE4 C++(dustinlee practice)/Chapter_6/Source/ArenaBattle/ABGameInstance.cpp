// Fill out your copyright notice in the Description page of Project Settings.
//#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Construcor Call! Start"));
	//매크로
	AB_LOG(Warning, TEXT("Coustructor Call Start"));
	WebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("MyWebConnection"));
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Construcor Call! End"));
	//매크로
	AB_LOG(Warning, TEXT("Constructor Call End"));
}

void UABGameInstance::Init()
{
	Super::Init();
	//UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Init!"));
	AB_LOG_CALLONLY(Warning);

	UClass* ClassInfo1 = WebConnection->GetClass();
	UClass* ClassInfo2 = UWebConnection::StaticClass();
	if (ClassInfo1 == ClassInfo2)
	{
		AB_LOG(Warning, TEXT("ClassInfo1 is name with ClassInfo2"));
	}

	for (TFieldIterator<UProperty>It(ClassInfo1); It; ++It)
	{
		AB_LOG(Warning, TEXT("Field:%s, Type:%s"), *It->GetName(), *It->GetClass()->GetName());
		UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
		if (StrProp)
		{
			AB_LOG(Warning, TEXT("Value=%s"), *StrProp->GetPropertyValue_InContainer(WebConnection));
		}
	}

	for (const auto& Entry : ClassInfo1->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function=%s"), *Entry.Name.ToString());
		UFunction* Func1 = ClassInfo1->FindFunctionByName(Entry.Name);
		if (Func1->ParmsSize == 0)
		{
			WebConnection->ProcessEvent(Func1, NULL);
		}
	}
}