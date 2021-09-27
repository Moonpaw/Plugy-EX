/*=================================================================
	File created by Yohann NICOLAS.

	Stucture of binary file

=================================================================*/

#pragma once

#include <windows.h>

enum D2CubeItemFlag
{
	CUBE_COWPORTAL		=1,
	CUBE_USEITEM		=0xFF,
	CUBE_USETYPE		=0xFE,
	CUBE_TYPE			=0xFD,
	CUBE_ITEM			=0xFC
};


struct CubeOutput//size: 0x54=84 (source total : fct of dll)
{
	union {
		WORD flag;				//+00
		struct {
			WORD	keepModifiers:1;			//",mod"
			WORD	haveSockets:1;				//",sock=#nbsocket"
			WORD	isEthereal:1;				//",eth"
			WORD	isSpecificItem:1;			//"#itemUniqueName" or "#itemSetName" (set byItemID too)
			WORD	destroysFillers :1;			//",uns"
			WORD	removeFillers:1;			//",rem"
			WORD	regeneratesUnique:1;		//",reg"
			WORD	upgradeToExceptional:1;		//",exc"
			WORD	upgradeToElite:1;			//",eli"
			WORD	repair:1;					//",rep"
			WORD	recharge:1;					//",rch"
		};
	};
	WORD	ID;					//+02
	WORD	specificID;			//+04
	BYTE	quality;			//+06	1=",low"; 2=",nor"; 3=",hiq"; 4=",mag"; 5=",set"; 6=",rar"; 7=",uni"; 8=",crf"; 9=",tmp"
	BYTE	quantityOrNbSockets;//+07	",qty=#quantity" Or ",sock=#nbsocket"
	BYTE	outputType;			//+08	02="Pand. Portal" 01="Cow Portal" FF="usetype"; FE="useitem" FC="#item4Code" FD="#type4Code"
	BYTE	lvl;				//+09	//+55
	BYTE	plvl;				//+0A	//+56
	BYTE	ilvl;				//+0B	//+57
	WORD	Prefix;				//+0C
	WORD	PrefixMin;			//+0E (always 0)
	WORD	PrefixMax;			//+10 (always 0)
	WORD	Suffix;				//+12
	WORD	SuffixMin;			//+14 (always 0)
	WORD	SuffixMax;			//+16 (always 0)
	DWORD	mod1;				//+18	//+64(13)
	WORD	mod1param;			//+1C	//+68
	WORD	mod1min;			//+1E	//+6A
	WORD	mod1max;			//+20	//+6C
	BYTE	mod1chance;			//+22	//+6E
	DWORD	mod2;				//+24	//+70
	WORD	mod2param;			//+28	//+74
	WORD	mod2min;			//+2A	//+76
	WORD	mod2max;			//+2C	//+78
	BYTE	mod2chance;			//+2E	//+7A
	DWORD	mod3;				//+30	//+7C
	WORD	mod3param;			//+34	//+80
	WORD	mod3min;			//+36	//+82
	WORD	mod3max;			//+38	//+84
	BYTE	mod3chance;			//+3A	//+86
	DWORD	mod4;				//+3C	//+88
	WORD	mod41param;			//+40	//+8C
	WORD	mod4min;			//+42	//+8E
	WORD	mod4max;			//+44	//+90
	BYTE	mod4chance;			//+46	//+92
	DWORD	mod5;				//+48	//+94
	WORD	mod5param;			//+4C	//+98
	WORD	mod5min;			//+4E	//+9A
	WORD	mod5max;			//+50	//+9C
	BYTE	mod5chance;			//+52	//+9E
};


struct CubeInput//size: 8 (source total : fct of dll)
{
	union {
		WORD flag;			//+00
		struct {
			WORD	byItemID:1;					//"#item4Code" or "any"
			WORD	byItemTypeID:1;				//"#itemType4Code"
			WORD	haveNoSocket:1;				//",nos"
			WORD	haveSockets:1;				//",sock"
			WORD	isEthereal:1;				//",eth"
			WORD	isNotEthereal:1;			//",noe"
			WORD	isSpecificItem:1;			//"#itemUniqueName" or "#itemSetName" (set byItemID too)
			WORD	includeUpgradedVersions:1;	//",upg"
			WORD	isBasic:1;					//",bas"
			WORD	isExceptional:1;			//",exc"
			WORD	isElite:1;					//",eli"
			WORD	isNotRuneword:1;			//",nru"
		};
	};
	WORD	ID;				//+02	FFFF = any items
	WORD	specificID;		//+04
	BYTE	quality;		//+06	1=",low"; 2=",nor"; 3=",hiq"; 4=",mag"; 5=",set"; 6=",rar"; 7=",uni"; 8=",crf"; 9=",tmp"
	BYTE	quantity;		//+07	",qty=#quantity"
};


