// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMeshs.h"

UPlayerMeshs::UPlayerMeshs()
{
	faceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMesh"));
	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	upperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperMesh"));
	underMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnderMesh"));

	SetSkeletalMeshComponent(faceMesh, TEXT("/Game/PlayerCharacter/Mesh/Face/Face.Face"));
	SetSkeletalMeshComponent(hairMesh, TEXT("/Game/PlayerCharacter/Mesh/Hair/1/Hair.Hair"));
	SetSkeletalMeshComponent(upperMesh, TEXT("/Game/PlayerCharacter/Mesh/Shirts/1/shirts2.shirts2"));
	SetSkeletalMeshComponent(underMesh, TEXT("/Game/PlayerCharacter/Mesh/Pants/1/Pants.Pants"));

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
	skeletalMesh->SetSkeletalMesh(faceMesh->SkeletalMesh);
	faceMesh->SetupAttachment(skeletalMesh);
	hairMesh->SetupAttachment(skeletalMesh);
	upperMesh->SetupAttachment(skeletalMesh);
	underMesh->SetupAttachment(skeletalMesh);
}
