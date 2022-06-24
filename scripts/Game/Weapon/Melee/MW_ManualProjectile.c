class MW_ManualProjectileClass : ProjectileClass
{
};

class MW_ManualProjectile : Projectile 
{
	
	ShellMoveComponent shell;		//to modify stuff in real time
	Physics addedPhysics;
	const ResourceName replaceEntityResourceName = "{81D22DE5FB6B4414}TEST2/FirstWorkingThrowingKnife.et";

	override void EOnInit(IEntity owner)
	{
		//Print("Projectile Mele");
		
		
		
		// we need to ignore the player... later I guess
		SetEventMask(EntityEvent.INIT | EntityEvent.SIMULATE | EntityEvent.CONTACT);
		
		shell = ShellMoveComponent.Cast(FindComponent(ShellMoveComponent));		//everything is hidden in here... not sure if I can actually manage stuff with it.
		//Physics test = owner.GetPhysics();
		//test.Destroy();
		//owner.GetPhysics().Destroy();


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
			Print("Terrain");
			
			
			
			IEntity newWeapon = GetGame().SpawnEntityPrefab(replaceEntityResource, GetGame().GetWorld());
			
			vector currentTransform[4];
			GetTransform(currentTransform);
			
			
			newWeapon.SetTransform(currentTransform);
			
			delete owner;
			
		}
		
		
		
		if (!tempFixAlreadySpawned && other.FindComponent(CharacterControllerComponent) && currentPlayer != other)
		{
			CharacterControllerComponent cntrlComp = CharacterControllerComponent.Cast(other.FindComponent(CharacterControllerComponent));
			//cntrlComp.ForceDeath();

			
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
					{
						bestDifference = currentDifference;

					
					}
				
					
					if (bestDifference > currentDifference)
					{
						bestDifference = currentDifference;
						correctNodeID = currentNodeID;		//node id
						correctBoneIndex = currentBoneIndex;
						bestHitzone = ScriptedHitZone.Cast(hitzone);


					
					}

					//Print(bestDifference);
					//bestDifference = Math.AbsFloat(contact.Position[0] - worldTransform[0];
					
					
					//Print(currentNodeID);
				}
				
				
				
				//Print(hitzoneTransform[0]);
			}
			//Print(correctNodeID);
			//Print("_____________");
						
			//deletes the knife and apply a mesh on the char 
			
			if (correctNodeID != 0)
			{

				IEntity spawnedKnife = GetGame().SpawnEntityPrefab(replaceEntityResource);
				//Print(spawnedKnife.GetOrigin());
				
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
				//todo delete it.
				
				//array<string> colliderNames;
				//other.GetAllColliderNames(colliderNames);
				
				//SetEventMask(EntityEvent.SIMULATE );
			}


			//foreach(string cName : colliderNames)
			//{
				
			
			
			//}
			
			//mat[0] = contact.Position;
			
			//spawnedKnife.SetWorldTransform(mat);

			//spawnedKnife.SetOrigin(contact.Position);

			//spawnedKnife.SetScale(10);
			
			//set it invisible or disable it?
			//delete owner;
			
		}
		
		
		

		
	}
	
	override void EOnPhysicsActive(IEntity owner, bool activeState)
	{		
		super.EOnPhysicsActive(owner, activeState);

		//Print("Active?");
	}
	
	override void EOnSimulate(IEntity owner, float timeSlice)
	{
	
		//vector vel = addedPhysics.GetVelocity();
		//
		//if (vel[0] != 0)
		//	Print(addedPhysics.GetVelocity());

	}
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		//SetEventMask(EntityEvent.ALL);
		//Print("cmon");
		//Physics test = owner.GetPhysics();
		
		//test.Destroy();
		
		//Physics test2 = Physics.CreateDynamic(owner, 10, EPhysicsLayerPresets.Projectile);
		
		//Print(test2.GetVelocity());
	}
	
	
	
	
	
	override void EOnPostFrame(IEntity owner, float timeSlice)
	{
		//Print("PostFrame");
	}

	
	
	
}