struct CubeMainBIN//size: 0x148=328  (source total : fct of dll) (total size in LoD1.10 : BDA0)
{
	BYTE		enabled;	//+00
	BYTE		ladder;		//+01
	BYTE		minDiff;	//+02
	BYTE		playerClass;//+03 FF=all classes
	BYTE		op;			//+04
	DWORD		param;		//+08
	DWORD		value;		//+0C
	BYTE		numinputs;	//+10
	WORD		version;	//+12
	CubeInput	input1;		//+14
	CubeInput	input2;		//+1C
	CubeInput	input3;		//+24
	CubeInput	input4;		//+2C
	CubeInput	input5;		//+34
	CubeInput	input6;		//+3C
	CubeInput	input7;		//+44
	CubeOutput	output1;	//+4C
	CubeOutput	output2;	//+A0
	CubeOutput	output3;	//+F4
};

struct TreasureClassBIN
{

};

struct ObjectsBIN
{

};

struct ExperienceBIN//size=0x20
{
	DWORD Amazon;
	DWORD Sorceress;
	DWORD Necromancer;
	DWORD Paladin;
	DWORD Barbarian;
	DWORD Druid;
	DWORD Assassin;
	DWORD ExpRatio;
};

struct LevelsBIN//size=0x220
{
};

struct GemsBIN //size: 0xC0=192 (source : fct of dll)
{
	char	name[0x20];		//+00
	char	letter[6];		//+20
	BYTE	uk1[2];			//+26
	DWORD	code;			//+28
	BYTE	uk2[2];			//+2C
	BYTE	nummods;		//+2E
	BYTE	transform;		//+2F
	int		weaponmod1code;	//+30
	DWORD	weaponmod1param;//+34
	DWORD	weaponmod1min;	//+38
	DWORD	weaponmod1max;	//+3C
	int		weaponmod2code;	//+40
	DWORD	weaponmod2param;//+44
	DWORD	weaponmod2min;	//+48
	DWORD	weaponmod2max;	//+4C
	int		weaponmod3code;	//+50
	DWORD	weaponmod3param;//+54
	DWORD	weaponmod3min;	//+58
	DWORD	weaponmod3max;	//+5C
	int		helmmod1code;	//+60
	DWORD	helmmod1param;	//+64
	DWORD	helmmod1min;	//+68
	DWORD	helmmod1max;	//+6C
	int		helmmod2code;	//+70
	DWORD	helmmod2param;	//+74
	DWORD	helmmod2min;	//+78
	DWORD	helmmod2max;	//+7C
	int		helmmod3code;	//+80
	DWORD	helmmod3param;	//+84
	DWORD	helmmod3min;	//+88
	DWORD	helmmod3max;	//+8C
	int		shieldmod1code;	//+90
	DWORD	shieldmod1param;//+94
	DWORD	shieldmod1min;	//+98
	DWORD	shieldmod1max;	//+9C
	int		shieldmod2code;	//+A0
	DWORD	shieldmod2param;//+A4
	DWORD	shieldmod2min;	//+A8
	DWORD	shieldmod2max;	//+AC
	int		shieldmod3code;	//+B0
	DWORD	shieldmod3param;//+B4
	DWORD	shieldmod3min;	//+B8
	DWORD	shieldmod3max;	//+BC
};

