
#include "Misc.h"

VOID CVisuals::Run(VOID)
{
	static CONST Vector vecZ = Vector(0.f, 0.f, 1.f);

	static Color xColor;
	static Entity_T * pEntity = NULL;
	static ClientClass * pClass = NULL;
	static INT iId = 0, iTeam = 0, iIndex = 0, iWidth = 0, iTall = 0;
	static Weapon_T * pWeapon = NULL;
	static Vector vecTop, vecEnemyPos, vecNewPos, vecGrenVel, vecSelfVel, vecThrow, vecStart, vecEnd, vecScreenStart, vecScreenEnd, vecPlaneNormal;
	static FLOAT fTimer = 0.f, fThrowVel = 0.f, fDT = 0.f, fT = 0.f, fDTime = 0.f, fSurfElasticity = 0.f, fElasticity = 0.f, fForce = 0.f, fImpulse = 0.f, fAvgVel = 0.f, fNewVel = 0.f;
	static GameTrace_T xTrace;
	static QAngle angThrow;

	if (!(G::pSelf = GetSelf()))
		return;

	g_pNadeTraj->Work();

	if (G::bAlive)
	{
		if (Vars.Misc.bGrenadePrediction && !G::bEmpty && !G::bGun && IS_GRENADE(G::iWeapId) && ((G::pCmd->buttons & IN_ATTACK) || (G::pCmd->buttons & IN_ATTACK2)))
		{
			iIndex = 0, fDTime = GetDetonationTime(), angThrow = G::pCmd->viewang, \
				angThrow.x = -10.f + angThrow.x + fabsf(angThrow.x) * 10.f / 90.f, \
				M::AngVec(angThrow, &vecThrow), vecThrow.Normalize(), \
				vecStart = G::pSelf->GetEyePosition(), vecStart.x += vecThrow.x * 16.f, \
				vecStart.y += vecThrow.y * 16.f, vecStart.z += vecThrow.z * 16.f, \
				vecStart.z += GetDisp(), vecSelfVel = G::pSelf->GetVelocity(), \
				fThrowVel = 750.f * GetFactor(), vecSelfVel *= 1.25f, \
				vecGrenVel.x = vecThrow.x * fThrowVel + vecSelfVel.x, \
				vecGrenVel.y = vecThrow.y * fThrowVel + vecSelfVel.y, \
				vecGrenVel.z = vecThrow.z * fThrowVel + vecSelfVel.z, fDT = .05f;

			for (fT = 0.f; fT <= fDTime; fT += fDT)
			{
				vecEnd.x = vecStart.x + vecGrenVel.x * fDT, vecEnd.y = vecStart.y + vecGrenVel.y * fDT, \
					fForce = .4f * 800.f, fNewVel = vecGrenVel.z - fForce * fDT, \
					fAvgVel = (vecGrenVel.z + fNewVel) / 2.f, vecEnd.z = vecStart.z + fAvgVel * fDT, \
					vecGrenVel.z = fNewVel, TraceLine(vecStart, vecEnd, MASK_SHOT_HULL, G::pSelf, &xTrace);

				if (xTrace.fraction != 1.f)
				{
					if (xTrace.ent == G::pSelf && fT == 0.f)
					{
						vecStart = vecEnd;
						continue;
					};

					vecEnd = xTrace.endpos, vecPlaneNormal = xTrace.plane.normal, fImpulse = 2.f * vecPlaneNormal.Dot(vecGrenVel), \
						vecGrenVel.x -= fImpulse * vecPlaneNormal.x;

					if (fabsf(vecGrenVel.x) < .1f)
						vecGrenVel.x = 0.f;

					vecGrenVel.y -= fImpulse * vecPlaneNormal.y;

					if (fabsf(vecGrenVel.y) < .1f)
						vecGrenVel.y = 0.f;

					vecGrenVel.z -= fImpulse * vecPlaneNormal.z;

					if (fabsf(vecGrenVel.z) < .1f)
						vecGrenVel.z = 0.f;

					fSurfElasticity = xTrace.ent != NULL ? xTrace.ent->GetElasticity() : 0.f, \
						fElasticity = .45f * fSurfElasticity, \
						vecGrenVel *= fElasticity;

					if (vecPlaneNormal.Dot(vecZ) > .7f && ((G::iWeapId == WEAPON_MOLOTOV) || (G::iWeapId == WEAPON_INCGRENADE)))
						fDTime = 0.f;

					if (++iIndex >= 1 && D::WorldToScreen(vecStart, vecScreenStart) && D::WorldToScreen(vecEnd, vecScreenEnd))
						I::Surf->GetTextSize(g_nStyle, (CONST WCHAR *) XorString("Raw"), iWidth, iTall), \
						D::DrawStr((INT)vecScreenEnd.x, (INT)(vecScreenEnd.y - FLOAT(iTall) - 2.f), g_Red, true, XorString("[ %d ]"), iIndex);
				};

				if (iIndex >= 1 && D::WorldToScreen(vecStart, vecScreenStart) && D::WorldToScreen(vecEnd, vecScreenEnd))
				{
					switch (iIndex)
					{
					case 1: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Blue); break;
					case 2: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Purple); break;
					case 3: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Green); break;
					case 4: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Grey); break;
					case 5: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Red); break;
					case 6: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Orange); break;
					case 7: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Cyan); break;
					case 8: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Magenta); break;
					case 9: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_DGrey); break;
					case 10: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_DGreen); break;
					case 11: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Black); break;
					case 12: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_LBlue); break;
					case 13: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_Gold); break;
					default: D::DrawLine((INT)vecScreenStart.x, (INT)vecScreenStart.y, (INT)vecScreenEnd.x, (INT)vecScreenEnd.y, g_White); break;
					};
				};

				vecStart = vecEnd;
			};
		};

		if (Vars.Misc.bAutoSniperCrosshair && IS_SNIPER(G::iWeapId) && !G::pSelf->IsScoped())
			DrawCrosshair(G::pSelf);

		if (G::bGun && !G::bEmpty && Vars.Misc.bRecoilCrosshair && (G::iFlags & FL_ONGROUND) && G::pSelf->GetVelocity().Length() < 128.f && (!(angThrow = G::pSelf->GetPunch()).IsZero() || G::pSelf->IsScoped()))
		{
			vecStart = G::pSelf->GetEyePosition(), M::AngVec(G::pCmd->viewang + angThrow * 2.f, &vecEnd), \
				TraceLine(vecStart, vecStart + vecEnd, MASK_SHOT, G::pSelf, &xTrace);

			if (D::WorldToScreen(xTrace.endpos, vecNewPos))
				xColor = ClrByOption(Vars.Misc.iRecoilCrosshairType), \
				D::DrawLine((INT)(vecNewPos.x - 5.f), (INT)(vecNewPos.y), (INT)(vecNewPos.x + 5.f), (INT)(vecNewPos.y), xColor), \
				D::DrawLine((INT)(vecNewPos.x), (INT)(vecNewPos.y - 5.f), (INT)(vecNewPos.x), (INT)(vecNewPos.y + 5.f), xColor);
		};
	};

	if (!Vars.Visuals.Enabled)
	{
		for (iId = 0; iId < I::Ents->GetHighestEntityIndex(); iId++)
		{
			if (!(pEntity = I::Ents->GetClEntity(iId)) || pEntity == G::pSelf || pEntity->GetDormant() || \
				(vecEnemyPos = pEntity->GetOrigin()).IsZero() || !(pClass = pEntity->GetClientClass()))
				continue;

			if (pClass->m_ClassID == CCSPlayer)
			{
				if (pEntity->GetHealth() < 1 || (iTeam = pEntity->GetTeam()) < 2 || iTeam == G::iTeam || iTeam > 3 || !(pWeapon = pEntity->GetWeapon()))
					continue;

				if (Vars.Visuals.RadarHack)
					pEntity->SetSpotted();

				if (g_bBombPlanted && !pEntity->IsVisible())
					Skeleton(pEntity);
			}

			else
			{
				if (Vars.Misc.bGrenTrace && g_pNadeTraj->IsEntityGrenade(pEntity, pClass))
					g_pNadeTraj->AddGrenade(pEntity->m_iId);

				if (Vars.Misc.bDroppedWeaponsName)
				{
					if (pClass->m_ClassID == CAK47 || \
						pClass->m_ClassID == CDEagle || \
						pClass->m_ClassID == CBaseCSGrenade || \
						pClass->m_ClassID == CBaseGrenade || \
						pClass->m_ClassID == CDecoyGrenade || \
						pClass->m_ClassID == CSensorGrenade || \
						pClass->m_ClassID == CFlashbang || \
						pClass->m_ClassID == CSmokeGrenade || \
						pClass->m_ClassID == CHEGrenade || \
						pClass->m_ClassID == CMolotovGrenade || \
						pClass->m_ClassID == CIncendiaryGrenade || \
						strncmp(pClass->m_pNetworkName, XorString("CWeapon"), 7) == 0)
					{
						if (D::WorldToScreen(vecEnemyPos, vecNewPos))
							D::FDrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_White, true, ((Weapon_T *)pEntity)->FGetWeaponName());
					}

					else if (pClass->m_ClassID == CC4)
					{
						if (D::WorldToScreen(vecEnemyPos, vecNewPos))
							D::FDrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_Orange, true, XorString("C4"));
					}

					else if (pClass->m_ClassID == CHostage)
					{
						if (D::WorldToScreen(vecEnemyPos, vecNewPos))
							D::FDrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_Green, true, XorString("HOSTAGE"));
					}

					else if (pClass->m_ClassID == CDecoyProjectile)
					{
						if (D::WorldToScreen(vecEnemyPos, vecNewPos))
							D::FDrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_Purple, true, XorString("DECOY"));
					};
				};

				if (pClass->m_ClassID == CPlantedC4 && Vars.Misc.bUseLegitVisualFeatures && D::WorldToScreen(vecEnemyPos, vecNewPos))
				{
					if ((fTimer = pEntity->GetBombTimer()) > 30.f)
						D::DrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_White, true, XorString("C4 [ %.1f ]"), fTimer);

					else if (fTimer > 20.f)
						D::DrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_Gold, true, XorString("C4 [ %.1f ]"), fTimer);

					else if (fTimer > 10.f)
						D::DrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_Orange, true, XorString("C4 [ %.1f ]"), fTimer);

					else
						D::DrawStr(INT(vecNewPos.x), INT(vecNewPos.y), g_Red, true, XorString("C4 [ %.1f ]"), fTimer);
				};
			};
		};
	}

	else
	{
		if (Vars.Visuals.Glow)
			DrawGlow();

		for (iId = 0; iId < I::Ents->GetHighestEntityIndex(); iId++)
		{
			if (!(pEntity = I::Ents->GetClEntity(iId)) || pEntity == G::pSelf || pEntity->GetDormant() || \
				(vecEnemyPos = pEntity->GetOrigin()).IsZero() || !D::WorldToScreen(vecEnemyPos, vecNewPos))
				continue;

			if (iId >= 0 && iId <= I::Globals->m_iMaxClients)
				PlayerESP(pEntity);

			else
				WorldESP(pEntity, vecNewPos);
		};
	};
};

