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
		baseContainer.Set("weaponSlotType", "primary");		//primary right?
		//should be 10 or 11
		//Print(GetWeaponType());

		
		
		
		
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