struct ItemsBIN //size: 0x1A8=424 (source : fct of dll)
{
	char	FlippyFile[0x20];		//+00
	char	InvFile[0x20];			//+20
	char	UniqueInvFile[0x20];	//+40
	char	SetInvFile[0x20];		//+60
	DWORD	ItemCode;				//+80
	DWORD	NormCode;				//+84
	DWORD	UberCode;				//+88
	DWORD	HellCode;				//+8C
	DWORD	AlternateGfx;			//+90
	DWORD	pSpell;					//+94
	WORD	State;					//+98
	WORD	cState1;				//+9A
	WORD	cState2;				//+9C
	WORD	Stat1;					//+9E
	WORD	Stat2;					//+A0
	WORD	Stat3;					//+A2
	DWORD	Calc1;					//+A4
	DWORD	Calc2;					//+A8
	DWORD	Calc3;					//+AC
	DWORD	Len;					//+B0
	WORD	SpellDesc;				//+B4
	WORD	SpellDescStr;			//+B6
	DWORD	SpellDescCalc;			//+B8
	DWORD	BetterGem;				//+BC
	DWORD	WClass;					//+C0
	DWORD	TwoHandedWClass;		//+C4
	DWORD	TMogType;				//+C8
	DWORD	MinAC;					//+CC
	DWORD	MaxAC;					//+D0
	DWORD	GambleCost;				//+D4
	DWORD	Speed;					//+D8
	DWORD	BitField;				//+DC
	DWORD	Cost;					//+E0
	DWORD	MinStack;				//+E4
	DWORD	MaxStack;				//+E8
	DWORD	SpawnStack;				//+EC
	DWORD	GemOffset;				//+F0
	WORD	NameStr;				//+F4
	WORD	Version;				//+F6
	WORD	AutoPrefix;				//+F8
	WORD	MissileType;			//+FA
	BYTE	Rarity;					//+FC
	BYTE	Level;					//+FD
	BYTE	MinDam;					//+FE
	BYTE	MaxDam;					//+FF
	BYTE	MinMisDam;				//+100
	BYTE	MaxMisDam;				//+101
	BYTE	TwoHandMinDam;			//+102
	BYTE	TwoHandMaxDam;			//+103
	BYTE	RangeAdder;				//+104
	BYTE	NotUsed1;				//+105
	WORD	StrBonus;				//+106
	WORD	DexBonus;				//+108
	WORD	RegStr;					//+10A
	WORD	RegDex;					//+10C
	BYTE	Absorbs;				//+10E
	BYTE	InvWidth;				//+10F
	BYTE	InvHeight;				//+110
	BYTE	Block;					//+111
	BYTE	Durability;				//+112
	BYTE	NoDurability;			//+113
	BYTE	Missile;				//+114
	BYTE	Component;				//+115
	BYTE	RArm;					//+116
	BYTE	LArm;					//+117
	BYTE	Torso;					//+118
	BYTE	Legs;					//+119
	BYTE	RSpad;					//+11A
	BYTE	LSpad;					//+11B
	BYTE	TwoHanded;				//+11C
	BYTE	Usable;					//+11D
	WORD	Type;					//+11E
	WORD	Type2;					//+120
	BYTE	SubType;				//+122
	BYTE	NotUsed2;				//+123
	WORD	DropSound;				//+124
	WORD	UseSound;				//+126
	BYTE	DropSfxFrame;			//+128
	BYTE	Unique;					//+129
	BYTE	Quest;					//+12A
	BYTE	QuestDiffCheck;			//+12B
	BYTE	Transparent;			//+12C
	BYTE	TransTbl;				//+12D
	BYTE	NotUsed3;				//+12E
	BYTE	LightRadius;			//+12F
	BYTE	Belt;					//+130
	BYTE	AutoBelt;				//+131
	BYTE	Stackable;				//+132
	BYTE	Spawnable;				//+133
	BYTE	SpellIcon;				//+134
	BYTE	DurWarning;				//+135
	BYTE	QntWaning;				//+136
	BYTE	HasInv;					//+137
	BYTE	GemSockets;				//+138
	BYTE	TransmoGrify;			//+139
	BYTE	TMogMin;				//+13A
	BYTE	TMogMax;				//+13B
	BYTE	HitClass;				//+13C
	BYTE	OneOrTwoHanded;			//+13D
	BYTE	GemApplyType;			//+13E
	BYTE	LevelReq;				//+13F
	BYTE	MagicLvl;				//+140
	BYTE	Transform;				//+141
	BYTE	InvTrans;				//+142
	BYTE	CompactSave;			//+143
	BYTE	SkipName;				//+144
	BYTE	NotUsed4;				//+145
	BYTE	VendorMin[17];			//+146
	BYTE	VendorMax[17];			//+157
	BYTE	VendorMagicMin[17];		//+168
	BYTE	VendorMagicMax[17];		//+179
	BYTE	VendorMagicLvl[17];		//+18A
	BYTE	NotUsed5;				//+19B
	DWORD	NightmareUpgrade;		//+19C
	DWORD	HellUpgrade;			//+1A0
	BYTE	PermStoreItem;			//+1A4
	BYTE	Multibuy;				//+1A5
	WORD	zeros;					//+1A6
};

