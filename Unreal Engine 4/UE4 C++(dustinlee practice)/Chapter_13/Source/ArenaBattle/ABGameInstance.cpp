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
	//chapter 5
	{
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

	//chapter 6
	{
		TArray<UObject*> DefaultSubobjects;
		GetDefaultSubobjects(DefaultSubobjects);
		for (const auto& Entry : DefaultSubobjects)
		{
			AB_LOG(Warning, TEXT("DefaultSubobject:%s"), *Entry->GetClass()->GetName());
			AB_LOG(Warning, TEXT("Outer of DefaultSubobject:%s"), *Entry->GetOuter()->GetClass()->GetName());
		}

		WebConnectionNew = NewObject<UWebConnection>(this);
		AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnectionNew->GetOuter()->GetClass()->GetName());

		UWorld* CurrentWorld = GetWorld();
		for (const auto& Entry : FActorRange(CurrentWorld))
		{
			AB_LOG(Warning, TEXT("Actor:%s"), *Entry->GetName());
			TArray<UObject*>Components;
			Entry->GetDefaultSubobjects(Components);
			for (const auto&CEntry : Components)
			{
				AB_LOG(Warning, TEXT(" -- Conmpoenet:%s"), *CEntry->GetName());
			}
		}

		for (TActorIterator<AStaticMeshActor>It(CurrentWorld); It; ++It)
		{
			AB_LOG(Warning, TEXT("StaticMesh Actor: %s"), *It->GetName());
		}

		WebConnection->Host = TEXT("localhost");
		WebConnectionNew->Host = TEXT("127.0.0.1");

		for (TObjectIterator<UWebConnection>It; It; ++It)
		{
			UWebConnection* Conn = *It;
			AB_LOG(Warning, TEXT("WebConnection Object Host:%s"), *Conn->Host);
		}
	}

	//WebConnection->TokenCompleteDelegate.BindUObject(this, &UABGameInstance::RequestTokenComplete);
	WebConnection->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	WebConnection->RequestToken(TEXT("destiny)"));

	/*{
		WebConnectionNew = NewObject<UWebConnection>(this);
		WebConnectionNew->Host = TEXT("127.0.0.7");
		WebConnectionNew->URI = TEXT("/");

		FString FullPath = FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), TEXT("WebConnection.txt"));
		FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);
		if (ArWriter)
		{
			//*ArWriter << WebConnectionNew->Host;
			//*ArWriter << WebConnectionNew->URI;
			*ArWriter << *WebConnectionNew;
			ArWriter->Close();
			delete ArWriter;
			ArWriter = NULL;
		}

		TSharedPtr<FArchive>FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));
		if (FileReader.IsValid())
		{
			//FString Host;
			//FString URI;
			//*FileReader.Get() << Host;
			//*FileReader.Get() << URI;
			UWebConnection* WebConnectionFromFile = NewObject<UWebConnection>(this);
			*FileReader.Get() << *WebConnectionFromFile;
			FileReader->Close();
			AB_LOG(Warning, TEXT("WebConnection From File: Host %s, URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
			//AB_LOG(Warning, TEXT("WebConnection:Host %s,URI%s"), *Host, *URI);
		}
	}*/

	FString PackageName = TEXT("/Temp/SavedWebConnection");
	UPackage* NewPackage = CreatePackage(nullptr, *PackageName);
	WebConnectionNew = NewObject<UWebConnection>(NewPackage);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	WebConnectionNew->Host = TEXT("127.0.0.7");
	WebConnectionNew->URI = TEXT("/");
	if (UPackage::SavePackage(NewPackage, WebConnectionNew, RF_Standalone, *PackageFileName))
	{
		UPackage* SavedPackage = ::LoadPackage(NULL, *PackageFileName, LOAD_None);
		TArray<UObject*>ObjectsInPackage;
		GetObjectsWithOuter(SavedPackage, ObjectsInPackage, false);
		for (const auto& EachObject : ObjectsInPackage)
		{
			UWebConnection* WebConnectionFromFile = Cast<UWebConnection>(EachObject);
			if (WebConnectionFromFile)
			{
				AB_LOG(Warning, TEXT("WebConnection From Filr: Host %s, URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
			}
		}
	}
	// 1 단계
	AB_LOG(Warning, TEXT("*****step1*****"));
	FHouse* NewHouseAddress = new FHouse();
	AB_LOG(Warning, TEXT("New House. Size: %d"), NewHouseAddress->Size);
	if (NewHouseAddress)
	{
		delete NewHouseAddress;
		AB_LOG(Warning, TEXT("Broken My House.Size%d"), NewHouseAddress->Size);
		NewHouseAddress = nullptr;
	}
	

	// 2 단계
	AB_LOG(Warning, TEXT("******step2******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 100;
	AB_LOG(Warning, TEXT("Re bulild House. Size : %d"), NewHouseAddress->Size);
	{
		TUniquePtr<FHouse>MyHouseDeed = TUniquePtr<FHouse>(NewHouseAddress);
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("Only Mine. Size: %d"), MyHouseDeed->Size);
		}

		//TUniquePtr<FHouse>FriendHouseDeed = MyHouseDeed;	// 컴파일 에러! 단독 소유만 가능
		TUniquePtr<FHouse>FriendHouseDeed = MoveTemp(MyHouseDeed);	//집은 그대로 두고 집주인만 변경
		if (!MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("Sold My Friend.friendSize:%d"), FriendHouseDeed->Size);
		}
	}
	AB_LOG(Warning, TEXT("no paper broken house.size:%d"), NewHouseAddress->Size);
	
	
	//3단계
	AB_LOG(Warning, TEXT("*****Step3******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 150.0f;
	AB_LOG(Warning, TEXT("rebulild my house again. size:%d"), NewHouseAddress->Size);
	{
		TSharedPtr<FHouse>MyHouseDeed = MakeShareable(NewHouseAddress);	//만들어진 집을 차후에 등록
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("Share house . My house size:%d"), MyHouseDeed->Size);
			if (MyHouseDeed.IsUnique())
			{
				AB_LOG(Warning, TEXT("current only one use. myhouseSize:%d"), MyHouseDeed->Size);
			}
		}

	TSharedPtr<FHouse>FriendsHouseDeed = MyHouseDeed;
	if (!FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("friend share my house.friendsize:%d"), FriendsHouseDeed->Size);
		}

		MyHouseDeed.Reset();	//내가 집 소유권을 포기함
		if (FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("now friend only have house. friendSIze:%d"), FriendsHouseDeed->Size);
		}
		AB_LOG(Warning, TEXT("house no touch. size:%d"), NewHouseAddress->Size);
	}
	AB_LOG(Warning, TEXT("auto broken house. size:%d"), NewHouseAddress->Size);
	

	//4단계
	AB_LOG(Warning, TEXT("*****4단계*****"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 200.0f;
	AB_LOG(Warning, TEXT("house one more bulid, firstSize = %d"), NewHouseAddress->Size);

	FHouse* NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 250.0f;
	AB_LOG(Warning, TEXT("friend build self. second size=%d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("MyHouse has mine. 내집크기 : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse>FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("friend house has friend . size:%d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDead = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("friend house share paper in my house. friendsize:%d"), MyHouseDeed->OthersDead->Size);
		FriendsHouseDeed->OthersDead = MyHouseDeed;
		AB_LOG(Warning,TEXT("my house shacre paper in friendHouse. myhousesize:%d"),FriendsHouseDeed->OthersDead->Size);
	}

	AB_LOG(Warning, TEXT("paper burn my house not broken.firstHouseSIze:%d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("friendHouse not broken.secondHouseSize:%d"), NewHouseAddress2->Size);

	NewHouseAddress->OthersDead.Reset();
	AB_LOG(Warning, TEXT("friend hous broken self. secondHousesize:%d"), NewHouseAddress2->Size);
	AB_LOG(Warning, TEXT("my house broken self.firstHousesize:%d"), NewHouseAddress->Size);

	//5단게
	AB_LOG(Warning, TEXT("*****Step5*****"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 300.0f;
	AB_LOG(Warning, TEXT("last house build.firstSize:%d"), NewHouseAddress->Size);

	NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 350.0f;
	AB_LOG(Warning, TEXT("friend build again.secondHouse:%d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("MyHouse has mine. 내집크기 : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse>FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("friend house has friend . size:%d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDead = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("friend house share paper in my house. friendsize:%d"), MyHouseDeed->OthersDead->Size);
		FriendsHouseDeed->AccessHouse = MyHouseDeed;
		AB_LOG(Warning, TEXT("my house shacre paper in friendHouse. myhousesize:%d"), FriendsHouseDeed->AccessHouse.Pin()->Size);
	}

	AB_LOG(Warning, TEXT("friend hous broken auto. secondHousesize:%d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("my house broken auto.firstHousesize:%d"), NewHouseAddress2->Size);

	//6단계
	AB_LOG(Warning, TEXT("*****Step6*****"));
	WebConnectionNew = NewObject<UWebConnection>();
	WebConnectionNew->Host = TEXT("127.0.0.1");
	//WebConnectionNew->AddToRoot();
	WebConnectionNew->ConditionalBeginDestroy();
	//GetWorld()->ForceGarbageCollection(true);
	GetWorld()->GetTimerManager().SetTimer(ObjectCheckTimer, this, &UABGameInstance::CheckUObjectAlive, 1.0f, true);
}

void UABGameInstance::CheckUObjectAlive()
{
	if (!WebConnectionNew)
	{
		AB_LOG(Warning, TEXT("UnrealObject is NULL"));
		return;
	}
	if (!WebConnectionNew->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("UnrealObject isnot use"));
		return;
	}
	AB_LOG(Warning, TEXT("UnrealObject still alive.:%d"), *WebConnectionNew->Host);
}



void UABGameInstance::RequestTokenComplete(const FString & Token)
{
	AB_LOG(Warning, TEXT("Token : %s"), *Token);
}
