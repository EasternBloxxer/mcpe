/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once

#include "Screen.hpp"

class ProgressScreen : public Screen
{
public:
	void render(int, int, float) override;
	bool isInGameScreen() override;
};