struct RunesBIN	//size: 0x120=288 (1.10 ok)
{
	char	Name[0x40];		//+00
	char	RuneName[0x40];	//+40
	BYTE	Complete;		//+80
	BYTE	Server;			//+81
	WORD	RuneNameID;		//+82
	WORD	zero;			//+84 (=0x0000)
	WORD	Itypes[6];		//+86
	WORD	Etypes[3];		//+92
	int		Runes[6];		//+98
	DWORD	t1code1;		//+B0
	DWORD	t1param1;		//+B4
	DWORD	t1min1;			//+B8
	DWORD	t1max1;			//+BC
	DWORD	t1code2;		//+C0
	DWORD	t1param2;		//+C4
	DWORD	t1min2;			//+C8
	DWORD	t1max2;			//+CC
	DWORD	t1code3;		//+D0
	DWORD	t1param3;		//+D4
	DWORD	t1min3;			//+D8
	DWORD	t1max3;			//+DC
	DWORD	t1code4;		//+E0
	DWORD	t1param4;		//+E4
	DWORD	t1min4;			//+E8
	DWORD	t1max4;			//+EC
	DWORD	t1code5;		//+F0
	DWORD	t1param5;		//+F4
	DWORD	t1min5;			//+F8
	DWORD	t1max5;			//+FC
	DWORD	t1code6;		//+100
	DWORD	t1param6;		//+104
	DWORD	t1min6;			//+108
	DWORD	t1max6;			//+10C
	DWORD	t1code7;		//+110
	DWORD	t1param7;		//+114
	DWORD	t1min7;			//+118
	DWORD	t1max7;			//+11C
};

struct CharStatsBIN //size= 0xC4=196
{
	WCHAR	nameU[0x10];		//+00
	char	name[0x10];			//+20
	BYTE	baseSTR;			//+30
	BYTE	baseDEX;			//+31
	BYTE	baseENE;			//+32
	BYTE	baseVIT;			//+33
	BYTE	baseStamina;		//+34
	BYTE	hpadd;				//+35
	BYTE	percentStr;			//+36
	BYTE	percentInt;			//+37
	BYTE	percentDex;			//+38
	BYTE	percentVit;			//+39
	BYTE	manaRegen;			//+3A
	BYTE	__3B;				//+3B
	DWORD	toHitFactor;		//+3C
	BYTE	walkVelocity;		//+40
	BYTE	runVelocity;		//+41
	BYTE	runDrain;			//+42
	BYTE	lifePerLevel;		//+43
	BYTE	staminaPerLevel;	//+44
	BYTE	manaPerLevel;		//+45
	BYTE	lifePerVitality;	//+46
	BYTE	staminaPerVitality;	//+47
	BYTE	manaPerMagic;		//+48
	BYTE	blockFactor;		//+49
	WORD	__4A_startSkill;	//+4A
	DWORD	baseWClass;			//+4C
	BYTE	StatPerLevel;		//+50
	BYTE	__51;				//+51
	WORD	StrAllSkills;		//+52
	WORD	StrSkillTab1;		//+54
	WORD	StrSkillTab2;		//+56
	WORD	StrSkillTab3;		//+58
	WORD	StrClassOnly;		//+5A
	DWORD	item1;
	BYTE	item1Loc;
	BYTE	item1Count;
	WORD	item1Unknown;
	DWORD	item2;
	BYTE	item2Loc;
	BYTE	item2Count;
	WORD	item2Unknown;
	DWORD	item3;
	BYTE	item3Loc;
	BYTE	item3Count;
	WORD	item3Unknown;
	DWORD	item4;
	BYTE	item4Loc;
	BYTE	item4Count;
	WORD	item4Unknown;
	DWORD	item5;
	BYTE	item5Loc;
	BYTE	item5Count;
	WORD	item5Unknown;
    DWORD	item6;
	BYTE	item6Loc;
	BYTE	item6Count;
	WORD	item6Unknown;
	DWORD	item7;
	BYTE	item7Loc;
	BYTE	item7Count;
	WORD	item7Unknown;
	DWORD	item8;
	BYTE	item8Loc;
	BYTE	item8Count;
	WORD	item8Unknown;
	DWORD	item9;
	BYTE	item9Loc;
	BYTE	item9Count;
	WORD	item9Unknown;
	DWORD	item10;
	BYTE	item10Loc;
	BYTE	item10Count;
	WORD	item10Unknown;
	BYTE	unknown2[0x18];
};

