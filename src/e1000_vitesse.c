#include "e1000_vitesse.h"

/**
 *  setup_vitesse_phy_8584
 *  @hw: pointer to the HW structure
 *
 *  Does magic according to some spec sheet and AEWIN decoding
 **/
s32 setup_vitesse_phy_8584(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;

	DEBUGFUNC("setup_vitesse_phy_8584");
	/*
		// READ EXAMPLE
		ret_val = hw->phy.ops.read_reg(hw, 0x00, &phy_data);
		if (ret_val)
			return ret_val;
		// WRITE EXAMPLE
		ret_val = hw->phy.ops.write_reg(hw, 0x00, phy_data);
		if (ret_val)
			return ret_val;
	//*/

	//Select page 0x10[Set reg31 to 0x10]
	phy_data = 0x10;
	ret_val = hw->phy.ops.write_reg(hw, 31, phy_data);
	if (ret_val)
		return ret_val;

	//Read 19G
	ret_val = hw->phy.ops.read_reg(hw, 19, &phy_data);
	if (ret_val)
		return ret_val;

	//Config SGMII[Set bit15:14 to 00]
	phy_data = phy_data & 0x3FFF;
	ret_val = hw->phy.ops.write_reg(hw, 19, phy_data);
	if (ret_val)
		return ret_val;

	//Config 18G to 0x80F0
	phy_data = 0x80F0;
	ret_val = hw->phy.ops.write_reg(hw, 18, phy_data);
	if (ret_val)
		return ret_val;

	//Wait 18G bit 15 equals 0
	WaitBit15Zero(hw, 18);

	//Config 18G to 0x8FC1
	phy_data = 0x8FC1;
	ret_val = hw->phy.ops.write_reg(hw, 18, phy_data);
	if (ret_val)
		return ret_val;

	//Wait 18G bit 15 equals 0
	WaitBit15Zero(hw, 18);

	//Select page 0x00[Set reg31 to 0x00]
	phy_data = 0x00;
	ret_val = hw->phy.ops.write_reg(hw, 31, phy_data);
	if (ret_val)
		return ret_val;

	//Read 23G
	ret_val = hw->phy.ops.read_reg(hw, 23, &phy_data);
	if (ret_val)
		return ret_val;

	//Config 1000BASE-X[Set bit10:8 to 010]
	phy_data = (phy_data & 0xFAFF) | 0x0200;
	ret_val = hw->phy.ops.write_reg(hw, 23, phy_data);
	if (ret_val)
		return ret_val;

	//Read 0G
	ret_val = hw->phy.ops.read_reg(hw, 0, &phy_data);
	if (ret_val)
		return ret_val;

	//Set bit 15 to 1
	phy_data = (phy_data & 0x7FFF) | 0x8000;
	ret_val = hw->phy.ops.write_reg(hw, 0, phy_data);
	if (ret_val)
		return ret_val;

	//Wait 0G bit 15 equals 0
	WaitBit15Zero(hw, 0);

	return 0;
}

/**
 *  WaitBit15Zero
 *  @hw: pointer to the HW structure
 *  @reg: register to monitor
 *
 *  Waits until a specified register equals zero on bit15 (or a timeout)
 **/
void WaitBit15Zero(struct e1000_hw *hw, int reg)
{
	int i;
	u16 phy_data;

	for (i = 0; i < 20; i++)
	{
		hw->phy.ops.read_reg(hw, reg, &phy_data);
		if ((phy_data & 0x00008000) == 0)
			break;
		usleep(5000);
	}
}