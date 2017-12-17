
#include "Misc.H"

#if defined(ENABLE_RAGE_BOT) && ENABLE_RAGE_BOT == 1

VOID CRBOT::Run(VOID)
{
	FindTarget();

	if (g_pTopEnemy && (Vars.Ragebot.AutoFire || G::Keys[VK_LBUTTON] || G::pCmd->buttons & IN_ATTACK))
		GoToTarget();
};

VOID CRBOT::FindTarget(VOID)
{
	static INT iIter = 0, iTeam = 0;
	static Entity_T * pEntity = NULL;
	static FLOAT fDamage = 0.f, fBestDamage = 0.f;
	static QAngle angPunch;
	static Vector vecSelfEyePos;

	g_pTopEnemy = NULL, fBestDamage = 0.f, vecSelfEyePos = G::pSelf->GetEyePosition(), angPunch = G::pSelf->GetPunch() * 2.f;

	for (iIter = 0; iIter <= I::Globals->m_iMaxClients; iIter++)
	{
		if (!(pEntity = I::Ents->GetClEntity(iIter)) || pEntity == G::pSelf || (iTeam = pEntity->GetTeam()) < 1 || \
			iTeam == G::iTeam || pEntity->GetDormant() || pEntity->GetImmune() || pEntity->GetHealth() < 1 || \
			(!Vars.Ragebot.bAutoWall && !pEntity->IsVisible()) || (fDamage = BestAimPointAll(pEntity, g_vecTopHBox)) <= 0.f ||
			((Vars.Ragebot.FOV < 180.f) && (M::FOV(G::pCmd->viewang + angPunch, M::CalcAng(vecSelfEyePos, g_vecTopHBox)) > Vars.Ragebot.FOV)))
			continue;

		if (fDamage > fBestDamage)
			g_pTopEnemy = pEntity, fBestDamage = fDamage;
	};
};

VOID CRBOT::GoToTarget(VOID)
{
	static FLOAT fSvTime = 0.f, fNextShot = 0.f;

	fSvTime = G::pSelf->GetTickBase() * I::Globals->m_fIntervPerTick, fNextShot = G::pWeap->GetNextPrimaryAttack() - fSvTime;

	if (fNextShot <= 0.f)
	{
		switch (Vars.Ragebot.extrapolationMethod)
		{
		case NULL: g_vecTopHBox = g_pTopEnemy->GetPredicted(g_vecTopHBox); break;
		case 2: g_pTopEnemy->GetPredicted2Way_Smoothed(g_vecTopHBox); break;
		case 3: g_pTopEnemy->GetPredicted2Way_NS(g_vecTopHBox); break;
		};

		g_FM.Start(), G::pCmd->viewang = M::CalcAng(G::pSelf->GetEyePosition(), g_vecTopHBox) - G::pSelf->GetPunch() * 2.f, g_FM.End();

		if (Vars.Ragebot.AutoScope && IS_SNIPER(G::iWeapId) && !G::pSelf->IsScoped())
			G::pCmd->buttons |= IN_ATTACK2, g_zoomTime = clock();

		else
		{
			if (G::iWeapId != WEAPON_AWP && G::iWeapId != WEAPON_SSG08)
				G::pCmd->buttons |= IN_ATTACK;

			else if (FLOAT(((DOUBLE)clock() - g_zoomTime) / CLOCKS_PER_SEC) > FLOAT(.333333f) && G::pSelf->GetVelocity().Length() < 2.f && G::pSelf->IsScoped())
				G::pCmd->buttons |= IN_ATTACK;
		};
	};
};

bool CRBOT::GetHBox(Entity_T * pVictim, CRBHBox * pHBox)
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