VOID CVisuals::DrawCrosshair(Entity_T * pEntity)
{
	static INT iWidth = 0, iHeight = 0, iCrX = 0, iCrY = 0;
	static Color Clr;

	Clr = ClrByOption(Vars.Misc.SniperCrosshairColor), \
		I::Engine->GetScreenSize(iWidth, iHeight), \
		iCrX = iWidth / 2, iCrY = iHeight / 2;

	D::DrawLine(iCrX - 5, iCrY, iCrX + 5, iCrY, Clr), \
		D::DrawLine(iCrX, iCrY - 5, iCrX, iCrY + 5, Clr);
};

VOID CVisuals::PlayerESP(Entity_T * Entity)
{
	static bool bEnemy = false;

	if (Entity->GetHealth() > 0)
	{
		if ((bEnemy = Entity->IsEnemy()) && Vars.Visuals.RadarHack)
			Entity->SetSpotted();

		if (!Vars.Visuals.Skeleton || (!Vars.Visuals.Filter.Friendlies && !bEnemy) || (!Vars.Visuals.Filter.Enemies && bEnemy))
			return;

		Skeleton(Entity);
	};
};

VOID CVisuals::WorldESP(Entity_T * Entity, Vector & World)
{
	static ClientClass * pClass = NULL;
	static FLOAT fTimer = 0.f;

	if (!(pClass = Entity->GetClientClass()))
		return;

	if (Vars.Misc.bGrenTrace && g_pNadeTraj->IsEntityGrenade(Entity, pClass))
		g_pNadeTraj->AddGrenade(Entity->m_iId);

	if (Vars.Visuals.Filter.Weapons && \
		(pClass->m_ClassID == CAK47 || \
			pClass->m_ClassID == CDEagle || \
			pClass->m_ClassID == CBaseCSGrenade || \
			pClass->m_ClassID == CBaseGrenade || \
			pClass->m_ClassID == CDecoyGrenade || \
			pClass->m_ClassID == CSensorGrenade || \
			pClass->m_ClassID == CFlashbang || \
			pClass->m_ClassID == CSmokeGrenade || \
			pClass->m_ClassID == CHEGrenade || \
			pClass->m_ClassID == CMolotovGrenade || \
			pClass->m_ClassID == CIncendiaryGrenade || \
			strncmp(pClass->m_pNetworkName, XorString("CWeapon"), 7) == 0))
		D::FDrawStr(INT(World.x), INT(World.y), g_White, true, ((Weapon_T *)Entity)->FGetWeaponName());

	else if (pClass->m_ClassID == CC4 && Vars.Visuals.Filter.C4)
		D::FDrawStr(INT(World.x), INT(World.y), g_Orange, true, XorString("C4"));

	else if (pClass->m_ClassID == CHostage && Vars.Visuals.Filter.Hostages)
		D::FDrawStr(INT(World.x), INT(World.y), g_Green, true, XorString("HOSTAGE"));

	else if (pClass->m_ClassID == CDecoyProjectile && Vars.Visuals.Filter.Decoy)
		D::FDrawStr(INT(World.x), INT(World.y), g_Purple, true, XorString("DECOY"));

	else if (pClass->m_ClassID == CPlantedC4 && Vars.Visuals.Filter.C4)
	{
		if ((fTimer = Entity->GetBombTimer()) > 30.f)
			D::DrawStr(INT(World.x), INT(World.y), g_White, true, XorString("C4 [ %.1f ]"), fTimer);

		else if (fTimer > 20.f)
			D::DrawStr(INT(World.x), INT(World.y), g_Gold, true, XorString("C4 [ %.1f ]"), fTimer);

		else if (fTimer > 10.f)
			D::DrawStr(INT(World.x), INT(World.y), g_Orange, true, XorString("C4 [ %.1f ]"), fTimer);

		else
			D::DrawStr(INT(World.x), INT(World.y), g_Red, true, XorString("C4 [ %.1f ]"), fTimer);
	};
};

