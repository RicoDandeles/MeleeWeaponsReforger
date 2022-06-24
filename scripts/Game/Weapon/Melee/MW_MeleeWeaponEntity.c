class MW_MeleeWeaponEntityClass : GenericEntityClass 
{}

class MW_MeleeWeaponEntity : GenericEntity 
{
	
	//[Attribute("", UIWidgets.ResourcePickerThumbnail, "Projectile assigned to this entity", params: "et", category : "Weapon Configuration")]
	//private ResourceName projectilePrefab;


	MuzzleInMagComponent muzzleInMagComponent; 
	WeaponComponent weaponComponent;
	AttachmentSlotComponent thrower;			//must be present in the hierarchy
	
	
	
	void MW_MeleeWeaponEntity(IEntitySource src, IEntity parent)
	{
		SetEventMask(EntityEvent.INIT|EntityEvent.SIMULATE);
	}
	
	
	
	MW_ManualProjectile meleeProjectile;			//wtf is htis
	
	override void EOnInit(IEntity owner)
	{
		
		if (FindComponent(WeaponComponent))
			weaponComponent = WeaponComponent.Cast(FindComponent(WeaponComponent));

		if (FindComponent(AttachmentSlotComponent))
		{
			thrower = AttachmentSlotComponent.Cast(FindComponent(AttachmentSlotComponent));		//this will manage the throwing part.
			IEntity attachmentThrower = thrower.GetAttachedEntity();
			

			if (attachmentThrower.FindComponent(MuzzleInMagComponent))
			{
				muzzleInMagComponent = MuzzleInMagComponent.Cast(attachmentThrower.FindComponent(MuzzleInMagComponent));
				BaseMagazineComponent t = muzzleInMagComponent.GetMagazine();
			}
		
		}
			
	
	}
	
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		
		// triggers only when the weapon is in someone's hands
		if (owner.GetParent())
		{
			ChimeraCharacter character = ChimeraCharacter.Cast(owner.GetParent());		//should be the parent?
			CharacterControllerComponent charController = character.GetCharacterController();
			
			
			if (muzzleInMagComponent)
			{
				// Force  it to UGL thrower... we need a better way to do this
				BaseMagazineComponent magazineComponent = muzzleInMagComponent.GetMagazine();		//WE NEED LOGIC TO SET PROJECTILES!!!
				charController.SetMuzzle(1);
				
				
				if (magazineComponent && !meleeProjectile)
					meleeProjectile = MW_ManualProjectile.Cast(magazineComponent.GetOwner());
				else if (!magazineComponent && meleeProjectile)
				{
					//Setup physics 
					meleeProjectile.addedPhysics = Physics.CreateDynamic(meleeProjectile, 1,  -1);			
					meleeProjectile.addedPhysics.SetInteractionLayer(EPhysicsLayerPresets.Main);
					meleeProjectile.addedPhysics.SetActive(1);
					meleeProjectile.addedPhysics.EnableGravity(true);
					
					//Launch it 
					
					vector charDirection = owner.GetYawPitchRoll();
					Print(charDirection);
					vector impulse = owner.GetTransformAxis(2);// * charDirection;
					impulse[0] = impulse[0] * 10;
					impulse[1] = impulse[1] * 10;
					impulse[2] = impulse[2] * 10;
					meleeProjectile.addedPhysics.ApplyImpulse(impulse);
					
					
					//Removes the entity from the player storage
					InventoryStorageManagerComponent inventoryComp = charController.GetInventoryStorageManager();
					BaseWeaponManagerComponent baseWeaponComp = charController.GetWeaponManagerComponent();
					baseWeaponComp.GetCurrentSlot();
					charController.SelectWeapon(null);
							
					delete owner;
					meleeProjectile = null;
					
				}	

			

				
			}
		}
		
	}
}