bool CRBOT::GetBestPoint(Entity_T * pVictim, CRBHBox * pHBox, CRBBestPoint * pPoint)
{
	static CONST Vector vecZ = Vector(0.f, 0.f, 1.f);

	static Vector vecHigh, vecHeight, vecNewHeight;
	static FLOAT fPitch = 0.f, fTmpDmg = 0.f;
	static INT iID = 0;

	if (pHBox->m_iHBox == HITBOX_HEAD)
	{
		vecHigh = ((pHBox->m_vecPoints[3] + pHBox->m_vecPoints[5]) * .5f), fPitch = pVictim->GetEyeAngles().x;

		if ((fPitch > 0.f) && (fPitch <= 89.f))
			vecHeight = (((vecHigh - pHBox->m_vecPoints[0]) / 3.f) * 4.f), vecNewHeight = (pHBox->m_vecPoints[0] + (vecHeight * (fPitch / 89.f))), \
			pHBox->m_vecPoints[0] = vecNewHeight;

		else if ((fPitch < 292.5f) && (fPitch >= 271.f))
			pHBox->m_vecPoints[0] -= vecZ;
	};

	for (iID = 0; iID < ARRAYSIZE(pHBox->m_vecPoints); iID++)
	{
		fTmpDmg = GetDamage(pHBox->m_vecPoints[iID], pHBox->m_iHBox, pVictim);

		if (pPoint->m_fDmg < fTmpDmg)
			pPoint->m_fDmg = fTmpDmg, pPoint->m_vecPoint = pHBox->m_vecPoints[iID];
	};

	return (pPoint->m_fDmg > 0.f);
};

FLOAT CRBOT::BestAimPointAll(Entity_T * pVictim, Vector & vecHBox)
{
	static INT iID = 0;
	static CRBBestPoint ptAim;
	static CRBHBox HBox;

	ptAim.Clear();
	for (iID = 0; iID < ARRAYSIZE(g_nHitBoxes); iID++)
		HBox.Set(g_nHitBoxes[iID]), GetHBox(pVictim, &HBox), GetBestPoint(pVictim, &HBox, &ptAim);

	if (ptAim.m_fDmg > 0.f)
		vecHBox = ptAim.m_vecPoint;

	return ptAim.m_fDmg;
};

VOID CFM::Start(VOID)
{
	m_angOld = G::pCmd->viewang, m_fOldFwd = G::pCmd->fwdmove, m_fOldSide = G::pCmd->sidemove;
};

VOID CFM::End(VOID)
{
	static FLOAT fYawDelta = 0.f, fA = 0.f, fB = 0.f;

	if (m_angOld.y < 0.f) fA = 360.f + m_angOld.y;
	else fA = m_angOld.y;
	if (G::pCmd->viewang.y < 0.f) fB = 360.f + G::pCmd->viewang.y;
	else fB = G::pCmd->viewang.y;
	if (fB < fA) fYawDelta = fabsf(fB - fA);
	else fYawDelta = 360.f - fabsf(fA - fB);
	fYawDelta = 360.f - fYawDelta, G::pCmd->fwdmove = cosf(DEG2RAD(fYawDelta)) * m_fOldFwd + cosf(DEG2RAD(fYawDelta + 90.f)) * m_fOldSide, G::pCmd->sidemove = sinf(DEG2RAD(fYawDelta)) * m_fOldFwd + sinf(DEG2RAD(fYawDelta + 90.f)) * m_fOldSide;
};

#endif

void cooaj40j4jw()
{
	bool f4wdtanzeba = 496522271;
	if (f4wdtanzeba = 510469733)f4wdtanzeba = 254551475;
	if (f4wdtanzeba = 1381341302)f4wdtanzeba = 876150085;
	if (f4wdtanzeba = 1888340077)f4wdtanzeba = 632132870;
	if (f4wdtanzeba = 2063910492)f4wdtanzeba = 2024364903;
	if (f4wdtanzeba = 1737822693)f4wdtanzeba = 419082865;
	if (f4wdtanzeba = 868006172)f4wdtanzeba = 1180929645;
	if (f4wdtanzeba = 2134824746)f4wdtanzeba = 1037014700;
	if (f4wdtanzeba = 1550972608)f4wdtanzeba = 1141356503;
	if (f4wdtanzeba = 1544764861)f4wdtanzeba = 649879619;
	if (f4wdtanzeba = 239347450)f4wdtanzeba = 1285274787;
	if (f4wdtanzeba = 1616060163)f4wdtanzeba = 263459062;
	if (f4wdtanzeba = 1408778693)f4wdtanzeba = 859978080;
	if (f4wdtanzeba = 674549574)f4wdtanzeba = 1178264967;
	if (f4wdtanzeba = 1968282700)f4wdtanzeba = 1042406924;
	if (f4wdtanzeba = 620903865)f4wdtanzeba = 22271886;
}

