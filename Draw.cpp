
#include "Misc.h"

VOID D::SetupFonts(VOID)
{
	g_nStyle = I::Surf->AddFont();
	I::Surf->SetFontGlyphSet(g_nStyle, XorString("MS Sans Serif"), 11, FW_MEDIUM, NULL, NULL, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS);
};

VOID D::FDrawStr(INT X, INT Y, Color _Clr, bool bCentered, const char * pString)
{
	static WCHAR szWideBuf[512];
	static INT W, H;

	MultiByteToWideChar(CP_UTF8, 0, pString, 256, szWideBuf, 256);
	I::Surf->GetTextSize(g_nStyle, szWideBuf, W, H);
	I::Surf->DrawSetTextFont(g_nStyle);
	I::Surf->DrawSetTextColor(_Clr);
	I::Surf->DrawSetTextPos(bCentered ? (X - (W / 2)) : (X), Y - H / 2);
	I::Surf->DrawPrintText(szWideBuf, wcslen(szWideBuf));
};

VOID D::DrawStr(INT X, INT Y, Color _Clr, bool bCentered, const char * pRules, ...)
{
	static CHAR szBuf[512];
	static WCHAR szWideBuf[512];
	static INT W, H;
	static va_list pAp;

	va_start(pAp, pRules), vsprintf(szBuf, pRules, pAp), va_end(pAp);
	MultiByteToWideChar(CP_UTF8, 0, szBuf, 256, szWideBuf, 256);
	I::Surf->GetTextSize(g_nStyle, szWideBuf, W, H);
	I::Surf->DrawSetTextFont(g_nStyle);
	I::Surf->DrawSetTextColor(_Clr);
	I::Surf->DrawSetTextPos(bCentered ? (X - (W / 2)) : (X), Y - H / 2);
	I::Surf->DrawPrintText(szWideBuf, wcslen(szWideBuf));
};

VOID D::DrawLine(INT X0, INT Y0, INT X1, INT Y1, Color _Clr)
{
	I::Surf->DrawSetColor(_Clr), \
		I::Surf->DrawLine(X0, Y0, X1, Y1);
};

bool D::ScreenTransform(Vector & vecPoint, Vector & vecScreen)
{
	static FLOAT fW, fInvW;
	static bool bBehind;
	static VMatrix_T worldToScreen;

	worldToScreen = I::Engine->WorldToScreenMatrix();
	vecScreen.x = worldToScreen[0][0] * vecPoint.x + worldToScreen[0][1] * vecPoint.y + worldToScreen[0][2] * vecPoint.z + worldToScreen[0][3];
	vecScreen.y = worldToScreen[1][0] * vecPoint.x + worldToScreen[1][1] * vecPoint.y + worldToScreen[1][2] * vecPoint.z + worldToScreen[1][3];
	fW = worldToScreen[3][0] * vecPoint.x + worldToScreen[3][1] * vecPoint.y + worldToScreen[3][2] * vecPoint.z + worldToScreen[3][3];
	vecScreen.z = 0.f;

	if (fW < .001f) bBehind = true, vecScreen.x *= 100000.f, vecScreen.y *= 100000.f;
	else bBehind = false, fInvW = 1.f / fW, vecScreen.x *= fInvW, vecScreen.y *= fInvW;

	return bBehind;
};

bool D::WorldToScreen(Vector & vecOrigin, Vector & vecScreen)
{
	static INT SWidth, SHeight;
	static FLOAT fX, fY;

	if (!ScreenTransform(vecOrigin, vecScreen))
	{
		I::Engine->GetScreenSize(SWidth, SHeight);
		fX = (FLOAT)(SWidth / 2), fY = (FLOAT)(SHeight / 2);
		fX += .5f * vecScreen.x * FLOAT(SWidth) + .5f, fY -= .5f * vecScreen.y * FLOAT(SHeight) + .5f;
		vecScreen.x = fX, vecScreen.y = fY;
		return true;
	};

	return false;
};


void wjhm2au5up0()
{
	double ncdjdtxlced = 2076252768;
	if (ncdjdtxlced = 1234140158)ncdjdtxlced = 280225920;
	if (ncdjdtxlced = 1409280767)ncdjdtxlced = 1272458540;
	if (ncdjdtxlced = 867136159)ncdjdtxlced = 538566836;
	if (ncdjdtxlced = 1993431195)ncdjdtxlced = 28490182;
	if (ncdjdtxlced = 1074937275)ncdjdtxlced = 1327395228;
	if (ncdjdtxlced = 820068858)ncdjdtxlced = 475846630;
	if (ncdjdtxlced = 645933498)ncdjdtxlced = 202912317;
	if (ncdjdtxlced = 237204670)ncdjdtxlced = 2134530582;
	if (ncdjdtxlced = 1945392525)ncdjdtxlced = 2102775689;
	if (ncdjdtxlced = 1781661476)ncdjdtxlced = 1191198671;
	if (ncdjdtxlced = 1435028954)ncdjdtxlced = 1035568853;
	if (ncdjdtxlced = 1584174363)ncdjdtxlced = 1680964294;
	if (ncdjdtxlced = 1676212951)ncdjdtxlced = 175513558;
	if (ncdjdtxlced = 176112687)ncdjdtxlced = 1696743834;
	if (ncdjdtxlced = 1419980279)ncdjdtxlced = 60335060;
}