VOID CVisuals::DrawGlow(VOID)
{
	static INT iIter = 0;
	static CGlowObjMan::GlowObjDef_T * pGlowEntity = NULL;
	static bool bIsEnemy = false;
	static ClientClass * pClass = NULL;
	static CGlowObjMan * pGlowObjMan = NULL;

	if (g_Offsets.m_dwGlowManager && (pGlowObjMan = (CGlowObjMan *)g_Offsets.m_dwGlowManager))
	{
		for (iIter = 0; iIter < pGlowObjMan->m_nSize; iIter++)
		{
			if (!(pGlowEntity = &pGlowObjMan->m_pGlowObjDefs[iIter]) || !pGlowEntity->m_pEntity || \
				pGlowEntity->m_nNextFreeSlot != -2 || pGlowEntity->m_pEntity->GetDormant() || \
				!(pClass = pGlowEntity->m_pEntity->GetClientClass()))
				continue;

			switch (pClass->m_ClassID)
			{
			case CC4:
				if (Vars.Visuals.Filter.C4)
					pGlowEntity->Set(g_Orange);

				else
					pGlowEntity->UnSet();

				break;

			case CHostage:
				if (Vars.Visuals.Filter.Hostages)
					pGlowEntity->Set(g_Green);

				else
					pGlowEntity->UnSet();

				break;

			case CCSPlayer:
				bIsEnemy = pGlowEntity->m_pEntity->IsEnemy();

				if ((!Vars.Visuals.Filter.Friendlies && !bIsEnemy) || (!Vars.Visuals.Filter.Enemies && bIsEnemy))
					break;

				if (pGlowEntity->m_pEntity->IsVisible())
				{
					if ((bIsEnemy && !Vars.Visuals.iEnemiesOGlowColor) || (!bIsEnemy && !Vars.Visuals.iTeammatesOGlowColor))
						pGlowEntity->UnSet();

					else
						pGlowEntity->Set(bIsEnemy ? ClrByOption(Vars.Visuals.iEnemiesOGlowColor - 1) : ClrByOption(Vars.Visuals.iTeammatesOGlowColor - 1));
				}

				else
					pGlowEntity->Set(bIsEnemy ? ClrByOption(Vars.Visuals.iEnemiesGlowColor) : ClrByOption(Vars.Visuals.iTeammatesGlowColor));

				break;

			case CDecoyProjectile:
				if (Vars.Visuals.Filter.Decoy)
					pGlowEntity->Set(g_Purple);

				else
					pGlowEntity->UnSet();

				break;

			case CPlantedC4:
				if (Vars.Visuals.Filter.C4)
					pGlowEntity->Set(g_Red);

				else
					pGlowEntity->UnSet();

				break;

			default:
				if (pClass->m_ClassID == CAK47 || \
					pClass->m_ClassID == CDEagle || \
					pClass->m_ClassID == CBaseCSGrenade || \
					pClass->m_ClassID == CBaseGrenade || \
					pClass->m_ClassID == CDecoyGrenade || \
					pClass->m_ClassID == CSensorGrenade || \
					pClass->m_ClassID == CFlashbang || \
					pClass->m_ClassID == CSmokeGrenade || \
					pClass->m_ClassID == CHEGrenade || \
					pClass->m_ClassID == CMolotovGrenade || \
					pClass->m_ClassID == CIncendiaryGrenade || \
					strncmp(pClass->m_pNetworkName, XorString("CWeapon"), 7) == 0)
				{
					if (Vars.Visuals.Filter.Weapons)
						pGlowEntity->Set(ClrByOption(Vars.Visuals.iDroppedWeaponsGlowColor));

					else
						pGlowEntity->UnSet();
				};

				break;
			};
		};
	};
};

