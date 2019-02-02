// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMeshs.h"

UPlayerMeshs::UPlayerMeshs()
{
	faceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMesh"));
	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	upperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperMesh"));
	underMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnderMesh"));

	SetSkeletalMeshComponent(faceMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Face/1/PlayerCharacter.PlayerCharacter"));
	SetSkeletalMeshComponent(hairMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Hair/1/Hair.Hair"));
	SetSkeletalMeshComponent(upperMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Pants/1/Pants.Pants"));
	SetSkeletalMeshComponent(underMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Shirts/1/shirts2.shirts2"));

}

void UPlayerMeshs::SetSkeletalMeshComponent(USkeletalMeshComponent * skeletalMesh, const TCHAR * Channel)
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> m_Skeletal(Channel);
	if (m_Skeletal.Succeeded()) {
		skeletalMesh->SetSkeletalMesh(m_Skeletal.Object);
	}
}

void UPlayerMeshs::SetRootSkeletalMeshComponent(USkeletalMeshComponent * skeletalMesh)
{
	//skeletalMesh->SetSkeletalMesh(n);
	faceMesh->SetupAttachment(skeletalMesh);
	hairMesh->SetupAttachment(skeletalMesh);
	upperMesh->SetupAttachment(skeletalMesh);
	underMesh->SetupAttachment(skeletalMesh);
}

void UPlayerMeshs::SetAnimClass(const TCHAR * AnimChannel)
{
	static ConstructorHelpers::FClassFinder<UAnimInstance> Player_ANIM(AnimChannel);
	if (Player_ANIM.Succeeded()) {
		faceMesh->SetAnimInstanceClass(Player_ANIM.Class);
		hairMesh->SetAnimInstanceClass(Player_ANIM.Class);
		upperMesh->SetAnimInstanceClass(Player_ANIM.Class);
		underMesh->SetAnimInstanceClass(Player_ANIM.Class);
	}
}