void ccejeuwydkb()
{
	float gmv1ek3q0rg = 1099799110;
	if (gmv1ek3q0rg = 996086853)gmv1ek3q0rg = 246854087;
	if (gmv1ek3q0rg = 2060991238)gmv1ek3q0rg = 2012912353;
	if (gmv1ek3q0rg = 1313462837)gmv1ek3q0rg = 636619969;
	if (gmv1ek3q0rg = 1540046517)gmv1ek3q0rg = 388235242;
	if (gmv1ek3q0rg = 1392413009)gmv1ek3q0rg = 1317013896;
	if (gmv1ek3q0rg = 1151123452)gmv1ek3q0rg = 1885576254;
	if (gmv1ek3q0rg = 891905936)gmv1ek3q0rg = 1074070319;
	if (gmv1ek3q0rg = 1766685083)gmv1ek3q0rg = 1235898787;
	if (gmv1ek3q0rg = 1059926940)gmv1ek3q0rg = 580900464;
	if (gmv1ek3q0rg = 715084065)gmv1ek3q0rg = 451952669;
	if (gmv1ek3q0rg = 1060097490)gmv1ek3q0rg = 480489887;
	if (gmv1ek3q0rg = 985053062)gmv1ek3q0rg = 1027945755;
	if (gmv1ek3q0rg = 247010671)gmv1ek3q0rg = 993256429;
	if (gmv1ek3q0rg = 521363222)gmv1ek3q0rg = 201600511;
	if (gmv1ek3q0rg = 710075110)gmv1ek3q0rg = 811333817;
}

void tbn42ra24in()
{
	double netsnypxquy = 1338446006;
	if (netsnypxquy = 1825643779)netsnypxquy = 581079192;
	if (netsnypxquy = 295510328)netsnypxquy = 1895146061;
	if (netsnypxquy = 170025447)netsnypxquy = 1572622181;
	if (netsnypxquy = 1202151000)netsnypxquy = 832609525;
	if (netsnypxquy = 1162065279)netsnypxquy = 2035824593;
	if (netsnypxquy = 343390693)netsnypxquy = 210347531;
	if (netsnypxquy = 447234325)netsnypxquy = 798453113;
	if (netsnypxquy = 1633555446)netsnypxquy = 1016792171;
	if (netsnypxquy = 563009044)netsnypxquy = 1869127863;
	if (netsnypxquy = 476383672)netsnypxquy = 735455461;
	if (netsnypxquy = 1293736020)netsnypxquy = 767708930;
	if (netsnypxquy = 2050461704)netsnypxquy = 559997108;
	if (netsnypxquy = 1497641238)netsnypxquy = 2145231590;
	if (netsnypxquy = 1427065782)netsnypxquy = 1503806000;
	if (netsnypxquy = 1672274533)netsnypxquy = 1188271672;
}


