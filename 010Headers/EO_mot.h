//------------------------------------------------
//--- 010 Editor v12.0.1 Header file
//
//      File: Endless Ocean .mot file
//   Authors: NiV
//   Version: 0.2
//   Purpose: 
//  Category: Endless Ocean Modding Experience
// File Mask: 
//  ID Bytes: 
//   History: 
//------------------------------------------------

local byte PrintCorrection = 1;
local byte ZeroIDCounter = 1;

struct MOTHeader_t
{
	char Magic[0x04]<bgcolor=cRed>;
	uint Size<bgcolor=cBlue>;
	float Framerate<bgcolor=cGreen>;
	ushort LenInFrames<bgcolor=cAqua>;
	ushort TRSPoseIdxCount<bgcolor=cAqua>;
	
	ushort TRSPoseValuesCount<bgcolor=cAqua>;
	ushort BonesCount<bgcolor=cAqua>;
	uint TRSPoseIdxOff<bgcolor=0x7f007f>;
	uint TRSPoseValuesOff<bgcolor=0x9f009f>;
	ushort BoneTransCount<bgcolor=cAqua>;
	ushort KeyFramesTransCount<bgcolor=cAqua>;
	
	uint TransBufferOff<bgcolor=0xff00ff>;
	uint TransKeyFramesOff<bgcolor=0x5f005f>;
	ushort BoneRotCount<bgcolor=cAqua>;
	ushort KeyFramesRotCount<bgcolor=cAqua>;
	uint RotBufferOff<bgcolor=0xdf00df>;
	
	uint RotKeyFramesOff<bgcolor=0x3f003f>;
	ushort BoneScaleCount<bgcolor=cAqua>;
	ushort KeyFramesScaleCount<bgcolor=cAqua>;
	uint ScaleBufferOff<bgcolor=0xbf00bf>;
	uint ScaleKeyFramesOff<bgcolor=0x0f000f>;
};

struct OrientationCorrectionIdx_t
{
	local ushort tID = ReadUShort();
	local ushort Tr = tID & 0b00000001;
	local ushort Ro = (tID & 0b00000010) >> 1;
	local ushort Sc = (tID & 0b00000100) >> 2;
	local uint RGBCol = 0;
	if (Tr == 1)
		RGBCol = 0x00ff00;
	if (Ro == 1)
		RGBCol = 0x00ffa0;
	if (Sc == 1)
		RGBCol = 0x00fff0;

	if (tID == 0)
		ushort ID<bgcolor=cBlack, fgcolor=cRed>;
	else if (tID == 3 || tID >= 5)
		ushort ID<bgcolor=cNone, fgcolor=cAqua>;
	else
		ushort ID<bgcolor=cNone, fgcolor=RGBCol>;
	//ushort ID<bgcolor=cBlack, fgcolor=cRed>;
	ushort Trans<bgcolor=cBlack,fgcolor=0x00ff00>;
	ushort Rot<bgcolor=cBlack,fgcolor=0x00ffa0>;
	ushort Scale<bgcolor=cBlack,fgcolor=0x00fff0>;
};

struct Data_t
{
	local int i = 0;
	//TRS Channels
	if (Header.BoneTransCount > 0)
	{
		FSeek(MOTOffLocal + Header.TransBufferOff);
		Vec4 Trans(cNone, 0x00ff00)[Header.BoneTransCount * Header.KeyFramesTransCount]<optimize=true>;
	}
	if (Header.BoneRotCount > 0)
	{
		FSeek(MOTOffLocal + Header.RotBufferOff);
		Vec4 Rot(cNone, 0x00ffa0)[Header.BoneRotCount * Header.KeyFramesRotCount]<optimize=true>;
		//for (i = 0; i < Header.KeyFramesRotCount; i++)
		//{
		//	Printf("%X\t%s\n", i, read_vec4(Rot[i]));
		//}
	}
	if (Header.BoneScaleCount > 0)
	{
		FSeek(MOTOffLocal + Header.ScaleBufferOff);
		Vec4 Scale(cNone, 0x00fff0)[Header.BoneScaleCount * Header.KeyFramesScaleCount]<optimize=true>;
	}

