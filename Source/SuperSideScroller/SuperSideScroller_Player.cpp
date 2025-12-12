// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"//setPlayerInputComponent 사용을 위한 헤더파일
#include "GameFramework/CharacterMovementComponent.h"//스프린트 함수에 키 바인딩을 위한 헤더파일
ASuperSideScroller_Player::ASuperSideScroller_Player() {
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}
void ASuperSideScroller_Player::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ASuperSideScroller_Player::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASuperSideScroller_Player::StopSprinting);
	PlayerInputComponent->BindAction("ThrowProjectile", IE_Pressed, this, &ASuperSideScroller_Player::ThrowProjectile);

}
void ASuperSideScroller_Player::Sprint() {
	if (!bIsSprinting) {
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}
void ASuperSideScroller_Player::StopSprinting() {
	if (bIsSprinting) {
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}
void ASuperSideScroller_Player::ThrowProjectile() {
	UE_LOG(LogTemp, Warning, TEXT("ThrowProjectile"))
}