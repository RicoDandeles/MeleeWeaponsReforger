//class MW_MeleeWeaponComponent : WeaponComponent
//{
	// throw melee weapons 
	
	// throw sledgehammer :)))))
	
	
	
	
	
	// override mag stuff (maybe later)
	//SCR_BaseWeaponAction

//}



modded class SCR_CharacterInventoryStorageComponent 
{
	 ref array<ref array<int>>	m_aDefaultQuickSlots = 	{{ EWeaponType.WT_RIFLE, EWeaponType.WT_SNIPERRIFLE, EWeaponType.WT_MACHINEGUN, EWeaponType.WT_LIGHTMELEE, EWeaponType.WT_HEAVYMELEE },
														{ EWeaponType.WT_RIFLE, EWeaponType.WT_ROCKETLAUNCHER, EWeaponType.WT_GRENADELAUNCHER, EWeaponType.WT_SNIPERRIFLE, EWeaponType.WT_MACHINEGUN, EWeaponType.WT_LIGHTMELEE, EWeaponType.WT_HEAVYMELEE },
														{ EWeaponType.WT_HANDGUN, EWeaponType.WT_LIGHTMELEE },
														{ EWeaponType.WT_FRAGGRENADE, EWeaponType.WT_SMOKEGRENADE },
														{ EGadgetType.CONSUMABLE + GADGET_OFFSET },
														{ EGadgetType.FLASHLIGHT + GADGET_OFFSET },
														{ EGadgetType.BINOCULARS + GADGET_OFFSET },
														{ EGadgetType.MAP + GADGET_OFFSET },
														{ EGadgetType.COMPASS + GADGET_OFFSET },
														{ EItemType.IT_NONE }};

}




modded enum EEditableEntityLabel
{
	
	//this is gonna get ugly whenever someone implements custom roles. 
	ROLE_HEAVYMELEE = 1200,
	ROLE_LIGHTMELEE = 1201
	
}



class MeleeWeaponComponentClass: WeaponComponentClass
{
};


class MeleeWeaponComponent : WeaponComponent
{
	
	
	[Attribute("0", UIWidgets.ComboBox, "Test type", "", ParamEnumArray.FromEnum(EWeaponType) )]
	int customWeaponType; 
	
	
	override void _WB_OnInit(IEntity owner, inout vector mat[4], IEntitySource src)
	{
		//Print("test");
		// no idea if there is any way to "hide" this since we cannot make it show easily. questions for later
		BaseContainer baseContainer = GetComponentSource(GetOwner());
		baseContainer.Set("WeaponType", customWeaponType);
		baseContainer.Set("WeaponSlotType", "grenade");		//grenade makes throwing actually work
		//should be 10 or 11
		//Print(GetWeaponType());
	}
	
	
	
	void MakeItThrowable()
	{
	
		//Use grenade as a starting point. 
	
	}
	
	override void _WB_OnContextMenu(IEntity owner, int id)
	{
		Print("Test OnContextMenu");

	}

	
	void Test()
	{
		/*array<ref array<IEntityComponentSource>> weaponSlotComponents = {};
		array<string> componentTypeArray = {"CharacterWeaponSlotComponent"};
		int weaponSlotCount = SCR_BaseContainerTools.FindComponentSources(entitySource, componentTypeArray, weaponSlotComponents);
		
		array<IEntityComponentSource> weaponSlotComponentSources = weaponSlotComponents.Get(0);
		
		if (!weaponSlotComponentSources)
		{
			return;
		}
		
		foreach	(IEntityComponentSource weaponSlotComponent : weaponSlotComponentSources)
		{
			ResourceName weaponPrefab;
			if (weaponSlotComponent.Get("WeaponTemplate", weaponPrefab))
			{
				if (!weaponPrefab)
				{
					continue;
				}
				
				IEntitySource weaponSource = SCR_BaseContainerTools.FindEntitySource(Resource.Load(weaponPrefab));
				if (!weaponSource)
				{
					continue;
				}
				
				IEntityComponentSource weaponComponentSource = SCR_BaseContainerTools.FindComponentSource(weaponSource, "WeaponComponent");
				if (!weaponComponentSource)
				{
					continue;
				}
				
				EWeaponType weaponType;
				if (weaponComponentSource.Get("WeaponType", weaponType))
				{
					AddLabelForWeaponType(weaponType);
				}
				
				CheckWeaponAttachments(weaponComponentSource);
			}
		}
	
	*/
	}
	

	
	//USE SET FROM IENTITYSOURCECOMPONENT 
	
	

}




class CustomCollisionTriggerComponentClass : CollisionTriggerComponentClass
{}


class CustomCollisionTriggerComponent : CollisionTriggerComponent
{