struct UniqueItemsBIN //size=0x14C (332)
{
	WORD	uniqueId;		//+00
	BYTE	uk1[0x20];		//+02
	WORD	uniqueNameId;	//+22
	BYTE	uk2[0x08];		//+24
	union {
		BYTE	flag;		//+2C
		struct {
			BYTE ukf:2;
			BYTE carry1:1;
			BYTE ladder:1;
		};
	};
	BYTE	uk3[0x11F];		//+2D
};

struct SetsBIN //size=0x128 (source : fct of dll)
{
	WORD	setNum;			//+00
	WORD	setNameIndex;	//+02
	BYTE	uk3[0x124];		//+04
};

struct SetItemsBIN //size=0x1B8 (source : fct of dll)
{
	WORD	setNum;			//+00
	char	index[0x20];	//+02
	BYTE	uk1;			//+04
	WORD	setNameId;		//+24
	BYTE	uk2[0x6];		//+26
	WORD	setId;			//+2C
	BYTE	uk3[0x18A];		//+2E
};


struct SkillDescBIN //size=0x120=288  (source : fct of dll)
{
	BYTE	uk1[0x08];		//+00
	WORD	strNameID;		//+08
	WORD	strShortID;		//+0A
	WORD	strLongID;		//+0C
	WORD	strAltID;		//+0E
	BYTE	uk2[0x110];		//+10
};


struct SkillsBIN //size=0x23C (572)
{
	WORD	skillID;		//+00
	BYTE	uk1[0x0A];		//+02
	BYTE	charclass;		//+0C
	BYTE	uk2[0x08];		//+10
	WORD	itypea1;		//+18
	WORD	itypea2;		//+1A
	WORD	itypea3;		//+1C
	WORD	itypeb1;		//+1E
	WORD	itypeb2;		//+20
	WORD	itypeb3;		//+22
	WORD	etypea1;		//+24
	WORD	etypea2;		//+26
	WORD	etypeb1;		//+28
	WORD	etypeb2;		//+2A
	BYTE	uk3[0x100];		//+2C
	WORD	maxlvl;			//+12C
	BYTE	uk4[0x42];		//+12E
	int		skpoints;		//+170
	WORD	reqlevel;		//+174
	BYTE	uk5[0x1E];		//+176
	DWORD	skilldesc;		//+194 (DWORD ?)
	BYTE	uk6[0xA4];		//+198
};

struct DifficultyLevelsBIN
{
	DWORD	resistPenalty;	//+00
	BYTE	uk1[1];			//+04
};

struct SuperUniqueBIN
{
};

struct MonStatsBIN	//size=0x1A8 (424)
{
	BYTE	uk1[0x6];		//+00
	WORD	monsterNameID;	//+06
	BYTE	uk2[0x168];		//+08
	WORD	skill[8];		//+170
	BYTE	skillArg[8];	//+180
	BYTE	uk3[0x20];		//+188
};							//+1A8

struct ItemTypesBIN //size=0xE4 (228) (source : fct of dll)
{
	DWORD	code;			//+00
	BYTE	uk1[0x11];		//+04
	BYTE	rare;			//+15
	BYTE	uk2[0x09];		//+16
	BYTE	staffmods;		//+1F
	BYTE	uk3[0xC4];		//+20
};							//+E4

