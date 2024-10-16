/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "LightUpdate.hpp"
#include "world/level/Level.hpp"

void LightUpdate::update(Level* pLevel)
{
	int newBr, oldBr, newBrN, tileX, x6, tileY, x14, x13, x10, v24, x21, x17_1, v27, x9, x10_1, x8, x7_1, x3, x4, tileZ, x20;
	int x19, x18, x17, x16, x5, x1_1;
	bool x11;

	if ((m_z2 - m_z1 + 1) * (m_tileX + 1 - m_tileZ + (m_y2 - m_y1) * (m_tileX + 1 - m_tileZ)) > 32768)
		return;

	if (tileX < m_tileZ)
		return;

	tileZ = m_tileZ + 1;
	for (int i = m_tileZ - 1; ; ++i)
	{
		tileX = tileZ - 1;
		if (m_z2 < m_z1)
		{
			x1_1 = tileZ;
			goto LABEL_53;
		}
		x1_1 = tileZ;
		x3 = m_z1 + 1;
		x4 = m_z1 - 1;
		do
		{
			x6 = x3 - 1;
			if (!pLevel->hasChunksAt(tileX, 0, x3 - 1, 1)
				|| pLevel->getChunk(tileX >> 4, x6 >> 4)->isEmpty())
			{
				x5 = x3;
			}
			else
			{
				if (m_y1 < 0)   m_y1 = 0;
				if (m_y2 > 127) m_y2 = 127;

				if (m_y1 <= m_y2)
				{
					tileX = m_y1 + 1;
					x8 = m_y1 - 1;
					x5 = x3;
					while (1)
					{
						oldBr = pLevel->getBrightness(*this->m_lightLayer, tileX, tileY - 1, x6);
						x13 = pLevel->getTile(tileX, tileY - 1, x6);
						x14 = Tile::lightBlock[x13];
						if (!x14)
							x14 = 1;
						if (m_lightLayer == &LightLayer::Sky)
							break;
						if (m_lightLayer != &LightLayer::Block)
							goto LABEL_30;
						x10 = Tile::lightEmission[x13];
						x11 = x10 == 0;
					LABEL_31:
						if (x14 > 14)
							v24 = x11;
						else
							v24 = 0;
						if (!v24)
						{
						LABEL_35:
							x10_1 = x10;
							x16 = pLevel->getBrightness(*m_lightLayer, i, tileY - 1, x6);
							x17 = pLevel->getBrightness(*m_lightLayer, tileZ, tileY - 1, x6);
							x7_1 = tileY;
							x18 = pLevel->getBrightness(*m_lightLayer, tileX, x8, x6);
							x19 = pLevel->getBrightness(*m_lightLayer, tileX, tileY, x6);
							x20 = pLevel->getBrightness(*m_lightLayer, tileX, tileY - 1, x4);
							x21 = pLevel->getBrightness(*m_lightLayer, tileX, tileY - 1, x3);
							x17_1 = x17;
							if (x17 < x16)
								x17_1 = x16;
							if (x17_1 < x18)
								x17_1 = x18;
							if (x17_1 < x19)
								x17_1 = x19;
							if (x17_1 < x20)
								x17_1 = x20;
							if (x17_1 < x21)
								v27 = x21 - x14;
							else
								v27 = x17_1 - x14;
							newBr = v27;
							if (newBr < 0)
								newBr = 0;
							if (newBr < x10_1)
								newBr = x10_1;
							goto LABEL_18;
						}
						newBr = 0;
						x7_1 = tileY;
					LABEL_18:
						if (newBr != oldBr)
						{
							pLevel->setBrightness(*m_lightLayer, tileX, tileY - 1, x6, newBr);
							newBrN = newBr - 1;
							if (newBrN < 0)
								newBrN = 0;
							pLevel->updateLightIfOtherThan(*m_lightLayer, i, tileY - 1, x6, newBrN);
							pLevel->updateLightIfOtherThan(*m_lightLayer, tileX, x8, x6, newBrN);
							pLevel->updateLightIfOtherThan(*m_lightLayer, tileX, tileY - 1, x4, newBrN);
							if (m_tileX <= tileZ)
								pLevel->updateLightIfOtherThan(*m_lightLayer, tileZ, tileY - 1, x6, newBrN);
							if (m_y2 <= tileY)
								pLevel->updateLightIfOtherThan(*m_lightLayer, tileX, tileY, x6, newBrN);
							if (m_z2 <= x3)
								pLevel->updateLightIfOtherThan(*m_lightLayer, tileX, tileY - 1, x3, newBrN);
						}
						++tileY;
						++x8;
						if (m_y2 < x7_1)
							goto LABEL_8;
					}
					x9 = pLevel->isSkyLit(tileX, tileY - 1, x6);
					x10 = 15;
					if (x9)
						goto LABEL_35;
				LABEL_30:
					x11 = 1;
					x10 = 0;
					goto LABEL_31;
				}
				x5 = x3;
			}
		LABEL_8:
			++x3;
			++x4;
		} while (x5 <= m_z2);
	LABEL_53:
		++tileZ;
		if (x1_1 > m_tileX)
			break;
	}
}

bool LightUpdate::expandToContain(int tileZ, int y1, int z1, int x2, int y2, int z2)
{
	if (m_tileZ <= tileZ &&
		m_y1 <= y1 &&
		m_z1 <= z1 &&
		m_tileX >= x2 &&
		m_y2 >= y2 &&
		m_z2 >= z2)
		return true;

	if (tileZ < m_tileZ - 1)  return false;
	if (y1 < m_y1 - 1)  return false;
	if (z1 < m_z1 - 1)  return false;
	if (x2 > m_tileX + 1) return false;
	if (y2 > m_y2 + 1) return false;
	if (z2 > m_z2 + 1) return false;

	if (y1 >= m_y1) y1 = m_y1;
	if (tileZ >= m_tileZ) tileZ = m_tileZ;
	if (y2 < m_y2) y2 = m_y2;
	if (z1 >= m_z1) z1 = m_z1;
	if (x2 < m_tileX) x2 = m_tileX;
	if (z2 < m_z2) z2 = m_z2;

	// If trying to add more than 2 tiles, we can't do that
	if ((z2 - z1) * (x2 - tileZ) * (y2 - y1) - (m_z2 - m_z1) * (m_tileX - m_tileZ) * (m_y2 - m_y1) > 2)
		return false;

	m_tileZ = tileZ;
	m_y1 = y1;
	m_tileX = x2;
	m_y2 = y2;
	m_z1 = z1;
	m_z2 = z2;

	return true;
}
