class MW_MeleeWeaponEntityClass : GenericEntityClass 
{}

class MW_MeleeWeaponEntity : GenericEntity 
{
	MuzzleInMagComponent muzzleInMagComponent; 
	Projectile copyProjectile; 
	WeaponComponent weaponComponent;
	AttachmentSlotComponent thrower;			//must be present in the hierarchy
	
	
	
	void MW_MeleeWeaponEntity(IEntitySource src, IEntity parent)
	{
		Print("Init melee weapon");
		//copyProjectile = Projectile(src, this);		//makes stuff crash if it's right here... not sure why 
		
		SetEventMask(EntityEvent.INIT|EntityEvent.SIMULATE);

	}
	
	
	
	MW_ManualProjectile t2;
	
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
	

		if (muzzleInMagComponent)
		{
			BaseMagazineComponent t = muzzleInMagComponent.GetMagazine();
			
			
			if (!t2 && t)
			{
			
				t2 = MW_ManualProjectile.Cast(t.GetOwner());
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
				t2 = null;
			}
		}
		
	}
	
	override void EOnInit(IEntity owner)
	{
		
		if (FindComponent(WeaponComponent))
			weaponComponent = WeaponComponent.Cast(FindComponent(WeaponComponent));


		if (FindComponent(AttachmentSlotComponent))
		{
			Print("Found attachment slot");
			thrower = AttachmentSlotComponent.Cast(FindComponent(AttachmentSlotComponent));		//this will manage the throwing part.
			
			IEntity attachmentThrower = thrower.GetAttachedEntity();
			
			if (attachmentThrower)
			{
				if (attachmentThrower.FindComponent(MuzzleInMagComponent))
				{
					muzzleInMagComponent = MuzzleInMagComponent.Cast(attachmentThrower.FindComponent(MuzzleInMagComponent));
					BaseMagazineComponent t = muzzleInMagComponent.GetMagazine();
				}

				
			}
			
		
		
		
		}
			
	
	}
	

	
	
	//		we need to make a copy of this entity as a projectile.
	

}


