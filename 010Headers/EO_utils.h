//------------------------------------------------
//--- 010 Editor v12.0.1 Header file
//
//      File: Endless Ocean Utilities
//   Authors: MDB & NiV
//   Version: 0.1.5
//   Purpose: 
//  Category: Endless Ocean Modding Experience
// File Mask: 
//  ID Bytes: 
//   History: 
//------------------------------------------------
/*
8-Bit Signed Integer - char, byte, CHAR, BYTE
8-Bit Unsigned Integer - uchar, ubyte, UCHAR, UBYTE
16-Bit Signed Integer - short, int16, SHORT, INT16
16-Bit Unsigned Integer - ushort, uint16, USHORT, UINT16, WORD
32-Bit Signed Integer - int, int32, long, INT, INT32, LONG
32-Bit Unsigned Integer - uint, uint32, ulong, UINT, UINT32, ULONG, DWORD
64-Bit Signed Integer - int64, quad, QUAD, INT64, __int64
64-Bit Unsigned Integer - uint64, uquad, UQUAD, UINT64, QWORD, __uint64
32-Bit Floating Point Number - float, FLOAT
64-Bit Floating Point Number - double, DOUBLE
16-Bit Floating Point Number - hfloat, HFLOAT
Date Types - DOSDATE, DOSTIME, FILETIME, OLETIME, time_t, time64_t
cBlack - 0x000000
cRed - 0x0000ff
cDkRed - 0x000080
cLtRed - 0x8080ff
cGreen - 0x00ff00
cDkGreen - 0x008000
cLtGreen - 0x80ff80
cBlue - 0xff0000
cDkBlue - 0x800000
cLtBlue - 0xff8080
cPurple - 0xff00ff
cDkPurple - 0x800080
cLtPurple - 0xffe0ff
cAqua - 0xffff00
cDkAqua - 0x808000
cLtAqua - 0xffffe0
cYellow - 0x00ffff
cDkYellow - 0x008080
cLtYellow - 0x80ffff
cDkGray - 0x404040
cGray - 0x808080,
cSilver - 0xc0c0c0,
cLtGray - 0xe0e0e0
cWhite - 0xffffff
cNone - 0xffffffff
*/
typedef ubyte junk<hidden=true,fgcolor=cRed,bgcolor=cBlack>;
typedef ushort junk16<hidden=true,fgcolor=cRed,bgcolor=cBlack>;
typedef uint junk32<hidden=true,fgcolor=cRed,bgcolor=cBlack>;
typedef char junkchar<hidden=true,fgcolor=cRed,bgcolor=cBlack>;
local int bgcol, fgcol;

enum <byte> RFFileType
{
	vdl = 0,
	tdl = 1,
	txs = 2,
	mdl = 5,
	mot = 6,
	mol = 7
};

struct Name_t(int bcol, int fcol, int Size)
{
	bgcol = bcol; fgcol = fcol;
	char Name[Size]<bgcolor=bgcol, fgcolor=fgcol>;
};

typedef struct bvec4_t(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	ubyte X, Y, Z, W;
} BVec4 <read=read_bvec4, bgcolor=bgcol, fgcolor=fgcol>;
string read_bvec4(BVec4 &v) {
	string s;
	SPrintf(s, "%02X %02X %02X %02X",
		v.X, v.Y, v.Z, v.W);
	return s;
}

typedef struct vec2_t(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	float X, Y;
} Vec2 <read=read_vec2, bgcolor=bgcol, fgcolor=fgcol>;
string read_vec2(Vec2 &v)
{
	string s;
	SPrintf(s, "%7.5f %7.5f", v.X, v.Y);
	return s;
}

typedef struct vec3_t(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	float X, Y, Z;
} Vec3<read=read_vec3, bgcolor=bgcol, fgcolor=fgcol>;
string read_vec3(Vec3 &v)
{
	local string s;
	SPrintf(s, "%11f %11f %11f", v.X, v.Y, v.Z);
	//SPrintf(s, "%7.5f %7.5f %7.5f", v.X, v.Y, v.Z);
	return s;
}

typedef struct vec3stride_t(int bcol, int fcol, int stride)
{
	bgcol = bcol; fgcol = fcol;
	float X, Y, Z;
	stride = stride - 0xC;
	FSkip(stride);
} Vec3Stride<read=read_vec3stride, bgcolor=bgcol, fgcolor=fgcol>;
string read_vec3stride(Vec3Stride &v)
{
	string s;
	SPrintf(s, "%7.5f %7.5f %7.5f", v.X, v.Y, v.Z);
	return s;
}