struct AffixBIN //size=0x90 (144) (source : fct of dll) magicsuffix + magicprefix + automagic
{
	char	name[0x20];		//+00
	WORD	nameCode;		//+20
	WORD	version;		//+22
	DWORD	mod1code;		//+24
	DWORD	mod1param;		//+28
	DWORD	mod1min;		//+2C
	DWORD	mod1max;		//+30
	DWORD	mod2code;		//+34
	DWORD	mod2param;		//+38
	DWORD	mod2min;		//+3C
	DWORD	mod2max;		//+40
	DWORD	mod3code;		//+44
	DWORD	mod3param;		//+48
	DWORD	mod3min;		//+4C
	DWORD	mod3max;		//+50
	BYTE	spawnable;		//+54
	BYTE	uk1[0x1];		//+55
	WORD	transformcolor;	//+56
	DWORD	level;			//+58
	DWORD	group;			//+5C
	DWORD	maxlevel;		//+60
	BYTE	rare;			//+64
	BYTE	levelreq;		//+65
	BYTE	classspecific;	//+66
	BYTE	classf;			//+67
	BYTE	classlevelreq;	//+68
	BYTE	uk2[0x1];		//+69
	WORD	itype1;			//+6A
	WORD	itype2;			//+6C
	WORD	itype3;			//+6E
	WORD	itype4;			//+70
	WORD	itype5;			//+72
	WORD	itype6;			//+74
	WORD	itype7;			//+76
	WORD	etype1;			//+78
	WORD	etype2;			//+7A
	WORD	etype3;			//+7C
	WORD	etype4;			//+7E
	WORD	etype5;			//+80
	BYTE	frequency;		//+82
	BYTE	uk3[0x1];		//+83
	DWORD	divide;			//+84
	DWORD	multiply;		//+88
	DWORD	add;			//+8C
};

struct PropertiesBIN // size=0x2E (46) (source total : fct of dll)
{
	WORD	modcode;		//+00
	BYTE	set1;			//+02
	BYTE	set2;			//+03
	BYTE	set3;			//+04
	BYTE	set4;			//+05
	BYTE	set5;			//+06
	BYTE	set6;			//+07
	BYTE	set7;			//+08
	BYTE	uk1[0x1];		//+09

	WORD	val1;			//+0A
	WORD	val2;			//+0C
	WORD	val3;			//+0E
	WORD	val4;			//+10
	WORD	val5;			//+12
	WORD	val6;			//+14
	WORD	val7;			//+16

	BYTE	func1;			//+18
	BYTE	func2;			//+19
	BYTE	func3;			//+1A
	BYTE	func4;			//+1B
	BYTE	func5;			//+1C
	BYTE	func6;			//+1D
	BYTE	func7;			//+1E
	BYTE	uk2[0x1];		//+1F

	WORD	stat1;			//+20
	WORD	stat2;			//+22
	WORD	stat3;			//+24
	WORD	stat4;			//+26
	WORD	stat5;			//+28
	WORD	stat6;			//+2A
	WORD	stat7;			//+2C
};


