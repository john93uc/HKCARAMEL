
#include "Misc.h"

bool TraceToExit(Vector & vecEnd, GameTrace_T & xEnterTrace, FLOAT fX, FLOAT fY, FLOAT fZ, FLOAT fDirX, FLOAT fDirY, FLOAT fDirZ, GameTrace_T * pExitTrace)
{
	typedef bool(__fastcall * TTE) (Vector &, GameTrace_T &, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, GameTrace_T *);

	static TTE pFN = TTE(FindPattern(XorString("client.dll"), XorString("55 8B EC 83 EC 30 F3 0F 10 75")));

	if (!pFN)
		return false;

	_asm
	{
		push pExitTrace
		push fDirZ
		push fDirY
		push fDirX
		push fZ
		push fY
		push fX
		mov edx, xEnterTrace
		mov ecx, vecEnd
		call pFN
		add esp, 0x0000001C
	};
};

FLOAT GetDamage(Vector & vecPoint, INT iHBoxID, Entity_T * pEntity)
{
	static Vector vecStart, vecDir, vecDummy;
	static INT iTeam = 0;
	static GameTrace_T xTrace, xExitTrace;
	static FLOAT fWallLen = 0.f, fDamage[128] = { 0.f };
	static clock_t tArray[128][8], tNow = 0;

	vecStart = G::pSelf->GetEyePosition(), M::AngVec(M::CalcAng(vecStart, vecPoint), &vecDir), vecDir *= 8192.f;

	TraceLine(vecStart, vecStart + vecDir, MASK_SHOT, G::pSelf, &xTrace);

	if (xTrace.hitgroup > HITGROUP_NO)
	{
		if (xTrace.ent && ((iTeam = xTrace.ent->GetTeam()) < 2 || iTeam == G::iTeam || iTeam > 3))
			return (fDamage[pEntity->m_iId] = 0.f);

		switch (xTrace.hitgroup)
		{
		case HITGROUP_HEAD: fDamage[pEntity->m_iId] = 40.f;
		case HITGROUP_STOMACH: fDamage[pEntity->m_iId] = 30.f;
		case HITGROUP_CHEST: case HITGROUP_LARM: case HITGROUP_RARM: fDamage[pEntity->m_iId] = 20.f;
		case HITGROUP_LLEG: case HITGROUP_RLEG: fDamage[pEntity->m_iId] = 10.f;
		};

		return fDamage[pEntity->m_iId];
	};

	if (iHBoxID != HITBOX_HEAD && iHBoxID != HITBOX_CHEST)
		return (fDamage[pEntity->m_iId] = 0.f);

	if (G::iWeapId != WEAPON_DEAGLE && G::iWeapId != WEAPON_SCAR20 && G::iWeapId != WEAPON_G3SG1 && \
		G::iWeapId != WEAPON_SSG08 && G::iWeapId != WEAPON_AWP && G::iWeapId != WEAPON_AUG && \
		G::iWeapId != WEAPON_SG556 && G::iWeapId != WEAPON_M4A1_SILENCER && G::iWeapId != WEAPON_M4A1 && \
		G::iWeapId != WEAPON_AK47 && G::iWeapId != WEAPON_M249)
		return (fDamage[pEntity->m_iId] = 0.f);

	tNow = clock();

	if (FLOAT(((DOUBLE)tNow - tArray[pEntity->m_iId][iHBoxID]) / CLOCKS_PER_SEC) > FLOAT(.1f))
	{
		tArray[pEntity->m_iId][iHBoxID] = tNow, vecDummy.Zero();

		if (!TraceToExit(vecDummy, xTrace, xTrace.endpos.x, xTrace.endpos.y, xTrace.endpos.z, vecDir.x, vecDir.y, vecDir.z, &xExitTrace))
			return (fDamage[pEntity->m_iId] = 0.f);

		fWallLen = (xExitTrace.endpos - xTrace.endpos).Length();

		if (g_fMaxWallLen == 0.f)
		{
			g_fMaxWallLen = fWallLen;
			return (fDamage[pEntity->m_iId] = 0.f);
		};

		if (fWallLen > g_fMaxWallLen)
			g_fMaxWallLen = fWallLen;

		if (fWallLen < g_fMaxWallLen / 2.f)
		{
			TraceLine(xExitTrace.endpos, xExitTrace.endpos + vecDir, MASK_SHOT, G::pSelf, &xTrace);

			if (xTrace.hitgroup > HITGROUP_NO)
				return (fDamage[pEntity->m_iId] = ((xTrace.hitgroup == HITGROUP_HEAD) ? 5.f : 1.f));

			return (fDamage[pEntity->m_iId] = 0.f);
		};

		return (fDamage[pEntity->m_iId] = 0.f);
	};

	return fDamage[pEntity->m_iId];
};


