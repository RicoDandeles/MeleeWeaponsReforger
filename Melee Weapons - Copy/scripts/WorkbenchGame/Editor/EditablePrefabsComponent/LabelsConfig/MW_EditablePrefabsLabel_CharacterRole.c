
[BaseContainerProps(), SCR_BaseContainerCustomTitleEnum(EEditableEntityLabel, "m_Label")]
modded class EditablePrefabsLabel_CharacterRole
{

	override void AddLabelForWeaponType(EWeaponType weaponType)
	{
		switch (weaponType)
		{
			case EWeaponType.WT_RIFLE : 
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_RIFLEMAN);
				break;
			}
			case EWeaponType.WT_MACHINEGUN : 
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_MACHINEGUNNER);
				break;
			}
			case EWeaponType.WT_ROCKETLAUNCHER : 
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_ANTITANK);
				break;
			}
			case EWeaponType.WT_GRENADELAUNCHER : 
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_GRENADIER);
				break;
			}
			case EWeaponType.WT_SNIPERRIFLE : 
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_SHARPSHOOTER);
				break;
			}
			case EWeaponType.WT_HEAVYMELEE :
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_HEAVYMELEE);
				break;
			}
			case EWeaponType.WT_LIGHTMELEE : 
			{
				m_RoleLabels.Insert(EEditableEntityLabel.ROLE_LIGHTMELEE);
				break;
			}
			
			
			
			default: 
			{
				break;
			}
		}
	}
}

