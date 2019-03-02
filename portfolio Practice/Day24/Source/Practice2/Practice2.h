// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Practice2, Log, All);

#define AB_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
// �α� ���� �Լ�(FUNCTION)�� ��������(LINE)�� ����մϴ�.

#define ABLOG_S(Verbosity) UE_LOG(Practice2,Verbosity,TEXT("%s"),*AB_LOG_CALLINFO)
// �Լ��� ��������(AB_LOG_CALLINFO)�� ���� ���������� Verbosity(Warning�� ���� ��·���)�� �޾� ����մϴ�

#define ABLOG(Verbosity,Format,...)UE_LOG(Practice2,Verbosity,TEXT("%s %s"),*AB_LOG_CALLINFO,*FString::Printf(Format,##__VA_ARGS__))
// Verbosty(Warning�� ���� ��·���)�� ��� ������ �޾� �Է¹��� īŻ�α� ������ �Է¹��� ������ ����մϴ�.

#define ABCHECK(Expr,...){if(!(Expr)){ABLOG(Error,TEXT("ASSERTION : %s"),TEXT("'"#Expr"'")); return __VA_ARGS__;}}
// ABCHECK ���� Expr�� �ƴѰ�� �αװ� ���
