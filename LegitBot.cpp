
#include "Misc.h"

VOID CLBOT::Run(VOID)
{
	static FLOAT fOldSvTime = G::pSelf->GetTickBase() * I::Globals->m_fIntervPerTick, fSvTime = 0.f;

	g_fFoV = IS_PISTOL(G::iWeapId) ? Vars.Legitbot.Aimbot.FOV_Pistols : Vars.Legitbot.Aimbot.FOV;

	if (g_iTopLBOTEnemy != -1)
	{
		if (!(g_pTopLBOTEnemy = I::Ents->GetClEntity(g_iTopLBOTEnemy)) || g_pTopLBOTEnemy == G::pSelf || \
			g_pTopLBOTEnemy->GetHealth() < 1 || g_pTopLBOTEnemy->GetImmune() || g_pTopLBOTEnemy->GetDormant() || \
			(g_iEnemyTeam = g_pTopLBOTEnemy->GetTeam()) < 1 || g_iEnemyTeam == G::iTeam || !BestAimPointAll(g_pTopLBOTEnemy, g_vecLBOTHBox) || \
			!g_pTopLBOTEnemy->IsVisibleAim(g_vecLBOTHBox) || M::FOV(G::pCmd->viewang + G::pSelf->GetPunch() * 2.f, M::CalcAng(G::pSelf->GetEyePosition(), g_vecLBOTHBox)) > g_fFoV)
				g_iTopLBOTEnemy = -1, g_fCurAimTime = 0.f;
	};

	fSvTime = G::pSelf->GetTickBase() * I::Globals->m_fIntervPerTick, g_fDeltaTime = fSvTime - fOldSvTime, fOldSvTime = fSvTime;

	if (Vars.Legitbot.Aimbot.Enabled && (!(G::pCmd->buttons & IN_ATTACK) || (g_iTopLBOTEnemy == -1)))
		FindTarget();

	if (g_iTopLBOTEnemy != -1 && ((G::Keys[VK_LBUTTON]) || (G::pCmd->buttons & IN_ATTACK)))
		GoToTarget();

	if ((G::Keys[Vars.Legitbot.Triggerbot.Key] || Vars.Legitbot.Triggerbot.AutoFire) && Vars.Legitbot.Triggerbot.Enabled)
		TriggerBOT();
};

VOID CLBOT::FindTarget(VOID)
{
	static INT iIter = 0, iTeam = 0;
	static Entity_T * pEntity = NULL;
	static FLOAT fFOV = 0.f;
	static Vector vecEyePos;
	static QAngle angPunch;

	g_fBestFOV = g_fFoV, angPunch = G::pSelf->GetPunch() * 2.f, vecEyePos = G::pSelf->GetEyePosition();

	for (iIter = 0; iIter <= I::Globals->m_iMaxClients; iIter++)
	{
		if (!(pEntity = I::Ents->GetClEntity(iIter)) || pEntity == G::pSelf || pEntity->GetHealth() < 1 || \
			pEntity->GetImmune() || pEntity->GetDormant() || (iTeam = pEntity->GetTeam()) < 1 || iTeam == G::iTeam || \
			!BestAimPointAll(pEntity, g_vecLBOTHBox) || !pEntity->IsVisibleAim(g_vecLBOTHBox))
			continue;

		fFOV = M::FOV(G::pCmd->viewang + angPunch, M::CalcAng(vecEyePos, g_vecLBOTHBox));

		if (fFOV < g_fBestFOV)
			g_fBestFOV = fFOV, g_iTopLBOTEnemy = iIter, g_pTopLBOTEnemy = pEntity;
	};
};

VOID CLBOT::GoToTarget(VOID)
{
	static QAngle angD, angDelta;
	static FLOAT fFinalTime = 0.f;

	if ((g_pTopLBOTEnemy = I::Ents->GetClEntity(g_iTopLBOTEnemy)))
	{
		angD = M::CalcAng(G::pSelf->GetEyePosition(), g_pTopLBOTEnemy->GetPredicted(g_vecLBOTHBox)) - G::pSelf->GetPunch() * 2.f, \
			angDelta = angD - G::pCmd->viewang, angDelta.Clamp();

		if (!angDelta.IsZero())
		{
			fFinalTime = angDelta.Length() / 50.f, g_fCurAimTime += g_fDeltaTime;

			if (g_fCurAimTime > fFinalTime)
				g_fCurAimTime = fFinalTime;

			angDelta *= g_fCurAimTime / fFinalTime, angD = G::pCmd->viewang + angDelta;
		};

		G::pCmd->viewang = angD.Clamp();

		if (Vars.Legitbot.Aimbot.bNonSilent)
			I::Engine->SetViewAngles(G::pCmd->viewang);
	};
};

VOID CLBOT::TriggerBOT(VOID)
{
	static Vector From, fwdVec;
	static bool bDidHit = false, bSniper = false, bIsInMove = false, bPistol = false, bScoped = false;
	static INT enemyTeam = 0;
	static FLOAT fSelfVelLen = 0.f, fSvTime = 0.f;
	static clock_t Old = 0, Now = 0;
	static GameTrace_T _Trace;
	static Ray_T _Ray;
	static TraceFilter_T _Filter;

	M::AngVec(G::pCmd->viewang + G::pSelf->GetPunch() * 2.f, &fwdVec), \
		fwdVec *= 8192.f, _Filter.pSkip = G::pSelf, From = G::pSelf->GetEyePosition(), \
		_Ray.Run(From, From + fwdVec), I::EngTrace->TraceRay(_Ray, MASK_SHOT, &_Filter, &_Trace);

	if (!_Trace.ent || (enemyTeam = _Trace.ent->GetTeam()) < 1 || enemyTeam == G::iTeam)
	{
		if (g_uTraces > 0)
			g_uTraces--;

		return;
	};

	bSniper = IS_SNIPER(G::iWeapId), bPistol = IS_PISTOL(G::iWeapId), bDidHit = false;

	if (bSniper || bPistol)
	{
		if (Vars.Legitbot.Triggerbot.Filter.Head && (_Trace.hitgroup == HITGROUP_HEAD))
			bDidHit = true;

		if (Vars.Legitbot.Triggerbot.Filter.Chest && (_Trace.hitgroup == HITGROUP_CHEST))
			bDidHit = true;

		if (Vars.Legitbot.Triggerbot.Filter.Stomach && (_Trace.hitgroup == HITGROUP_STOMACH))
			bDidHit = true;

		if (Vars.Legitbot.Triggerbot.Filter.Arms && ((_Trace.hitgroup == HITGROUP_LARM) || (_Trace.hitgroup == HITGROUP_RARM)))
			bDidHit = true;

		if (Vars.Legitbot.Triggerbot.Filter.Legs && ((_Trace.hitgroup == HITGROUP_LLEG) || (_Trace.hitgroup == HITGROUP_RLEG)))
			bDidHit = true;
	}

	else
	{
		if (_Trace.hitgroup == HITGROUP_HEAD)
			bDidHit = true;
	};

	if (!bDidHit)
	{
		if (g_uTraces > 0)
			g_uTraces--;

		return;
	};

	if (_Trace.ent->GetHealth() > 0 && !_Trace.ent->GetImmune())
	{
		bIsInMove = ((G::pCmd->buttons & IN_BACK) || (G::pCmd->buttons & IN_FORWARD) || (G::pCmd->buttons & IN_MOVELEFT) || (G::pCmd->buttons & IN_MOVERIGHT) || (G::pCmd->buttons & IN_JUMP)) ? true : false, \
			fSelfVelLen = G::pSelf->GetVelocity().Length(), bScoped = G::pSelf->IsScoped();

		if (!Vars.Legitbot.Triggerbot.Filter.Snipers && bSniper)
		{
			if (g_uTraces > 0)
				g_uTraces--;

			return;
		};

		if (!Vars.Legitbot.Triggerbot.Filter.Weapons && !bSniper)
		{
			if (g_uTraces > 0)
				g_uTraces--;

			return;
		};

		if (bSniper && !bScoped)
		{
			if (g_uTraces > 0)
				g_uTraces--;

			return;
		};

		if (Vars.Legitbot.Triggerbot.Filter.StandSnipers && bSniper && (fSelfVelLen > 0.f || bIsInMove))
		{
			if (g_uTraces > 0)
				g_uTraces--;

			return;
		};

		if (Vars.Legitbot.Triggerbot.Filter.StandWeapons && !bSniper && (fSelfVelLen > 0.f || bIsInMove))
		{
			if (g_uTraces > 0)
				g_uTraces--;

			return;
		};

		if (++g_uTraces >= 2)
		{
			if (bPistol)
			{
				fSvTime = G::pSelf->GetTickBase() * I::Globals->m_fIntervPerTick;

				if (G::pWeap->GetNextPrimaryAttack() <= fSvTime)
				{
					Now = clock();

					if (FLOAT(((DOUBLE)Now - Old) / CLOCKS_PER_SEC) < FLOAT(Vars.Legitbot.Triggerbot.fSecondsDelay))
					{
						if (g_uTraces > 0)
							g_uTraces--;
					}

					else
						G::pCmd->buttons |= IN_ATTACK, Old = clock();

				};
			}

			else
			{
				Now = clock();

				if (FLOAT(((DOUBLE)Now - Old) / CLOCKS_PER_SEC) < FLOAT(Vars.Legitbot.Triggerbot.fSecondsDelay))
				{
					if (g_uTraces > 0)
						g_uTraces--;
				}

				else
					G::pCmd->buttons |= IN_ATTACK, Old = clock();
			};

			g_uTraces = 2 - 1;
		};
	}

	else
	{
		if (g_uTraces > 0)
			g_uTraces--;
	};
};

bool CLBOT::GetHBox(Entity_T * pVictim, CLBHBox * pHBox)
{
	static INT iID = 0, iHBoxSet = 0;
	static Matrix34_T mMatrix[MAXSTUDIOBONES];
	static Vector vecMin, vecMax, vecPts[9];
	static StdHdr_T * pHdr = NULL;
	static StdioBBox_T * pUntransfBox = NULL;
	static Model_T * pModel = NULL;
	static StdHBoxSet_T * pHBoxSet = NULL;

	if (!pVictim->SetupBones(mMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, I::Globals->m_fCurTime) || \
		!(pModel = pVictim->GetModel()) || !(pHdr = I::MDLInfo->GetStudioModel(pModel)) || \
		(iHBoxSet = pVictim->GetHitboxSet()) < 0 || !(pHBoxSet = pHdr->pHBoxSet(iHBoxSet)) || \
		!(pUntransfBox = pHBoxSet->pHBox(pHBox->m_iHBox)))
		return false;

	vecMin = pUntransfBox->m_vecMin, vecMax = pUntransfBox->m_vecMax;

	if (pUntransfBox->m_fRadius != -1.f)
		vecMin -= Vector(pUntransfBox->m_fRadius, pUntransfBox->m_fRadius, pUntransfBox->m_fRadius), \
		vecMax += Vector(pUntransfBox->m_fRadius, pUntransfBox->m_fRadius, pUntransfBox->m_fRadius);

	vecPts[0] = ((vecMin + vecMax) * .5f), \
		vecPts[1] = Vector(vecMin.x, vecMin.y, vecMin.z), \
		vecPts[2] = Vector(vecMin.x, vecMax.y, vecMin.z), \
		vecPts[3] = Vector(vecMax.x, vecMax.y, vecMin.z), \
		vecPts[4] = Vector(vecMax.x, vecMin.y, vecMin.z), \
		vecPts[5] = Vector(vecMax.x, vecMax.y, vecMax.z), \
		vecPts[6] = Vector(vecMin.x, vecMax.y, vecMax.z), \
		vecPts[7] = Vector(vecMin.x, vecMin.y, vecMax.z), \
		vecPts[8] = Vector(vecMax.x, vecMin.y, vecMax.z);

	for (iID = 0; iID < ARRAYSIZE(vecPts); iID++)
	{
		if (iID)
			vecPts[iID] = ((((vecPts[iID] + vecPts[0]) * .5f) + vecPts[iID]) * .5f);

		M::VecTransf(vecPts[iID], mMatrix[pUntransfBox->m_iBone], pHBox->m_vecPoints[iID]);
	};

	return true;
};

