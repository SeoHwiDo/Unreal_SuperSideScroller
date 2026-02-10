// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"//setPlayerInputComponent 사용을 위한 헤더파일
#include "GameFramework/CharacterMovementComponent.h"//스프린트 함수에 키 바인딩을 위한 헤더파일
#include "Animation/AnimInstance.h"//애니메이션 몽타주 추가
#include "PlayerProjectile.h"
#include "Engine/World.h"//FActorSpawnParam 사용을 위한 헤더파일
#include "Components/SphereComponent.h"

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
	if (ThrowMontage) {//유효성 확인. NULL 객체 사용시 크래시 유발 위험
		bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlaying) {
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 1.0f);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Throwing Projectile"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Null Montage"));
	}
}
void ASuperSideScroller_Player::SpawnProjectile() {
	if (PlayerProjectile) {
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			FRotator SpawnRotation = this->GetActorForwardVector().Rotation();
			APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, SpawnRotation, SpawnParams);
			if (Projectile) {
				Projectile->CollisionComp->MoveIgnoreActors.Add(SpawnParams.Owner);//발사체(projectile)이 무시할 액터 배열에 플레이어 추가
			}
		}
	}
}