struct ItemStatCostBIN // size=0x144 (324) (source total : fct of dll) maxline = 0x1FF = 511
{
	DWORD	statID;			//+00
	union					//+04
	{
		DWORD	flags;
		struct
		{
			DWORD sendOther:1;			//0x00000001
			DWORD signedf:1;			//0x00000002
			DWORD damagerelated:1;		//0x00000004
			DWORD itemspecific:1;		//0x00000008
			DWORD direct:1;				//0x00000010
			DWORD fuk1:4;				//0x000001E0
			DWORD updateanimrate:1;		//0x00000200
			DWORD fmin:1;				//0x00000400
			DWORD fcallback:1;			//0x00000800
			DWORD saved:1;				//0x00001000
			DWORD cvssigned:1;			//0x00002000
			DWORD fuk2:18;				//0xFFFFC000
		};
	};
	BYTE	sendBits;		//+08
	BYTE	sendParamBits;	//+09
	BYTE	csvbits;		//+0A
	BYTE	csvparam;		//+0B
	DWORD	divide;			//+0C
	DWORD	multiply;		//+10
	DWORD	add;			//+14
	BYTE	valshift;		//+18
	BYTE	saveBits;		//+19
	BYTE	saveBits109;	//+1A	//are only for conversion
	BYTE	uk2[0x1];		//+1B
	DWORD	saveAdd;		//+1C
	DWORD	saveAdd109;		//+20	//are only for conversion
	DWORD	saveParamBits;	//+24
	BYTE	uk3[0x4];		//+28
	DWORD	minaccr;		//+2C
	BYTE	encode;			//+30
	BYTE	uk4[0x1];		//+31
	WORD	maxstat;		//+32
	WORD	descpriority;	//+34
	BYTE	descfunc;		//+36
	BYTE	descval;		//+37
	WORD	descstrpos;		//+38
	WORD	descstrneg;		//+3A
	WORD	descstr2;		//+3C
	WORD	dgrp;			//+3E
	BYTE	dgrpfunc;		//+40
	BYTE	dgrpval;		//+41
	WORD	dgrpstrpos;		//+42
	WORD	dgrpstrneg;		//+44
	WORD	dgrpstr2;		//+46
	WORD	itemevent1;		//+48
	WORD	itemevent2;		//+4A
	WORD	itemeventfunc1;	//+4C
	WORD	itemeventfunc2;	//+4E
	BYTE	keepzero;		//+50
	BYTE	uk5[0x3];		//+51
	BYTE	op;				//+54
	BYTE	opParam;		//+55
	WORD	opStat1;		//+58
	WORD	opStat2;		//+5A
	WORD	opStat3;		//+5C
	BYTE	uk6[0xE2];		//+5E
	DWORD	stuff;			//+140
};

struct InventoryBIN // size=0xF0 (240) (source total : fct of dll)
{
	DWORD	invLeft;		//+00
	DWORD	invRight;		//+04
	DWORD	invTop;			//+08
	DWORD	invBottom;		//+0C
	BYTE	gridX;			//+10
	BYTE	gridY;			//+11
	BYTE	uk1[2];			//+12
	DWORD	gridLeft;		//+14
	DWORD	gridRight;		//+18
	DWORD	gridTop;		//+1C
	DWORD	gridBottom;		//+20
	BYTE	gridBoxWidth;	//+24
	BYTE	gridBoxHeight;	//+25
	BYTE	uk2[2];			//+26
	DWORD	rArmLeft;		//+28
	DWORD	rArmRight;		//+2C
	DWORD	rArmTop;		//+30
	DWORD	rArmBottom;		//+34
	BYTE	rArmWidth;		//+38
	BYTE	rArmHeight;		//+39
	BYTE	uk3[2];			//+3A
	DWORD	torsoLeft;		//+3C
	DWORD	torsoRight;		//+40
	DWORD	torsoTop;		//+44
	DWORD	torsoBottom;	//+48
	BYTE	torsoWidth;		//+4C
	BYTE	torsoHeight;	//+4D
	BYTE	uk4[2];			//+4E
	DWORD	lArmLeft;		//+50
	DWORD	lArmRight;		//+54
	DWORD	lArmTop;		//+58
	DWORD	lArmBottom;		//+5C
	BYTE	lArmWidth;		//+60
	BYTE	lArmHeight;		//+61
	BYTE	uk5[2];			//+62
	DWORD	headLeft;		//+64
	DWORD	headRight;		//+68
	DWORD	headTop;		//+6C
	DWORD	headBottom;		//+70
	BYTE	headWidth;		//+74
	BYTE	headHeight;		//+75
	BYTE	uk6[2];			//+76
	DWORD	neckLeft;		//+78
	DWORD	neckRight;		//+7C
	DWORD	neckTop;		//+80
	DWORD	neckBottom;		//+84
	BYTE	neckWidth;		//+88
	BYTE	neckHeight;		//+89
	BYTE	uk7[2];			//+8A
	DWORD	rHandLeft;		//+8C
	DWORD	rHandRight;		//+90
	DWORD	rHandTop;		//+94
	DWORD	rHandBottom;	//+98
	BYTE	rHandWidth;		//+9C
	BYTE	rHandHeight;	//+9D
	BYTE	uk8[2];			//+9E
	DWORD	lHandLeft;		//+A0
	DWORD	lHandRight;		//+A4
	DWORD	lHandTop;		//+A8
	DWORD	lHandBottom;	//+AC
	BYTE	lHandWidth;		//+B0
	BYTE	lHandHeight;	//+B1
	BYTE	uk9[2];			//+B2
	DWORD	beltLeft;		//+B4
	DWORD	beltRight;		//+B8
	DWORD	beltTop;		//+BC
	DWORD	beltBottom;		//+C0
	BYTE	beltWidth;		//+C4
	BYTE	beltHeight;		//+C5
	BYTE	uk10[2];		//+C6
	DWORD	feetLeft;		//+C8
	DWORD	feetRight;		//+CC
	DWORD	feetTop;		//+D0
	DWORD	feetBottom;		//+D4
	BYTE	feetWidth;		//+D8
	BYTE	feetHeight;		//+D9
	BYTE	uk11[2];		//+DA
	DWORD	glovesLeft;		//+DC
	DWORD	glovesRight;	//+E0
	DWORD	glovesTop;		//+E4
	DWORD	glovesBottom;	//+E8
	BYTE	glovesWidth;	//+EC
	BYTE	glovesHeight;	//+ED
	BYTE	uk12[2];		//+EE
};


