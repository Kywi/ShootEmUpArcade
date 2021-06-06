#include "NWShield.h"

#include "Engine/World.h"
#include "TimerManager.h"


ANWShield::ANWShield():
	ShieldTime(5.f)
{
}

void ANWShield::ActivateShield_Implementation(ANWPlayerPawn* PlayerPawn)
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}
	ShildForPawn = PlayerPawn;
	PlayerPawn->bCanBeDamaged = false;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	);
	AttachToActor(PlayerPawn, AttachRules);
	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &ANWShield::DeactivateShield, ShieldTime, false);
}

void ANWShield::DeactivateShield()
{
	if (!ShildForPawn) return;
	ShildForPawn->bCanBeDamaged = true;
	Destroy();
}