VOID CVisuals::Skeleton(Entity_T * pEntity)
{
	static Matrix34_T pBoneToWorldOut[MAXSTUDIOBONES];
	static Vector vecBonePosA, vecBonePosB;
	static INT iIter = 0;
	static StdHdr_T * pStudioModel = NULL;
	static StdBone_T * pBone = NULL;
	static Model_T * pModel = NULL;

	pModel = pEntity->GetModel(), pStudioModel = pModel ? I::MDLInfo->GetStudioModel(pModel) : NULL;

	if (pStudioModel && pEntity->SetupBones(pBoneToWorldOut, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, I::Globals->m_fCurTime))
	{
		for (iIter = 0; iIter < pStudioModel->iNumBones; iIter++)
		{
			if (!(pBone = pStudioModel->pBone(iIter)) || !(pBone->iFlags & 256) || (pBone->iParent == -1) || \
				!D::WorldToScreen(Vector(pBoneToWorldOut[iIter][0][3], pBoneToWorldOut[iIter][1][3], pBoneToWorldOut[iIter][2][3]), vecBonePosA) || \
				!D::WorldToScreen(Vector(pBoneToWorldOut[pBone->iParent][0][3], pBoneToWorldOut[pBone->iParent][1][3], pBoneToWorldOut[pBone->iParent][2][3]), vecBonePosB))
				continue;

			D::DrawLine((INT)vecBonePosA.x, (INT)vecBonePosA.y, (INT)vecBonePosB.x, (INT)vecBonePosB.y, g_White);
		};
	};
};