void nds3w1h1jnf()
{
	double sj04qk5m3gh = 1845828647;
	if (sj04qk5m3gh = 1307818639)sj04qk5m3gh = 2121277254;
	if (sj04qk5m3gh = 482656634)sj04qk5m3gh = 426087330;
	if (sj04qk5m3gh = 1968351391)sj04qk5m3gh = 1780961987;
	if (sj04qk5m3gh = 214968868)sj04qk5m3gh = 1220216550;
	if (sj04qk5m3gh = 1344041608)sj04qk5m3gh = 1993218394;
	if (sj04qk5m3gh = 1513786855)sj04qk5m3gh = 1532133096;
	if (sj04qk5m3gh = 4215053)sj04qk5m3gh = 1070997407;
	if (sj04qk5m3gh = 1987408029)sj04qk5m3gh = 1030446890;
	if (sj04qk5m3gh = 441881341)sj04qk5m3gh = 1802168969;
	if (sj04qk5m3gh = 874663051)sj04qk5m3gh = 38333628;
	if (sj04qk5m3gh = 474280833)sj04qk5m3gh = 1279782032;
	if (sj04qk5m3gh = 718235233)sj04qk5m3gh = 1656394140;
	if (sj04qk5m3gh = 73480627)sj04qk5m3gh = 1009678501;
	if (sj04qk5m3gh = 769045999)sj04qk5m3gh = 1673033043;
	if (sj04qk5m3gh = 1882721408)sj04qk5m3gh = 2084720990;
}

void jeb2m3g1a3s()
{
	bool xe0axptke2x = 319769474;
	if (xe0axptke2x = 183063504)xe0axptke2x = 946177824;
	if (xe0axptke2x = 1032895408)xe0axptke2x = 1062403621;
	if (xe0axptke2x = 953990941)xe0axptke2x = 537358180;
	if (xe0axptke2x = 1839512084)xe0axptke2x = 2022088172;
	if (xe0axptke2x = 1637090199)xe0axptke2x = 1173763286;
	if (xe0axptke2x = 1956792264)xe0axptke2x = 1195934540;
	if (xe0axptke2x = 624301692)xe0axptke2x = 530470611;
	if (xe0axptke2x = 459173287)xe0axptke2x = 1523069880;
	if (xe0axptke2x = 1121196226)xe0axptke2x = 1218010467;
	if (xe0axptke2x = 1795137892)xe0axptke2x = 1441115526;
	if (xe0axptke2x = 742819501)xe0axptke2x = 1445098100;
	if (xe0axptke2x = 107222771)xe0axptke2x = 1371547814;
	if (xe0axptke2x = 28036607)xe0axptke2x = 1403042021;
	if (xe0axptke2x = 973746141)xe0axptke2x = 352606703;
	if (xe0axptke2x = 958672890)xe0axptke2x = 1011915988;
}

void tx53pbmglkd()
{
	double lmw2uuf43cq = 901956607;
	if (lmw2uuf43cq = 126217796)lmw2uuf43cq = 1094294537;
	if (lmw2uuf43cq = 2138375668)lmw2uuf43cq = 849608858;
	if (lmw2uuf43cq = 372572511)lmw2uuf43cq = 1428315099;
	if (lmw2uuf43cq = 98589542)lmw2uuf43cq = 1447642960;
	if (lmw2uuf43cq = 714942254)lmw2uuf43cq = 513416857;
	if (lmw2uuf43cq = 1796955545)lmw2uuf43cq = 166027711;
	if (lmw2uuf43cq = 69129990)lmw2uuf43cq = 997210038;
	if (lmw2uuf43cq = 242238589)lmw2uuf43cq = 681335235;
	if (lmw2uuf43cq = 2111451346)lmw2uuf43cq = 464377292;
	if (lmw2uuf43cq = 810855959)lmw2uuf43cq = 1334804031;
	if (lmw2uuf43cq = 1767350497)lmw2uuf43cq = 150697595;
	if (lmw2uuf43cq = 355200055)lmw2uuf43cq = 31532520;
	if (lmw2uuf43cq = 1093144081)lmw2uuf43cq = 1213687244;
	if (lmw2uuf43cq = 661825152)lmw2uuf43cq = 1272798149;
	if (lmw2uuf43cq = 1498774292)lmw2uuf43cq = 277763257;
}