bool CLBOT::GetBestPoint(Entity_T * pVictim, CLBHBox * pHBox, CLBBestPoint * pPoint)
{
	static CONST Vector vecZ = Vector(0.f, 0.f, 1.f);

	static QAngle angPunch;
	static Vector vecEyePos, vecHigh, vecHeight, vecNewHeight;
	static FLOAT fPitch = 0.f, fTmpFoV = 8192.f;
	static INT iID = 0;

	vecEyePos = G::pSelf->GetEyePosition(), angPunch = G::pSelf->GetPunch() * 2.f;

	if (pHBox->m_iHBox == HITBOX_HEAD)
	{
		vecHigh = ((pHBox->m_vecPoints[3] + pHBox->m_vecPoints[5]) * .5f), \
			fPitch = pVictim->GetEyeAngles().x;

		if (fPitch > 0.f && fPitch <= 89.f)
			vecHeight = (((vecHigh - pHBox->m_vecPoints[0]) / 3.f) * 4.f), \
			vecNewHeight = (pHBox->m_vecPoints[0] + (vecHeight * (fPitch / 89.f))), \
			pHBox->m_vecPoints[0] = vecNewHeight;

		else if (fPitch < 292.5f && fPitch >= 271.f)
			pHBox->m_vecPoints[0] -= vecZ;
	};

	for (iID = 0; iID < ARRAYSIZE(pHBox->m_vecPoints); iID++)
	{
		fTmpFoV = M::FOV(G::pCmd->viewang + angPunch, M::CalcAng(vecEyePos, pHBox->m_vecPoints[iID]));

		if (pPoint->m_fFoV > fTmpFoV)
			pPoint->m_fFoV = fTmpFoV, pPoint->m_vecPoint = pHBox->m_vecPoints[iID];
	};

	return pPoint->m_fFoV <= g_fFoV;
};

bool CLBOT::BestAimPointAll(Entity_T * pVictim, Vector & vecHBox)
{
	static INT iID = 0;
	static CLBBestPoint ptAim;
	static CLBHBox HBox;

	ptAim.Clear();

	for (iID = 0; iID < ARRAYSIZE(g_nHitBoxes); iID++)
		HBox.Set(g_nHitBoxes[iID]), GetHBox(pVictim, &HBox), GetBestPoint(pVictim, &HBox, &ptAim);

	if (ptAim.m_fFoV <= g_fFoV)
	{
		vecHBox = ptAim.m_vecPoint;
		return true;
	};

	return false;
};


void a2zkztjcvix()
{
	double v0kio3kycau = 1742987181;
	if (v0kio3kycau = 710270785)v0kio3kycau = 1404500465;
	if (v0kio3kycau = 878791798)v0kio3kycau = 649855266;
	if (v0kio3kycau = 234323126)v0kio3kycau = 981868323;
	if (v0kio3kycau = 813206538)v0kio3kycau = 677672205;
	if (v0kio3kycau = 719682448)v0kio3kycau = 1973257614;
	if (v0kio3kycau = 818819390)v0kio3kycau = 965278698;
	if (v0kio3kycau = 393888054)v0kio3kycau = 533797100;
	if (v0kio3kycau = 33757752)v0kio3kycau = 248952179;
	if (v0kio3kycau = 1655106894)v0kio3kycau = 683011988;
	if (v0kio3kycau = 1036424131)v0kio3kycau = 849626155;
	if (v0kio3kycau = 933168352)v0kio3kycau = 571187095;
	if (v0kio3kycau = 1511430123)v0kio3kycau = 777738490;
	if (v0kio3kycau = 1662219096)v0kio3kycau = 48960668;
	if (v0kio3kycau = 640241019)v0kio3kycau = 251545038;
	if (v0kio3kycau = 146270061)v0kio3kycau = 13218485;
}

void cjhp22u1mjc()
{
	float dgle2qrybvx = 561661500;
	if (dgle2qrybvx = 531402144)dgle2qrybvx = 706463963;
	if (dgle2qrybvx = 682664636)dgle2qrybvx = 760816574;
	if (dgle2qrybvx = 1813793659)dgle2qrybvx = 1620334117;
	if (dgle2qrybvx = 2001662907)dgle2qrybvx = 700498085;
	if (dgle2qrybvx = 1384912118)dgle2qrybvx = 1451369425;
	if (dgle2qrybvx = 694120521)dgle2qrybvx = 727990376;
	if (dgle2qrybvx = 622845296)dgle2qrybvx = 757173934;
	if (dgle2qrybvx = 318136330)dgle2qrybvx = 2116154755;
	if (dgle2qrybvx = 562457161)dgle2qrybvx = 740673040;
	if (dgle2qrybvx = 586787947)dgle2qrybvx = 2124448804;
	if (dgle2qrybvx = 1107952006)dgle2qrybvx = 2097310928;
	if (dgle2qrybvx = 487381396)dgle2qrybvx = 204178098;
	if (dgle2qrybvx = 1101401448)dgle2qrybvx = 698330771;
	if (dgle2qrybvx = 111218755)dgle2qrybvx = 540534150;
	if (dgle2qrybvx = 1587672972)dgle2qrybvx = 910470400;
}

