class MW_ManualProjectileClass : ProjectileClass
{
};

class MW_ManualProjectile : Projectile 
{
	Physics addedPhysics;
	const ResourceName replaceEntityResourceName = "{81D22DE5FB6B4414}TEST2/FirstWorkingThrowingKnife.et";

	override void EOnInit(IEntity owner)
	{
		SetEventMask(EntityEvent.INIT | EntityEvent.SIMULATE | EntityEvent.CONTACT);
	}

	
	
	bool tempFixAlreadySpawned = false;
	override void EOnContact(IEntity owner, IEntity other, Contact contact)
	{
		super.EOnContact(owner, other, contact);
		
		PlayerManager pMan = GetGame().GetPlayerManager();
		SCR_PlayerController m_playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
		IEntity currentPlayer = m_playerController.GetMainEntity();
		
		Resource replaceEntityResource = Resource.Load(replaceEntityResourceName);

		
		
		if (!tempFixAlreadySpawned && other.Type() == GenericTerrainEntity)
		{
			//Print("Terrain");
			IEntity newWeapon = GetGame().SpawnEntityPrefab(replaceEntityResource, GetGame().GetWorld());
			vector currentTransform[4];
			GetTransform(currentTransform);
			
			newWeapon.SetTransform(currentTransform);
			delete owner;
			
		}
		
		
		
		if (!tempFixAlreadySpawned && other.FindComponent(CharacterControllerComponent) && currentPlayer != other)
		{
			CharacterControllerComponent cntrlComp = CharacterControllerComponent.Cast(other.FindComponent(CharacterControllerComponent));
			ChimeraCharacter chimeraOther = ChimeraCharacter.Cast(other);
			SCR_DamageManagerComponent damageManagerComponent = chimeraOther.GetDamageManager();
			array<HitZone> hitZones = {};
			damageManagerComponent.GetPhysicalHitZones(hitZones);
			vector hitzoneTransform[4];
			
			int index = 0;		//??
			float bestDifference = -1;
			
			
			
			
			int currentNodeID;
			int currentBoneIndex;

			int correctNodeID;
			int correctBoneIndex;
			
			
			
			
			
			ScriptedHitZone bestHitzone;

			//Print(contact.Position);
			foreach(HitZone hitzone : hitZones)
			{
			
				hitzone.TryGetColliderDescription(other, index, hitzoneTransform, currentBoneIndex, currentNodeID);
				vector worldTransform = other.CoordToParent(hitzoneTransform[1]);

				float currentDifference = Math.AbsFloat(contact.Position[0] - worldTransform[0]);
				if (currentDifference < 2)
				{

					if (bestDifference == -1)
						bestDifference = currentDifference;

					if (bestDifference > currentDifference)
					{
						bestDifference = currentDifference;
						correctNodeID = currentNodeID;		//node id
						correctBoneIndex = currentBoneIndex;
						bestHitzone = ScriptedHitZone.Cast(hitzone);

					}

				}
				
			}

			if (correctNodeID != 0)
			{

				IEntity spawnedKnife = GetGame().SpawnEntityPrefab(replaceEntityResource);
				float damage = Math.RandomFloat(30, 60);
				damageManagerComponent.HandleDamage(EDamageType.KINETIC, damage, contact.Normal, owner, bestHitzone, spawnedKnife, contact.Material1 , correctBoneIndex, correctNodeID);
				vector correctedCoord = other.CoordToLocal(contact.Position);
				
				
				if (correctedCoord[0] < 0)
					correctedCoord[0] = correctedCoord[0] + 0.01;
				else
					correctedCoord[0] = correctedCoord[0] - 0.01;
				
				
				correctedCoord[1] = correctedCoord[1]/5;
				
				
				if (correctedCoord[2] < 0)
					correctedCoord[2] = correctedCoord[2] + 0.01;
				else 
					correctedCoord[2] = correctedCoord[2] - 0.01;

				
				spawnedKnife.SetOrigin(correctedCoord);	
				spawnedKnife.SetYawPitchRoll(currentPlayer.GetYawPitchRoll());
				
				
				Print(spawnedKnife.GetOrigin());
				
				int testBone = 2090329209;
				other.AddChild(spawnedKnife, testBone);
				tempFixAlreadySpawned = true;
				owner.GetPhysics().SetActive(0);
				owner.SetOrigin("0 0 0");
				//delete owner;

			}
		}

	}

}