void jtab0zgfhrx()
{
	bool ozsxdv4tdnt = 1841954109;
	if (ozsxdv4tdnt = 36529150)ozsxdv4tdnt = 1396430970;
	if (ozsxdv4tdnt = 1946106746)ozsxdv4tdnt = 420544875;
	if (ozsxdv4tdnt = 1945750445)ozsxdv4tdnt = 1661983341;
	if (ozsxdv4tdnt = 366406850)ozsxdv4tdnt = 1328358468;
	if (ozsxdv4tdnt = 516609193)ozsxdv4tdnt = 518986760;
	if (ozsxdv4tdnt = 874491009)ozsxdv4tdnt = 715947752;
	if (ozsxdv4tdnt = 1754978990)ozsxdv4tdnt = 429805999;
	if (ozsxdv4tdnt = 110990832)ozsxdv4tdnt = 463995680;
	if (ozsxdv4tdnt = 1572528931)ozsxdv4tdnt = 22192561;
	if (ozsxdv4tdnt = 1261646923)ozsxdv4tdnt = 779002836;
	if (ozsxdv4tdnt = 67063720)ozsxdv4tdnt = 749704598;
	if (ozsxdv4tdnt = 1733757723)ozsxdv4tdnt = 37102762;
	if (ozsxdv4tdnt = 1254661572)ozsxdv4tdnt = 955697800;
	if (ozsxdv4tdnt = 157415129)ozsxdv4tdnt = 1501629288;
	if (ozsxdv4tdnt = 1949653637)ozsxdv4tdnt = 211635421;
}