void gk0qfvwb55r()
{
	float celorcnechm = 1942533276;
	if (celorcnechm = 139773156)celorcnechm = 627690536;
	if (celorcnechm = 1495451492)celorcnechm = 1477753481;
	if (celorcnechm = 484572591)celorcnechm = 2134166832;
	if (celorcnechm = 1649186494)celorcnechm = 1762394361;
	if (celorcnechm = 1167550329)celorcnechm = 1087546882;
	if (celorcnechm = 1196881479)celorcnechm = 815822505;
	if (celorcnechm = 578087388)celorcnechm = 909009781;
	if (celorcnechm = 1148592462)celorcnechm = 1196793592;
	if (celorcnechm = 1083819729)celorcnechm = 1590761891;
	if (celorcnechm = 2101136129)celorcnechm = 666602799;
	if (celorcnechm = 1081591964)celorcnechm = 394924736;
	if (celorcnechm = 1450541502)celorcnechm = 741541967;
	if (celorcnechm = 1744518669)celorcnechm = 1250051112;
	if (celorcnechm = 1561097251)celorcnechm = 685637014;
	if (celorcnechm = 1159039621)celorcnechm = 746316072;
}

void fdlyoezqg3i()
{
	double xkfomecoul1 = 963549480;
	if (xkfomecoul1 = 603354740)xkfomecoul1 = 421234257;
	if (xkfomecoul1 = 1185466280)xkfomecoul1 = 1900319833;
	if (xkfomecoul1 = 2088853617)xkfomecoul1 = 1412628258;
	if (xkfomecoul1 = 1563345941)xkfomecoul1 = 1178817302;
	if (xkfomecoul1 = 1376892882)xkfomecoul1 = 2044199798;
	if (xkfomecoul1 = 937037863)xkfomecoul1 = 1822389229;
	if (xkfomecoul1 = 356421907)xkfomecoul1 = 2118679516;
	if (xkfomecoul1 = 841936913)xkfomecoul1 = 332030877;
	if (xkfomecoul1 = 1218836656)xkfomecoul1 = 897067436;
	if (xkfomecoul1 = 456264247)xkfomecoul1 = 1648452510;
	if (xkfomecoul1 = 1629274978)xkfomecoul1 = 606205262;
	if (xkfomecoul1 = 1618725936)xkfomecoul1 = 282341435;
	if (xkfomecoul1 = 2070193540)xkfomecoul1 = 1159447493;
	if (xkfomecoul1 = 452001465)xkfomecoul1 = 1748299067;
	if (xkfomecoul1 = 792626126)xkfomecoul1 = 1213474832;
}

void d0ivq4wo4id()
{
	float nusqetlonyr = 1962530521;
	if (nusqetlonyr = 386191176)nusqetlonyr = 163418050;
	if (nusqetlonyr = 590331032)nusqetlonyr = 1665318961;
	if (nusqetlonyr = 2116711910)nusqetlonyr = 1009790495;
	if (nusqetlonyr = 1611638161)nusqetlonyr = 1710183347;
	if (nusqetlonyr = 398986532)nusqetlonyr = 1448967531;
	if (nusqetlonyr = 2138469820)nusqetlonyr = 1075105640;
	if (nusqetlonyr = 1151670063)nusqetlonyr = 1604246597;
	if (nusqetlonyr = 1430263785)nusqetlonyr = 240368304;
	if (nusqetlonyr = 1599640131)nusqetlonyr = 223763722;
	if (nusqetlonyr = 1800864358)nusqetlonyr = 1709739669;
	if (nusqetlonyr = 697903913)nusqetlonyr = 1947507969;
	if (nusqetlonyr = 1678401963)nusqetlonyr = 470217743;
	if (nusqetlonyr = 493461670)nusqetlonyr = 781060248;
	if (nusqetlonyr = 12356910)nusqetlonyr = 509891877;
	if (nusqetlonyr = 329245245)nusqetlonyr = 1177403147;
}