typedef struct vec4_t(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	float X, Y, Z, W;
} Vec4 <read=read_vec4, bgcolor=bgcol, fgcolor=fgcol>;
string read_vec4(Vec4 &v)
{
	local string s;
	SPrintf(s, "%11f %11f %11f %11f", v.X, v.Y, v.Z, v.W);
	//SPrintf(s, "%7.5f %7.5f %7.5f %7.5f", v.X, v.Y, v.Z, v.W);
	return s;
}

typedef struct mat44_t(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	Vec4 M0(bgcol, fgcol);
	Vec4 M1(bgcol, fgcol);
	Vec4 M2(bgcol, fgcol);
	Vec4 M3(bgcol, fgcol);
} Mat44 <read=read_mat44>;
string read_mat44(Mat44 &v)
{
	string s;
	SPrintf(s,
"\n%11f\t%11f\t%11f\t%11f %11f\t%11f\t%11f\t%11f %11f\t%11f\t%11f\t%11f %11f\t%11f\t%11f\t%11f",
v.M0.X, v.M0.Y, v.M0.Z, v.M0.W,
v.M1.X, v.M1.Y, v.M1.Z, v.M1.W,
v.M2.X, v.M2.Y, v.M2.Z, v.M2.W,
v.M3.X, v.M3.Y, v.M3.Z, v.M3.W);
	return s;
}

struct Offs_t(int bcol, int fcol)
{
	bgcol = bcol; fgcol = fcol;
	int Off<bgcolor=bgcol, fgcolor=fgcol>;
};

struct RFFile_t
{
	if (MagicRFVersion == "2") //RF2, most common
	{
		char FileName[0x14]<bgcolor=cSilver>;
		uint FileSize<bgcolor=cBlue>;
		uint FileOff<bgcolor=cPurple>;
		ubyte FileType<bgcolor=cRed>;
		ubyte unk1<bgcolor=cRed>;
		ubyte IsInFile<bgcolor=cRed>;
		ubyte unk2<bgcolor=cRed>;
	}
	else //RFP / RFS, rare
	{
		char FileName[0x10]<bgcolor=cSilver>;
		uint FileOff<bgcolor=cPurple>;
		uint FileSize<bgcolor=cBlue>;
		uint unkFlags<bgcolor=cRed>;
		ubyte FileType<bgcolor=cRed>;
		ubyte unk1<bgcolor=cRed>;
		ubyte IsInFile<bgcolor=cRed>;
		ubyte unk2<bgcolor=cRed>;
	}
};

struct RFHeader_t
{
	LittleEndian();
	char MagicRF[2]<bgcolor=cRed>;
	char MagicRFVersion[1]<bgcolor=cRed>;
	char MagicRFType[2]<bgcolor=cRed>;
	char MagicRFTypeVersion[1]<bgcolor=cRed>;
	ushort FileCount<bgcolor=cAqua>;
	ushort FilesListSize<bgcolor=cBlue>;
	ushort Flag<bgcolor=cBlack, fgcolor=cRed>;
	uint HeaderSize<bgcolor=cBlue>;

	RFFile_t Files[FileCount]<optimize=true>;
};

void Align(int alignment)
{
	local int val = FTell();
	local int pad_size = (-val) & (alignment - 1);
	if (pad_size != 0)
		byte pad[pad_size];
}

void PrintPos(string v)
{
	Printf("[0x%08X]%s", FTell(), v);
}

