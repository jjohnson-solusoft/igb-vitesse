#ifndef _E1000_VITESSE_H_
#define _E1000_VITESSE_H_


#define VSC8584_E_PHY_ID	0x000707C0
#define VSC_VENDOR 			0x0007
/*
s32 e1000_check_polarity_vsc8584(struct e1000_hw *hw);
s32 e1000_get_phy_info_vsc8584(struct e1000_hw *hw);
*/
s32 setup_vitesse_phy_8584(struct e1000_hw *hw);

#endif