void mmkuxhaflaj()
{
	bool tilzovpehst = 252364512;
	if (tilzovpehst = 632400878)tilzovpehst = 1869908907;
	if (tilzovpehst = 510704069)tilzovpehst = 301397352;
	if (tilzovpehst = 2027213043)tilzovpehst = 1548599278;
	if (tilzovpehst = 748576475)tilzovpehst = 1100313535;
	if (tilzovpehst = 2027258398)tilzovpehst = 950329331;
	if (tilzovpehst = 1427909437)tilzovpehst = 2008979742;
	if (tilzovpehst = 3447651)tilzovpehst = 377566525;
	if (tilzovpehst = 1035587893)tilzovpehst = 1531901680;
	if (tilzovpehst = 1194704084)tilzovpehst = 1749992433;
	if (tilzovpehst = 1435538341)tilzovpehst = 252496973;
	if (tilzovpehst = 898193602)tilzovpehst = 1400965391;
	if (tilzovpehst = 161895771)tilzovpehst = 468425857;
	if (tilzovpehst = 76431993)tilzovpehst = 1031383045;
	if (tilzovpehst = 250382457)tilzovpehst = 859297819;
	if (tilzovpehst = 358911383)tilzovpehst = 132323881;
}

void dnxvhuqk0wr()
{
	bool nl1ugdqhiac = 2036762303;
	if (nl1ugdqhiac = 741402152)nl1ugdqhiac = 1894934517;
	if (nl1ugdqhiac = 1215764926)nl1ugdqhiac = 1632526485;
	if (nl1ugdqhiac = 400500073)nl1ugdqhiac = 105635149;
	if (nl1ugdqhiac = 355721367)nl1ugdqhiac = 768003245;
	if (nl1ugdqhiac = 1842114938)nl1ugdqhiac = 1174226469;
	if (nl1ugdqhiac = 1924261054)nl1ugdqhiac = 1136453324;
	if (nl1ugdqhiac = 1646791083)nl1ugdqhiac = 770046621;
	if (nl1ugdqhiac = 819229617)nl1ugdqhiac = 990146595;
	if (nl1ugdqhiac = 1718181678)nl1ugdqhiac = 1396201175;
	if (nl1ugdqhiac = 706912304)nl1ugdqhiac = 238425157;
	if (nl1ugdqhiac = 1481831493)nl1ugdqhiac = 1264487168;
	if (nl1ugdqhiac = 650650250)nl1ugdqhiac = 1794574221;
	if (nl1ugdqhiac = 333932827)nl1ugdqhiac = 306384877;
	if (nl1ugdqhiac = 543641592)nl1ugdqhiac = 790409671;
	if (nl1ugdqhiac = 707055159)nl1ugdqhiac = 1794992177;
}

void dnlg2qa2hrv()
{
	double txnkgo2elrm = 1942995903;
	if (txnkgo2elrm = 977385028)txnkgo2elrm = 1148351843;
	if (txnkgo2elrm = 863910881)txnkgo2elrm = 1534228476;
	if (txnkgo2elrm = 834284904)txnkgo2elrm = 103467897;
	if (txnkgo2elrm = 1412684988)txnkgo2elrm = 427214392;
	if (txnkgo2elrm = 218835592)txnkgo2elrm = 1803719580;
	if (txnkgo2elrm = 756946728)txnkgo2elrm = 1547276571;
	if (txnkgo2elrm = 454930809)txnkgo2elrm = 310696424;
	if (txnkgo2elrm = 472480448)txnkgo2elrm = 1802787356;
	if (txnkgo2elrm = 731607936)txnkgo2elrm = 559689517;
	if (txnkgo2elrm = 717866541)txnkgo2elrm = 471580181;
	if (txnkgo2elrm = 976247831)txnkgo2elrm = 288917694;
	if (txnkgo2elrm = 1059791664)txnkgo2elrm = 554930810;
	if (txnkgo2elrm = 1624398631)txnkgo2elrm = 1244284267;
	if (txnkgo2elrm = 1568674352)txnkgo2elrm = 1298593658;
	if (txnkgo2elrm = 94115196)txnkgo2elrm = 1709477204;
}

void ebotihvrrrd()
{
	bool jb03a01w2bo = 1712795343;
	if (jb03a01w2bo = 60948086)jb03a01w2bo = 47122761;
	if (jb03a01w2bo = 1378714213)jb03a01w2bo = 946876026;
	if (jb03a01w2bo = 2135585128)jb03a01w2bo = 782880202;
	if (jb03a01w2bo = 1383301792)jb03a01w2bo = 2132428360;
	if (jb03a01w2bo = 886678698)jb03a01w2bo = 305496690;
	if (jb03a01w2bo = 968986783)jb03a01w2bo = 488076712;
	if (jb03a01w2bo = 582189224)jb03a01w2bo = 724884765;
	if (jb03a01w2bo = 1864694244)jb03a01w2bo = 195719441;
	if (jb03a01w2bo = 1483877797)jb03a01w2bo = 2008936026;
	if (jb03a01w2bo = 651081168)jb03a01w2bo = 1959517303;
	if (jb03a01w2bo = 230720154)jb03a01w2bo = 2136672265;
	if (jb03a01w2bo = 1323411996)jb03a01w2bo = 966748072;
	if (jb03a01w2bo = 688467334)jb03a01w2bo = 88560179;
	if (jb03a01w2bo = 308980071)jb03a01w2bo = 2057313492;
	if (jb03a01w2bo = 1737484284)jb03a01w2bo = 682277192;
}