void PrintHex(int64 pos, int n)
{
	if (n > FileSize())
		n = FileSize();
	local int i = 0;
	local uchar buf[n];
	ReadBytes(buf, pos, n);
	Printf("             00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
	for (i = 0; i < n; i++)
	{
		if (i % 0x10 == 0)
			Printf("\n[0x%08X] ", i);
		Printf("%02X ", buf[i]);
	}
	Printf("\n");
}

float Mat44ToQuatX(Mat44 &v)
{
	local float tr = v.M0.X + v.M1.Y + v.M2.Z;
	local float S = 0;
	local float qx = 0;
	if (tr > 0)
	{ 
		S = Sqrt(tr+1.0) * 2;
		qx = (v.M2.Y - v.M1.Z) / S;
	}
	else if ((v.M0.X > v.M1.Y)&&(v.M0.X > v.M2.Z))
	{ 
		S = Sqrt(1.0 + v.M0.X - v.M1.Y - v.M2.Z) * 2;
		qx = 0.25 * S;
	}
	else if (v.M1.Y > v.M2.Z)
	{ 
		S = Sqrt(1.0 + v.M1.Y - v.M0.X - v.M2.Z) * 2;
		qx = (v.M0.Y + v.M1.X) / S; 
	}
	else
	{
		S = Sqrt(1.0 + v.M2.Z - v.M0.X - v.M1.Y) * 2;
		qx = (v.M0.Z + v.M2.X) / S;
	}
	return qx;
}

float Mat44ToQuatY(Mat44 &v)
{
	local float tr = v.M0.X + v.M1.Y + v.M2.Z;
	local float S = 0;
	local float qy = 0;
	if (tr > 0)
	{ 
		S = Sqrt(tr+1.0) * 2;
		qy = (v.M0.Z - v.M2.X) / S; 
	}
	else if ((v.M0.X > v.M1.Y)&&(v.M0.X > v.M2.Z))
	{ 
		S = Sqrt(1.0 + v.M0.X - v.M1.Y - v.M2.Z) * 2;
		qy = (v.M0.Y + v.M1.X) / S; 
	}
	else if (v.M1.Y > v.M2.Z)
	{ 
		S = Sqrt(1.0 + v.M1.Y - v.M0.X - v.M2.Z) * 2;
		qy = 0.25 * S;
	}
	else
	{
		S = Sqrt(1.0 + v.M2.Z - v.M0.X - v.M1.Y) * 2;
		qy = (v.M1.Z + v.M2.Y) / S;
	}
	return qy;
}

float Mat44ToQuatZ(Mat44 &v)
{
	local float tr = v.M0.X + v.M1.Y + v.M2.Z;
	local float S = 0;
	local float qz = 0;
	if (tr > 0)
	{ 
		S = Sqrt(tr+1.0) * 2;
		qz = (v.M1.X - v.M0.Y) / S; 
	}
	else if ((v.M0.X > v.M1.Y)&&(v.M0.X > v.M2.Z))
	{ 
		S = Sqrt(1.0 + v.M0.X - v.M1.Y - v.M2.Z) * 2;
		qz = (v.M0.Z + v.M2.X) / S; 
	}
	else if (v.M1.Y > v.M2.Z)
	{ 
		S = Sqrt(1.0 + v.M1.Y - v.M0.X - v.M2.Z) * 2;
		qz = (v.M1.Z + v.M2.Y) / S; 
	}
	else
	{
		S = Sqrt(1.0 + v.M2.Z - v.M0.X - v.M1.Y) * 2;
		qz = 0.25 * S;
	}
	return qz;
}

float Mat44ToQuatW(Mat44 &v)
{
	local float tr = v.M0.X + v.M1.Y + v.M2.Z;
	local float S = 0;
	local float qw = 0;
	if (tr > 0)
	{ 
		S = Sqrt(tr+1.0) * 2;
		qw = 0.25 * S;
	}
	else if ((v.M0.X > v.M1.Y)&&(v.M0.X > v.M2.Z))
	{ 
		S = Sqrt(1.0 + v.M0.X - v.M1.Y - v.M2.Z) * 2;
		qw = (v.M2.Y - v.M1.Z) / S;
	}
	else if (v.M1.Y > v.M2.Z)
	{ 
		S = Sqrt(1.0 + v.M1.Y - v.M0.X - v.M2.Z) * 2;
		qw = (v.M0.Z - v.M2.X) / S;
	}
	else
	{
		S = Sqrt(1.0 + v.M2.Z - v.M0.X - v.M1.Y) * 2;
		qw = (v.M1.X - v.M0.Y) / S;
	}
	return qw;
}

float Round(float n) //Round float number (hacky way)
{ return (float)(int)(n * 10 + 0.5) / 10.; }

float GetVec3Length(Vec3 &v) //Gets the length of the vector.
{ return Sqrt((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z)); }

int IsVec3Normalized(Vec3 &v) //Returns 1 if vector is normalized, else 0.
{ local float len = GetVec3Length(v); if (len >= 0.99 && len < 1.001) { return 1; } return 0; }

float GetVec4Length(Vec4 &v) //Gets the length of the vector.
{ return Sqrt((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z) + (v.W * v.W)); }

int IsVec4Normalized(Vec4 &v) //Returns 1 if vector is normalized, else 0.
{ local float len = GetVec4Length(v); if (len >= 0.99 && len < 1.001) { return 1; } return 0; }