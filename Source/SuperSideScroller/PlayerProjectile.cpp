// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereComp"));//컴포넌트 초기화
	CollisionComp->InitSphereRadius(15.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAll");//콜리전 프로파일 지정. BlockAll:다른액터와 충돌시 OnHit반응
	CollisionComp->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);//OnComponentHit이벤트 발생시, APlayerProjectile::OnHit가 발동하도록 AddDynamic으로 지정
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;//발사체의 중력영향 제거
	ProjectileMovement->InitialSpeed = 800.f;
	ProjectileMovement->MaxSpeed = 800.f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);//RootComponent에 생성한 스태틱메시 부착 후, 월드트랜스폼을 유지
	InitialLifeSpan = 3.0f;

}
void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy) {
		Enemy->DestroyEnemy();
	}
	ExplodeProjectile();

}
void APlayerProjectile::ExplodeProjectile() {
	Destroy();
}
// Called when the game starts or when spawned



