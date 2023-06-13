//------------------------------------------------
//--- 010 Editor v12.0.1 Header file
//
//      File: Endless Ocean .mol file
//   Authors: MDB & NiV
//   Version: 0.1
//   Purpose: 
//  Category: Endless Ocean Modding Experience
// File Mask: 
//  ID Bytes: 
//   History: 
//------------------------------------------------
//10 = T
//20 = R
//30 = T+R
//40 = S
//50 = T+S
//60 = R+S
//70 = T+R+S
typedef struct Ind16(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	ushort IND<bgcolor=bgcol, fgcolor=fgcol>;
};

struct MLCountsOffs_t
{
	ushort MOTFilesCount<bgcolor=cAqua>;
	ushort BonesCount<bgcolor=cAqua>;
	uint BoneNamesOff<bgcolor=cPurple>;
	uint MOTInfoOff<bgcolor=cPurple>;
	uint SemanticFlagsOff<bgcolor=cPurple>;
};

struct Offsets_t
{
	junk32 unk1;
	uint RemapOff<bgcolor=cPurple>;
	uint CorrectionIdxOff<bgcolor=cDkPurple>;
	local uint temp = FTell();
	FSeek(MOLOffLocal + RemapOff);
	ushort idx<bgcolor=cBlack, fgcolor=cGreen>;
	FSeek(MOLOffLocal + CorrectionIdxOff);
	ushort idx2<bgcolor=cBlack, fgcolor=cRed>;
	FSeek(temp);
};

struct MOTInfo_t(MLCountsOffs_t &CountsOffs)
{
	Offsets_t Offs[CountsOffs.MOTFilesCount]<optimize=false>;
	//Ind16 ind(cBlack, cDkGreen);
	//Ind16 ind(cBlack, cLtGreen);
};
/*
struct BoneRemapIdx_t
{
	if (First == 0)
	{
		Ind16 ind(cBlack, cDkGreen);
		First = 1;
	}
	else
	{
		Ind16 ind(cBlack, cLtGreen);
	}
};
*/
struct MOL_t(uint &MOLOffLocal)
{
	RFHeader_t RFHeader[1]<optimize=true>;
	BigEndian();
	MLCountsOffs_t CountsOffs[1]<optimize=false>;
	FSeek(MOLOffLocal + CountsOffs.BoneNamesOff);
	Name_t Bones(cSilver, cNone, 0x10)[CountsOffs.BonesCount]<optimize=true>;
	FSeek(MOLOffLocal + CountsOffs.MOTInfoOff);
	MOTInfo_t MOTInfo(CountsOffs)[1]<optimize=true>;
	FSeek(MOLOffLocal + CountsOffs.SemanticFlagsOff);
	char SemanticFlags[CountsOffs.BonesCount]<bgcolor=cBlack, fgcolor=cGreen>;
};