	//Corrections
	if (Header.TRSPoseValuesCount > 0)
	{
		FSeek(MOTOffLocal + Header.TRSPoseValuesOff);
		Vec4 OrientationCorrectionBuffer(cNone, 0x00aff0)[Header.TRSPoseValuesCount]<optimize=true>;
	}
	if (Header.TRSPoseIdxCount > 0)
	{
		FSeek(MOTOffLocal + Header.TRSPoseIdxOff);
		OrientationCorrectionIdx_t OrientationCorrectionIdx[Header.TRSPoseIdxCount]<optimize=false>;
	}

	//TRS Keyframes
	if (Header.BoneTransCount > 0)
	{
		FSeek(MOTOffLocal + Header.TransKeyFramesOff);
		float TransKeyFrameValuesBuffer[Header.KeyFramesTransCount]<fgcolor=0x00ff00, optimize=true>;
	}
	if (Header.BoneRotCount > 0)
	{
		FSeek(MOTOffLocal + Header.RotKeyFramesOff);
		float RotKeyFrameValuesBuffer[Header.KeyFramesRotCount]<fgcolor=0x00ffa0, optimize=true>;
	}
	if (Header.BoneScaleCount > 0)
	{
		FSeek(MOTOffLocal + Header.ScaleKeyFramesOff);
		float ScaleKeyFrameValuesBuffer[Header.KeyFramesScaleCount]<fgcolor=0x00fff0, optimize=true>;
	}

	//Prints
	if (PrintCorrection == 1)
	{
		if (Header.TRSPoseValuesCount > 0)
		{
			Printf("\nOrientationCorrectionBuffer:\n");
			for (i = 0; i < Header.TRSPoseValuesCount; i++)
			{
				//Printf("[%i]\t[%04X]\t", i, i);
				Printf("[%04X]\t", i);
				Printf("Value: %9f, %9f, %9f, %9f\n", OrientationCorrectionBuffer[i].X, OrientationCorrectionBuffer[i].Y, OrientationCorrectionBuffer[i].Z, OrientationCorrectionBuffer[i].W);
			}
		}
        
		if (Header.TRSPoseIdxCount > 0)
		{
			ZeroIDCounter = 0;
			Printf("OrientationCorrectionIdx:\n");
			for (i = 0; i < Header.TRSPoseIdxCount; i++)
			{
				if (OrientationCorrectionIdx[i].ID == 0)
				{
					Printf("\n");
				}
				//Printf("[%i]\t[%04X]\t", i, i);
				//Printf("[%04X]\t[%04i]\t", i, i);
				Printf("[%04X] %04X %04X %04X %04X\t", i, OrientationCorrectionIdx[i].ID, OrientationCorrectionIdx[i].Trans, OrientationCorrectionIdx[i].Rot, OrientationCorrectionIdx[i].Scale);
				switch(OrientationCorrectionIdx[i].ID)
				{
					case 0:
						Printf("%02i", ZeroIDCounter);
						ZeroIDCounter++;
						break;
					case 1:
						Printf("T"); //001
						break;
					case 2:
						Printf("R"); //010
						break;
					case 3:
						Printf("T + R"); //011
						break;
					case 4:
						Printf("S"); //100
						break;
					case 5:
						Printf("T + S"); //101
						break;
					case 6:
						Printf("R + S"); //110
						break;
					case 7:
						Printf("T + R + S"); //111
						break;
				}
				Printf("\n");
			}
		}
	}
};

struct MOT_t(uint &MOTOffLocal)
{
	MOTHeader_t Header[1];
	Data_t Data[1]<optimize=false>;;
};