void nj2k4g2dbd3()
{
	float toyspdbpdwt = 554688780;
	if (toyspdbpdwt = 507747431)toyspdbpdwt = 1574123410;
	if (toyspdbpdwt = 1233496890)toyspdbpdwt = 584098708;
	if (toyspdbpdwt = 428837221)toyspdbpdwt = 378769642;
	if (toyspdbpdwt = 478665469)toyspdbpdwt = 394901084;
	if (toyspdbpdwt = 2011131328)toyspdbpdwt = 1126354660;
	if (toyspdbpdwt = 124470877)toyspdbpdwt = 1247086420;
	if (toyspdbpdwt = 1963384119)toyspdbpdwt = 670364378;
	if (toyspdbpdwt = 1607887363)toyspdbpdwt = 1575372338;
	if (toyspdbpdwt = 546287118)toyspdbpdwt = 606441888;
	if (toyspdbpdwt = 499947817)toyspdbpdwt = 171680083;
	if (toyspdbpdwt = 217443946)toyspdbpdwt = 1209272959;
	if (toyspdbpdwt = 677713401)toyspdbpdwt = 1402512552;
	if (toyspdbpdwt = 1226710383)toyspdbpdwt = 417142136;
	if (toyspdbpdwt = 1970009475)toyspdbpdwt = 1776743645;
	if (toyspdbpdwt = 270593282)toyspdbpdwt = 1654322786;
}

void gf2emvdkdlw()
{
	float k5syatng0sp = 849405471;
	if (k5syatng0sp = 124307802)k5syatng0sp = 356808542;
	if (k5syatng0sp = 253177467)k5syatng0sp = 604394988;
	if (k5syatng0sp = 218595498)k5syatng0sp = 723614743;
	if (k5syatng0sp = 274706152)k5syatng0sp = 1189443209;
	if (k5syatng0sp = 1000371161)k5syatng0sp = 1035449130;
	if (k5syatng0sp = 1443149692)k5syatng0sp = 535130072;
	if (k5syatng0sp = 1093709162)k5syatng0sp = 1233543387;
	if (k5syatng0sp = 1590570998)k5syatng0sp = 2119327313;
	if (k5syatng0sp = 485324973)k5syatng0sp = 797029989;
	if (k5syatng0sp = 1783066176)k5syatng0sp = 1601082347;
	if (k5syatng0sp = 1368228571)k5syatng0sp = 214048678;
	if (k5syatng0sp = 877932808)k5syatng0sp = 840295348;
	if (k5syatng0sp = 1156968741)k5syatng0sp = 1585051235;
	if (k5syatng0sp = 902524542)k5syatng0sp = 1097183754;
	if (k5syatng0sp = 1669517792)k5syatng0sp = 744016839;
}

void rezf123nwbb()
{
	float hmaguexfrbh = 153449663;
	if (hmaguexfrbh = 1299080758)hmaguexfrbh = 1556057578;
	if (hmaguexfrbh = 376049097)hmaguexfrbh = 1007076404;
	if (hmaguexfrbh = 1409377066)hmaguexfrbh = 452692268;
	if (hmaguexfrbh = 312792591)hmaguexfrbh = 211084896;
	if (hmaguexfrbh = 57944864)hmaguexfrbh = 94220976;
	if (hmaguexfrbh = 1366555512)hmaguexfrbh = 1203657090;
	if (hmaguexfrbh = 1888424495)hmaguexfrbh = 737215800;
	if (hmaguexfrbh = 2122944370)hmaguexfrbh = 497214172;
	if (hmaguexfrbh = 1251185094)hmaguexfrbh = 2002870768;
	if (hmaguexfrbh = 924566343)hmaguexfrbh = 1493143012;
	if (hmaguexfrbh = 707841983)hmaguexfrbh = 376112556;
	if (hmaguexfrbh = 1102645114)hmaguexfrbh = 1628660547;
	if (hmaguexfrbh = 2057742771)hmaguexfrbh = 1626359381;
	if (hmaguexfrbh = 1560365766)hmaguexfrbh = 1594909894;
	if (hmaguexfrbh = 781027910)hmaguexfrbh = 1968573848;
}

void loe0cprntu3()
{
	double rhrmndwmthz = 865366344;
	if (rhrmndwmthz = 1577540633)rhrmndwmthz = 236854663;
	if (rhrmndwmthz = 916698578)rhrmndwmthz = 1846630095;
	if (rhrmndwmthz = 947302768)rhrmndwmthz = 1006425028;
	if (rhrmndwmthz = 593146866)rhrmndwmthz = 996388229;
	if (rhrmndwmthz = 1927037754)rhrmndwmthz = 1024718111;
	if (rhrmndwmthz = 1821676836)rhrmndwmthz = 1405414945;
	if (rhrmndwmthz = 1320610630)rhrmndwmthz = 121896890;
	if (rhrmndwmthz = 798474891)rhrmndwmthz = 1743267390;
	if (rhrmndwmthz = 1626987488)rhrmndwmthz = 899867536;
	if (rhrmndwmthz = 489367421)rhrmndwmthz = 1457286218;
	if (rhrmndwmthz = 413401876)rhrmndwmthz = 1840674494;
	if (rhrmndwmthz = 169750753)rhrmndwmthz = 83209412;
	if (rhrmndwmthz = 922457615)rhrmndwmthz = 1005480495;
	if (rhrmndwmthz = 1436391787)rhrmndwmthz = 1368584379;
	if (rhrmndwmthz = 673143677)rhrmndwmthz = 1970271515;
}