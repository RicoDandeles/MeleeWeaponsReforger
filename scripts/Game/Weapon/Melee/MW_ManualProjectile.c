class MW_ManualProjectileClass : ProjectileClass
{
};

class MW_ManualProjectile : Projectile 
{
	
	ShellMoveComponent shell;		//to modify stuff in real time
	Physics addedPhysics;
	
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
		
		if (!tempFixAlreadySpawned && other.FindComponent(CharacterControllerComponent) && currentPlayer != other)
		{
			CharacterControllerComponent cntrlComp = CharacterControllerComponent.Cast(other.FindComponent(CharacterControllerComponent));
			//cntrlComp.ForceDeath();
			
			


			//we'd need a way to check for nodeid from position... todo i guess 
			

			
			
			//vector mat[4];
			//spawnedKnife.GetWorldTransform(mat);
			
			
			
			ChimeraCharacter chimeraOther = ChimeraCharacter.Cast(other);
			SCR_DamageManagerComponent damageManagerComponent = chimeraOther.GetDamageManager();


			
			
			array<HitZone> hitZones = {};
			damageManagerComponent.GetPhysicalHitZones(hitZones);
			
			
			int currentBoneIndex;
			int currentBoneId;
			vector hitzoneTransform[4];
			
			int index = 0;		//??
			float bestDifference = -1;
			int correctBoneId;

			//Print(contact.Position);
			foreach(HitZone hitzone : hitZones)
			{
			
				hitzone.TryGetColliderDescription(other, index, hitzoneTransform, currentBoneIndex, currentBoneId);
				
				vector worldTransform = other.CoordToParent(hitzoneTransform[1]);
				
				
				
				
				float currentDifference = Math.AbsFloat(contact.Position[0] - worldTransform[0]);
				if (currentDifference < 2)
				{
					
					
					
					if (bestDifference == -1)
						bestDifference = currentDifference;
				
					
					if (bestDifference > currentDifference)
					{
						bestDifference = currentDifference;
						correctBoneId = currentBoneId;

					
					}

					//Print(bestDifference);
					//bestDifference = Math.AbsFloat(contact.Position[0] - worldTransform[0];
					
					
					//Print(currentBoneId);
				}
				
				
				
				//Print(hitzoneTransform[0]);
			}
			//Print(correctBoneId);
			//Print("_____________");
						
			//deletes the knife and apply a mesh on the char 
			
			if (correctBoneId != 0)
			{
				ResourceName tmpRes = "{4572958B97361D4B}TEST2/knifeProjectile2.et";
				Resource res = Resource.Load(tmpRes);
				IEntity spawnedKnife = GetGame().SpawnEntityPrefab(res);
				//Print(spawnedKnife.GetOrigin());
				
				
				
				
				
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

