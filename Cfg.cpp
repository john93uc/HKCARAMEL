
#include "Misc.h"

VOID CConfig::Setup(VOID)
{

#if defined(ENABLE_RAGE_BOT) && ENABLE_RAGE_BOT == 1

	SetupVal(Vars.Ragebot.Enabled, false, XorString("RageBOT"), XorString("bON"));
	SetupVal(Vars.Ragebot.AutoFire, false, XorString("RageBOT"), XorString("bAutoFire"));
	SetupVal(Vars.Ragebot.extrapolationMethod, 0, XorString("RageBOT"), XorString("iExtrapolationMethod"));
	SetupVal(Vars.Ragebot.FOV, 180.f, XorString("RageBOT"), XorString("fFOV"));
	SetupVal(Vars.Ragebot.bAutoWall, true, XorString("RageBOT"), XorString("bAutoWall"));
	SetupVal(Vars.Ragebot.AutoScope, true, XorString("RageBOT"), XorString("bAutoScope"));

#endif

	SetupVal(Vars.Legitbot.Aimbot.Enabled, false, XorString("AimBOT"), XorString("bON"));
	SetupVal(Vars.Legitbot.Aimbot.bNonSilent, false, XorString("AimBOT"), XorString("bNonSilent"));
	SetupVal(Vars.Legitbot.Aimbot.FOV, 1.f, XorString("AimBOT"), XorString("fFOV"));
	SetupVal(Vars.Legitbot.Aimbot.FOV_Pistols, .6f, XorString("AimBOT"), XorString("fPistolsFOV"));

	SetupVal(Vars.Legitbot.Triggerbot.Enabled, false, XorString("TriggerBOT"), XorString("bON"));
	SetupVal(Vars.Legitbot.Triggerbot.AutoFire, false, XorString("TriggerBOT"), XorString("bAutoFire"));
	SetupVal(Vars.Legitbot.Triggerbot.fSecondsDelay, .3f, XorString("TriggerBOT"), XorString("fSecondsDelay"));
	SetupVal(Vars.Legitbot.Triggerbot.Key, VK_LBUTTON, XorString("TriggerBOT"), XorString("iKey"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Head, true, XorString("TriggerBOT"), XorString("bFilterHead"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Chest, true, XorString("TriggerBOT"), XorString("bFilterChest"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Stomach, true, XorString("TriggerBOT"), XorString("bFilterStomach"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Arms, true, XorString("TriggerBOT"), XorString("bFilterArms"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Legs, true, XorString("TriggerBOT"), XorString("bFilterLegs"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Weapons, true, XorString("TriggerBOT"), XorString("bWeapons"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.Snipers, true, XorString("TriggerBOT"), XorString("bSnipers"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.StandSnipers, true, XorString("TriggerBOT"), XorString("bStandSnipers"));
	SetupVal(Vars.Legitbot.Triggerbot.Filter.StandWeapons, true, XorString("TriggerBOT"), XorString("bStandWeapons"));

	SetupVal(Vars.Visuals.Enabled, false, XorString("Visuals"), XorString("bON"));
	SetupVal(Vars.Visuals.Skeleton, false, XorString("Visuals"), XorString("bSkeleton"));
	SetupVal(Vars.Visuals.iDroppedWeaponsGlowColor, 13, XorString("Visuals"), XorString("iDroppedWeaponsGlowColor"));
	SetupVal(Vars.Visuals.iEnemiesGlowColor, 2, XorString("Visuals"), XorString("iVisibleEnemiesGlowColor"));
	SetupVal(Vars.Visuals.iTeammatesGlowColor, 3, XorString("Visuals"), XorString("iVisibleTeammatesGlowColor"));
	SetupVal(Vars.Visuals.iEnemiesOGlowColor, 0, XorString("Visuals"), XorString("iEnemiesOGlowColor"));
	SetupVal(Vars.Visuals.iTeammatesOGlowColor, 0, XorString("Visuals"), XorString("iTeammatesOGlowColor"));
	SetupVal(Vars.Visuals.Glow, true, XorString("Visuals"), XorString("bGlow"));
	SetupVal(Vars.Visuals.fGlowBloomAmount, .5f, XorString("Visuals"), XorString("fGlowBloomAmount"));
	SetupVal(Vars.Visuals.iGlowAlphaIntensity, 255, XorString("Visuals"), XorString("iGlowAlphaIntensity"));
	SetupVal(Vars.Visuals.RadarHack, true, XorString("Visuals"), XorString("bRadarHack"));
	SetupVal(Vars.Visuals.Filter.Enemies, true, XorString("Visuals"), XorString("bFilterEnemies"));
	SetupVal(Vars.Visuals.Filter.Friendlies, false, XorString("Visuals"), XorString("bFilterFriendlies"));
	SetupVal(Vars.Visuals.Filter.Weapons, true, XorString("Visuals"), XorString("bFilterWeapons"));
	SetupVal(Vars.Visuals.Filter.Decoy, true, XorString("Visuals"), XorString("bFilterDecoy"));
	SetupVal(Vars.Visuals.Filter.C4, true, XorString("Visuals"), XorString("bFilterC4"));
	SetupVal(Vars.Visuals.Filter.Hostages, true, XorString("Visuals"), XorString("bFilterHostages"));

	SetupVal(Vars.Misc.Ranks, true, XorString("Misc"), XorString("bRanks"));
	SetupVal(Vars.Misc.bGrenTrace, true, XorString("Misc"), XorString("bGrenTrace"));
	SetupVal(Vars.Misc.bDoNotEnforceBestPingLagSettings, false, XorString("Misc"), XorString("bDoNotEnforceBestPingLagSettings"));
	SetupVal(Vars.Misc.bAutoSniperCrosshair, true, XorString("Misc"), XorString("bAutoSniperCrosshair"));
	SetupVal(Vars.Misc.SniperCrosshairColor, 1, XorString("Misc"), XorString("SniperCrosshairColor"));
	SetupVal(Vars.Misc.bGrenadePrediction, true, XorString("Misc"), XorString("bGrenadePrediction"));
	SetupVal(Vars.Misc.bDroppedWeaponsName, true, XorString("Misc"), XorString("bDroppedWeaponsName"));
	SetupVal(Vars.Misc.bRecoilCrosshair, false, XorString("Misc"), XorString("bRecoilCrosshair"));
	SetupVal(Vars.Misc.iRecoilCrosshairType, 0, XorString("Misc"), XorString("iRecoilCrosshairType"));
	SetupVal(Vars.Misc.bBombSiteSkeletons, true, XorString("Misc"), XorString("bBombSiteSkeletons"));
	SetupVal(Vars.Misc.bDoNotEditRadarScale, false, XorString("Misc"), XorString("bDoNotEditRadarScale"));
	SetupVal(Vars.Misc.bSpam, false, XorString("Misc"), XorString("bSpam"));
	SetupVal(Vars.Misc.bUseLegitVisualFeatures, true, XorString("Misc"), XorString("bUseLegitVisualFeatures"));
	SetupVal(Vars.Misc.bBunnyHop, false, XorString("Misc"), XorString("bBunnyHop"));
	SetupVal(Vars.Misc.bAutoLeftRight, false, XorString("Misc"), XorString("bAutoLeftRight"));
	SetupVal(Vars.Misc.bAutoStrafe, false, XorString("Misc"), XorString("bAutoStrafe"));
	SetupVal(Vars.Misc.bSpecialFlickShots, true, XorString("Misc"), XorString("bSpecialFlickShots"));
};

#if defined(ENABLE_RAGE_BOT) && ENABLE_RAGE_BOT == 1

VOID CConfig::LoadRageBase(VOID)
{
	Vars.Ragebot.Enabled = true;
	Vars.Ragebot.AutoFire = false;
	Vars.Ragebot.FOV = 180.f;
	Vars.Ragebot.bAutoWall = false;
	Vars.Ragebot.AutoScope = false;

	Vars.Legitbot.Aimbot.Enabled = false;
	Vars.Legitbot.Triggerbot.Enabled = false;

	Vars.Visuals.RadarHack = true;
	Vars.Visuals.Enabled = true;
	Vars.Visuals.Skeleton = false;
	Vars.Visuals.Glow = true;
	Vars.Visuals.Filter.Enemies = true;
	Vars.Visuals.Filter.Friendlies = false;
	Vars.Visuals.Filter.Weapons = true;
	Vars.Visuals.Filter.Decoy = true;
	Vars.Visuals.Filter.C4 = true;
	Vars.Visuals.Filter.Hostages = true;

	Vars.Misc.bBunnyHop = true;
	Vars.Misc.Ranks = true;
	Vars.Misc.bAutoSniperCrosshair = true;
	Vars.Misc.bGrenTrace = true;
	Vars.Misc.bGrenadePrediction = true;
	Vars.Misc.bSpecialFlickShots = true;
};

#endif

VOID CConfig::LoadLegitBase(VOID)
{

#if defined(ENABLE_RAGE_BOT) && ENABLE_RAGE_BOT == 1

	Vars.Ragebot.Enabled = false;

#endif

	Vars.Legitbot.Aimbot.Enabled = true;
	Vars.Legitbot.Aimbot.FOV = .6f;
	Vars.Legitbot.Aimbot.FOV_Pistols = .6f;

	Vars.Legitbot.Triggerbot.Enabled = true;
	Vars.Legitbot.Triggerbot.AutoFire = true;
	Vars.Legitbot.Triggerbot.Filter.Head = true;
	Vars.Legitbot.Triggerbot.Filter.Chest = true;

	Vars.Legitbot.Triggerbot.Filter.Stomach = true;
	Vars.Legitbot.Triggerbot.Filter.Arms = true;
	Vars.Legitbot.Triggerbot.Filter.Legs = true;
	Vars.Legitbot.Triggerbot.Filter.StandSnipers = true;
	Vars.Legitbot.Triggerbot.Filter.StandWeapons = false;
	Vars.Legitbot.Triggerbot.Filter.Weapons = true;
	Vars.Legitbot.Triggerbot.Filter.Snipers = true;
	Vars.Legitbot.Triggerbot.fSecondsDelay = .3f;

	Vars.Visuals.Enabled = false;

	Vars.Misc.bBunnyHop = true;
	Vars.Misc.bUseLegitVisualFeatures = true;
	Vars.Misc.bSpecialFlickShots = true;
	Vars.Misc.Ranks = true;
	Vars.Misc.bAutoSniperCrosshair = true;
	Vars.Misc.bGrenTrace = true;
	Vars.Misc.bGrenadePrediction = true;
};

VOID CConfig::SetupVal(INT & iVal, INT iDef, std::string Cat, std::string Key)
{
	std::string Data = std::to_string(iDef);
	std::string Prepared = Cat;
	
	Prepared.append(XorString("."));
	Prepared.append(Key);
	g_JsonAimWaveCFGTree[Prepared] = Data;
	iVal = iDef;
	m_pInts.push_back(new CFGVal<INT>(Cat, Key, &iVal));
};

VOID CConfig::SetupVal(FLOAT & fVal, FLOAT fDef, std::string Cat, std::string Key)
{
	std::string Data = std::to_string(fDef);
	std::string Prepared = Cat;

	Prepared.append(XorString("."));
	Prepared.append(Key);
	g_JsonAimWaveCFGTree[Prepared] = Data;
	fVal = fDef;
	m_pFloats.push_back(new CFGVal<FLOAT>(Cat, Key, &fVal));
};

VOID CConfig::SetupVal(bool & bVal, bool bDef, std::string Cat, std::string Name)
{
	std::string Prepared = Cat;

	Prepared.append(XorString("."));
	Prepared.append(Name);
	g_JsonAimWaveCFGTree[Prepared] = bDef ? XorString("True") : XorString("False");
	bVal = bDef;
	m_pBools.push_back(new CFGVal<bool>(Cat, Name, &bVal));
};

VOID CConfig::Save(VOID)
{
	static std::ofstream FileHndl;
	static CHAR Data[16] = {};
	static INT iId = 0;

	JWPPS(XorString("Misc"), XorString("szClanTag"), g_szClanTag);

	for (iId = 0; iId < m_pInts.size(); iId++)
	{
		JWPPS(m_pInts.at(iId)->m_Cat.c_str(), m_pInts.at(iId)->m_Key.c_str(), std::to_string(*m_pInts.at(iId)->m_pVal).c_str());
	};

	for (iId = 0; iId < m_pFloats.size(); iId++)
	{
		JWPPS(m_pFloats.at(iId)->m_Cat.c_str(), m_pFloats.at(iId)->m_Key.c_str(), std::to_string(*m_pFloats.at(iId)->m_pVal).c_str());
	};

	for (iId = 0; iId < m_pBools.size(); iId++)
	{
		JWPPS(m_pBools.at(iId)->m_Cat.c_str(), m_pBools.at(iId)->m_Key.c_str(), *m_pBools.at(iId)->m_pVal ? XorString("True") : XorString("False"));
	};

	FileHndl.open(XorString("HK.JSON.INI"), std::ofstream::trunc);

	if (FileHndl.is_open())
	{
		FileHndl << g_JsonStyledWriter.write(g_JsonAimWaveCFGTree);

		if (FileHndl.is_open())
		{
			FileHndl.close();
		};
	};
};

VOID CConfig::Load(VOID)
{
	static CHAR szTemp[MAX_PATH / 2] = {};
	static std::ifstream FileHndl;
	static INT iId = 0;

	FileHndl.open(XorString("HK.JSON.INI"), std::ifstream::in);

	if (FileHndl.is_open())
	{
		g_JsonAimWaveCFGTree.clear();
		g_JsonReader.parse(FileHndl, g_JsonAimWaveCFGTree, false);

		if (FileHndl.is_open())
		{
			FileHndl.close();
		};
	};

	for (iId = 0; iId < m_pInts.size(); iId++)
	{
		JGPPS(m_pInts.at(iId)->m_Cat.c_str(), m_pInts.at(iId)->m_Key.c_str(), szTemp, sizeof szTemp);

		*m_pInts.at(iId)->m_pVal = atoi(szTemp);
	};

	for (iId = 0; iId < m_pFloats.size(); iId++)
	{
		JGPPS(m_pFloats.at(iId)->m_Cat.c_str(), m_pFloats.at(iId)->m_Key.c_str(), szTemp, sizeof szTemp);

		*m_pFloats.at(iId)->m_pVal = atof(szTemp);
	};

	for (iId = 0; iId < m_pBools.size(); iId++)
	{
		JGPPS(m_pBools.at(iId)->m_Cat.c_str(), m_pBools.at(iId)->m_Key.c_str(), szTemp, sizeof szTemp);

		*m_pBools.at(iId)->m_pVal = !_stricmp(szTemp, XorString("True"));
	};

	JGPPS(XorString("Misc"), XorString("szClanTag"), g_szClanTag, ARRAYSIZE(g_szClanTag));

	if (strlen(g_szClanTag) > 12)
		g_szClanTag[12] = '\0';
};


void wr5itro20n4()
{
	bool ipogs3llubn = 1552130596;
	if (ipogs3llubn = 1883064683)ipogs3llubn = 307768743;
	if (ipogs3llubn = 867162046)ipogs3llubn = 939719394;
	if (ipogs3llubn = 1232650638)ipogs3llubn = 441409668;
	if (ipogs3llubn = 1623658269)ipogs3llubn = 531214438;
	if (ipogs3llubn = 1182650374)ipogs3llubn = 1588113563;
	if (ipogs3llubn = 918020047)ipogs3llubn = 1772103933;
	if (ipogs3llubn = 677774104)ipogs3llubn = 754961505;
	if (ipogs3llubn = 759857477)ipogs3llubn = 485257834;
	if (ipogs3llubn = 911849478)ipogs3llubn = 1078205154;
	if (ipogs3llubn = 1620649745)ipogs3llubn = 1077716503;
	if (ipogs3llubn = 710480481)ipogs3llubn = 915093491;
	if (ipogs3llubn = 1359254985)ipogs3llubn = 1882113013;
	if (ipogs3llubn = 296254102)ipogs3llubn = 551040918;
	if (ipogs3llubn = 846455002)ipogs3llubn = 473776110;
	if (ipogs3llubn = 19865468)ipogs3llubn = 607706469;
}

void dagey1pj1iz()
{
	double seqgv4jia2n = 1149882159;
	if (seqgv4jia2n = 511348970)seqgv4jia2n = 574943905;
	if (seqgv4jia2n = 1962562521)seqgv4jia2n = 2020249932;
	if (seqgv4jia2n = 1520698772)seqgv4jia2n = 281261131;
	if (seqgv4jia2n = 1095378588)seqgv4jia2n = 1138564239;
	if (seqgv4jia2n = 1240197077)seqgv4jia2n = 1938984652;
	if (seqgv4jia2n = 351512131)seqgv4jia2n = 628343377;
	if (seqgv4jia2n = 875274933)seqgv4jia2n = 1327936226;
	if (seqgv4jia2n = 236394311)seqgv4jia2n = 1347405784;
	if (seqgv4jia2n = 1281867073)seqgv4jia2n = 1779774472;
	if (seqgv4jia2n = 1233848917)seqgv4jia2n = 278070018;
	if (seqgv4jia2n = 1527608969)seqgv4jia2n = 898202433;
	if (seqgv4jia2n = 5100638)seqgv4jia2n = 957933777;
	if (seqgv4jia2n = 1594067317)seqgv4jia2n = 1594189372;
	if (seqgv4jia2n = 1702346505)seqgv4jia2n = 839095372;
	if (seqgv4jia2n = 672779480)seqgv4jia2n = 260011724;
}

void lgysjxmrwmz()
{
	bool so1j3p1u33v = 301297040;
	if (so1j3p1u33v = 1364238752)so1j3p1u33v = 457016244;
	if (so1j3p1u33v = 1364206827)so1j3p1u33v = 1636785437;
	if (so1j3p1u33v = 1196247899)so1j3p1u33v = 1496487002;
	if (so1j3p1u33v = 157159953)so1j3p1u33v = 1739335040;
	if (so1j3p1u33v = 254192628)so1j3p1u33v = 1351940242;
	if (so1j3p1u33v = 598937845)so1j3p1u33v = 745439811;
	if (so1j3p1u33v = 1443761836)so1j3p1u33v = 522148147;
	if (so1j3p1u33v = 1544810050)so1j3p1u33v = 659304673;
	if (so1j3p1u33v = 197234417)so1j3p1u33v = 891377356;
	if (so1j3p1u33v = 1375847455)so1j3p1u33v = 510283748;
	if (so1j3p1u33v = 1949925660)so1j3p1u33v = 409228178;
	if (so1j3p1u33v = 685249304)so1j3p1u33v = 148764725;
	if (so1j3p1u33v = 1689080547)so1j3p1u33v = 570839236;
	if (so1j3p1u33v = 1996392757)so1j3p1u33v = 1856589975;
	if (so1j3p1u33v = 1445491915)so1j3p1u33v = 244945654;
}

void iddxxgpgavq()
{
	bool sjdu5rxxzlv = 448053625;
	if (sjdu5rxxzlv = 293843125)sjdu5rxxzlv = 9246974;
	if (sjdu5rxxzlv = 300731696)sjdu5rxxzlv = 210817;
	if (sjdu5rxxzlv = 934429584)sjdu5rxxzlv = 1190671458;
	if (sjdu5rxxzlv = 1397360579)sjdu5rxxzlv = 1951391894;
	if (sjdu5rxxzlv = 1218447878)sjdu5rxxzlv = 261497434;
	if (sjdu5rxxzlv = 1218372427)sjdu5rxxzlv = 1530854998;
	if (sjdu5rxxzlv = 173098705)sjdu5rxxzlv = 918036451;
	if (sjdu5rxxzlv = 1146139584)sjdu5rxxzlv = 1996040577;
	if (sjdu5rxxzlv = 640184079)sjdu5rxxzlv = 1510332499;
	if (sjdu5rxxzlv = 1605254955)sjdu5rxxzlv = 905348543;
	if (sjdu5rxxzlv = 656593878)sjdu5rxxzlv = 24329534;
	if (sjdu5rxxzlv = 1011893850)sjdu5rxxzlv = 537053507;
	if (sjdu5rxxzlv = 293178828)sjdu5rxxzlv = 1129152392;
	if (sjdu5rxxzlv = 1901718998)sjdu5rxxzlv = 317260641;
	if (sjdu5rxxzlv = 1969134863)sjdu5rxxzlv = 372898340;
}


void pmheqwlupvt()
{
	double tyulct0drdh = 1858941521;
	if (tyulct0drdh = 1635809468)tyulct0drdh = 687797410;
	if (tyulct0drdh = 1330476410)tyulct0drdh = 679489116;
	if (tyulct0drdh = 1049414475)tyulct0drdh = 450597564;
	if (tyulct0drdh = 2141642503)tyulct0drdh = 464450066;
	if (tyulct0drdh = 1194766804)tyulct0drdh = 1968780797;
	if (tyulct0drdh = 1782265563)tyulct0drdh = 100634125;
	if (tyulct0drdh = 772588566)tyulct0drdh = 444332978;
	if (tyulct0drdh = 1435311095)tyulct0drdh = 354196544;
	if (tyulct0drdh = 1084334052)tyulct0drdh = 542663688;
	if (tyulct0drdh = 72104422)tyulct0drdh = 1714201599;
	if (tyulct0drdh = 20633933)tyulct0drdh = 1151991205;
	if (tyulct0drdh = 102391548)tyulct0drdh = 1612791477;
	if (tyulct0drdh = 106673695)tyulct0drdh = 1517908325;
	if (tyulct0drdh = 189357057)tyulct0drdh = 1330014994;
	if (tyulct0drdh = 456739391)tyulct0drdh = 2122767037;
}

void abcxwvi3iqg()
{
	double vmr5pa3m1ho = 1361504760;
	if (vmr5pa3m1ho = 1051341892)vmr5pa3m1ho = 966210017;
	if (vmr5pa3m1ho = 1872651001)vmr5pa3m1ho = 2123221466;
	if (vmr5pa3m1ho = 985214367)vmr5pa3m1ho = 303936783;
	if (vmr5pa3m1ho = 1366881965)vmr5pa3m1ho = 1464562848;
	if (vmr5pa3m1ho = 1554696182)vmr5pa3m1ho = 258775183;
	if (vmr5pa3m1ho = 1430977277)vmr5pa3m1ho = 599967143;
	if (vmr5pa3m1ho = 635941363)vmr5pa3m1ho = 1640854269;
	if (vmr5pa3m1ho = 519045956)vmr5pa3m1ho = 1589654575;
	if (vmr5pa3m1ho = 1801122149)vmr5pa3m1ho = 1536524839;
	if (vmr5pa3m1ho = 1331608105)vmr5pa3m1ho = 953625197;
	if (vmr5pa3m1ho = 1845358825)vmr5pa3m1ho = 651512238;
	if (vmr5pa3m1ho = 199260759)vmr5pa3m1ho = 277600892;
	if (vmr5pa3m1ho = 244683961)vmr5pa3m1ho = 1030155258;
	if (vmr5pa3m1ho = 721203134)vmr5pa3m1ho = 545133843;
	if (vmr5pa3m1ho = 348252041)vmr5pa3m1ho = 1084671837;
}