struct DataTables//01EE6A20 * 01FDA2D0 //second comments=1.11
{
	BYTE			uk1[0xA78];			//+000
	MonStatsBIN*	monStats;			//+A78 //1.11 and 1.10
	BYTE			uk2[0x4];			//+A7C
	DWORD			nbMonStats;			//+A80 //1.11 and 1.10
	BYTE			uk3[0x108];			//+A84
	SkillDescBIN*	skilldesc;			//+B8C
	BYTE			uk4[0x4];			//+B90
	DWORD			nbSkilldesc;		//+B94
	SkillsBIN*		skills;				//+B98
	BYTE			uk5[0x4];			//+B9C
	DWORD			nbSkills;			//+BA0
	int*			nbSkillsPerPlayer;	//+BA4
	int				maxSkillsPerPlayer;	//+BA8
	WORD*			playerSkills;		//+BAC
	BYTE			uk6[0x14];			//+BB0
	CharStatsBIN*	charStats;			//+BC4
	DWORD			nbCharStats;		//+BC8
	ItemStatCostBIN* itemStatCost;		//+BCC
	BYTE			uk7[4];				//+BD0
	DWORD			nbItemStatCosts;	//+BD4
	WORD*			statsDescPriority;	//+BD8
	DWORD			nbStatsDescPriority;//+BDC
	BYTE			uk8[0x18];			//+BE0
	ItemTypesBIN*	itemTypes;			//+BF8
	DWORD			nbItemTypes;		//+BFC
	BYTE			uk9[0x0C];			//+C00
	SetsBIN*		sets;				//+C0C //1.11 and 1.10
	DWORD			nbSets;				//+C10 //1.11 and 1.10
	BYTE			uk9b[0x4];			//+C14
	SetItemsBIN*	setItems;			//+C18 //1.11 and 1.10
	DWORD			nbSetItems;			//+C1C //1.11 and 1.10
	BYTE			uk10[0x4];			//+C20
	UniqueItemsBIN*	uniqueItems;		//+C24 //1.11 and 1.10
	DWORD			nbUniqueItems;		//+C28 //1.11 and 1.10
	BYTE			uk11[0x2C];			//+C2C
	LevelsBIN*		levels;				//+C58
	DWORD			nbLevels;			//+C5C
	BYTE			uk12[0x64];			//+C60
	CubeMainBIN*	cubemain;			//+CC4 //14C0 by 148 for 1.11
	DWORD			nbCubemain;			//+CC8 //14C4 for 1.11
	DWORD			nbInventory;		//+CCC
	InventoryBIN*	inventory;			//+CD0
	BYTE			uk13[0x04];			//+CD4
	DWORD			nbItems;			//+CD8
	ItemsBIN*		items;				//+CDC
	ItemsBIN*		itemsBis;			//+CE0
	BYTE			uk14[0x1F8];		//+CDC
	DWORD			nbRunes;			//+EDC
	RunesBIN*		runes;				//+EE0
};