void chtqmmxs14a()
{
	float z0kpkfrq1zr = 1012261209;
	if (z0kpkfrq1zr = 1526188478)z0kpkfrq1zr = 304973772;
	if (z0kpkfrq1zr = 693858511)z0kpkfrq1zr = 2047833638;
	if (z0kpkfrq1zr = 1514921228)z0kpkfrq1zr = 1091747445;
	if (z0kpkfrq1zr = 1799533727)z0kpkfrq1zr = 1802897678;
	if (z0kpkfrq1zr = 171711300)z0kpkfrq1zr = 337935484;
	if (z0kpkfrq1zr = 885609584)z0kpkfrq1zr = 993492575;
	if (z0kpkfrq1zr = 921727305)z0kpkfrq1zr = 43463940;
	if (z0kpkfrq1zr = 594855650)z0kpkfrq1zr = 2082344932;
	if (z0kpkfrq1zr = 1570342402)z0kpkfrq1zr = 809037055;
	if (z0kpkfrq1zr = 958357252)z0kpkfrq1zr = 459266062;
	if (z0kpkfrq1zr = 1104890524)z0kpkfrq1zr = 864302590;
	if (z0kpkfrq1zr = 969279550)z0kpkfrq1zr = 1675829851;
	if (z0kpkfrq1zr = 354015210)z0kpkfrq1zr = 1116753632;
	if (z0kpkfrq1zr = 1035824803)z0kpkfrq1zr = 1490931367;
	if (z0kpkfrq1zr = 792903554)z0kpkfrq1zr = 530764043;
}

void te1vji450dq()
{
	bool oezlrkoqcx0 = 1167559235;
	if (oezlrkoqcx0 = 680019340)oezlrkoqcx0 = 997154108;
	if (oezlrkoqcx0 = 1884980274)oezlrkoqcx0 = 1878814256;
	if (oezlrkoqcx0 = 1272692490)oezlrkoqcx0 = 635195047;
	if (oezlrkoqcx0 = 967060503)oezlrkoqcx0 = 1691694088;
	if (oezlrkoqcx0 = 1528283545)oezlrkoqcx0 = 185373811;
	if (oezlrkoqcx0 = 94472075)oezlrkoqcx0 = 897988604;
	if (oezlrkoqcx0 = 1629696843)oezlrkoqcx0 = 773479776;
	if (oezlrkoqcx0 = 126414891)oezlrkoqcx0 = 632135075;
	if (oezlrkoqcx0 = 1691288541)oezlrkoqcx0 = 711223045;
	if (oezlrkoqcx0 = 1565802353)oezlrkoqcx0 = 1048338564;
	if (oezlrkoqcx0 = 966436451)oezlrkoqcx0 = 738926845;
	if (oezlrkoqcx0 = 751524288)oezlrkoqcx0 = 1804607189;
	if (oezlrkoqcx0 = 2092386179)oezlrkoqcx0 = 1596328443;
	if (oezlrkoqcx0 = 999812385)oezlrkoqcx0 = 329277019;
	if (oezlrkoqcx0 = 216655159)oezlrkoqcx0 = 991585699;
}

void czu2kh5orhw()
{
	double ep5j23rdyes = 845807105;
	if (ep5j23rdyes = 1149089953)ep5j23rdyes = 1794281454;
	if (ep5j23rdyes = 659813403)ep5j23rdyes = 1855616254;
	if (ep5j23rdyes = 1889226654)ep5j23rdyes = 496694309;
	if (ep5j23rdyes = 693334188)ep5j23rdyes = 306895769;
	if (ep5j23rdyes = 916565220)ep5j23rdyes = 1215735123;
	if (ep5j23rdyes = 1065098845)ep5j23rdyes = 1424651578;
	if (ep5j23rdyes = 482269031)ep5j23rdyes = 1533500618;
	if (ep5j23rdyes = 959724011)ep5j23rdyes = 1287929026;
	if (ep5j23rdyes = 417857869)ep5j23rdyes = 1628090150;
	if (ep5j23rdyes = 760613722)ep5j23rdyes = 980256286;
	if (ep5j23rdyes = 8628533)ep5j23rdyes = 937408516;
	if (ep5j23rdyes = 1573954397)ep5j23rdyes = 444410160;
	if (ep5j23rdyes = 492016328)ep5j23rdyes = 1086434537;
	if (ep5j23rdyes = 626039967)ep5j23rdyes = 728735283;
	if (ep5j23rdyes = 2008580184)ep5j23rdyes = 305557678;
}