	//Print("Pls");
	override void _WB_OnInit(IEntity owner, inout vector mat[4], IEntitySource src)
	{
	
		Print("pls print");
	}

	
	//override void OnUserTrigger(IEntity owner)
	//{
	//	Print("dai");
	//}	

}


class CustomInventoryItemComponentClass : InventoryItemComponentClass 
{}


class CustomInventoryItemComponent : InventoryItemComponent
{


}



class MeleeWeaponEntityClass : GenericEntityClass 
{}

class MeleeWeaponEntity : GenericEntity 
{
	//[Attribute("", UIWidgets.ResourcePickerThumbnail, "Preview entity material", "xob")]
	//private ResourceName meshObject;
	
	
	
	SignalsComponent signalsComponent;
	
	MuzzleInMagComponent muzzleInMagComponent; 
	Physics rigidBody;
	
	Projectile copyProjectile; 
	
	
	
	
	
	
	
	WeaponComponent weaponComponent;
	AttachmentSlotComponent thrower;			//must be present in the hierarchy

	CollisionTriggerComponent collisionTrigger;
	
	
	
	void MeleeWeaponEntity(IEntitySource src, IEntity parent)
	{
		Print("Init melee weapon");
		//copyProjectile = Projectile(src, this);		//makes stuff crash if it's right here... not sure why 
		
		SetEventMask(EntityEvent.INIT|EntityEvent.SIMULATE);

		
		

	
	
		
	}
	
	
	
	MeleeProjectile t2;
	
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
	

		if (muzzleInMagComponent)
		{
			BaseMagazineComponent t = muzzleInMagComponent.GetMagazine();
			
			
			if (!t2 && t)
			{
			
				t2 = MeleeProjectile.Cast(t.GetOwner());
			}
			else if (t2 && !t)	
			{
				Print("Applying physics!");
				t2.addedPhysics = Physics.CreateDynamic(t2, 1,  -1);		
				
				t2.addedPhysics.SetInteractionLayer(EPhysicsLayerPresets.Main);
				t2.addedPhysics.SetActive(1);
				t2.addedPhysics.EnableGravity(true);
				
				
				vector impulse = owner.GetTransformAxis(2);
				
				impulse[0] = impulse[0] * 10;
				impulse[1] = 1;
				impulse[2] = impulse[2] * 10;
				Print(impulse);
				t2.addedPhysics.ApplyImpulse(impulse);
				//t2.addedPhysics.ApplyImpulse("2 2 2");
				t2 = null;
			}

						
			
		
			
			
			/*if (t2)
			{
			vector vel = t2.addedPhysics.GetVelocity();
			if (vel[0] != 0)
				Print(t2.addedPhysics.GetVelocity());
			}
			else
				t2 = MeleeProjectile.Cast(t.GetOwner());
*/
			
		
			
		//	if (t)
		//		Print(t.GetOwner());
		//	else
		//		Print("no t");
		}
		
	}
	
	override void EOnInit(IEntity owner)
	{
		//Print("yes");
		if (FindComponent(WeaponComponent))
		{
			
			weaponComponent = WeaponComponent.Cast(FindComponent(WeaponComponent));
		
		}
		else 
			Print("No wpn compnent");
		
		
		
		
		if (FindComponent(AttachmentSlotComponent))
		{
			Print("Found attachment slot");
			thrower = AttachmentSlotComponent.Cast(FindComponent(AttachmentSlotComponent));		//this will manage the throwing part.
			
			IEntity attachmentThrower = thrower.GetAttachedEntity();
			
			if (attachmentThrower)
			{
				Print("found attachment");
			}
			else
				Print("not attachment");
			
			if (attachmentThrower.FindComponent(MuzzleInMagComponent))
				{
					Print("Found muzzle in mag");
					muzzleInMagComponent = MuzzleInMagComponent.Cast(attachmentThrower.FindComponent(MuzzleInMagComponent));
				
					BaseMagazineComponent t = muzzleInMagComponent.GetMagazine();
				
				
					Print(t);
	
				
		
				}
			else 
				Print("cant find d muzzle in mag");
				
		
		
		}
		
		
		//need to set various stuff to it, like meshes, attributes, ecc.
		
	
	}
	
	override void EOnContact(IEntity owner, IEntity other, Contact contact)
	{
		Print("PLS");
	}
	
	
	//override void OnUserTrigger(IEntity owner)
	//{
	//	Print("TT");
	//}
	
	// we need to add an attachment, use m203 as a base
	
	
	//		we need to make a copy of this entity as a projectile.
	

}







class MeleeProjectileClass : ProjectileClass
{
};

class MeleeProjectile : Projectile 
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



