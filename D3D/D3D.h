#pragma once

#ifdef _EXPORTING
#define CLASS_DECLSPEC    __declspec(dllexport)
#else
#define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#include <windows.h>
#include <d3dx9.h>
#include "Ema.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9d.lib" )
#pragma comment( lib, "winmm.lib" )

typedef unsigned short ushort;
typedef unsigned char Byte;

class CLASS_DECLSPEC CD3DRender
{	
public:
	CD3DRender();
	~CD3DRender();

	LPDIRECT3D9					g_D3D = NULL; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9			g_d3dDevice = NULL; // Our rendering device

	LPDIRECT3DINDEXBUFFER9**	g_pIndexBuffer = NULL; // Буфер индексов
	LPDIRECT3DVERTEXBUFFER9*	g_pVertexBuffer = NULL; // Буфер вертексов
	LPDIRECT3DTEXTURE9*			g_Texture = NULL;

	D3DDISPLAYMODE				d3ddm;
	D3DPRESENT_PARAMETERS		d3dpp;

	POINT ptLastMousePosit;
	POINT ptCurrentMousePosit;
	
	bool bMousing = false;
	float g_fSpinX = 0.0f;
	float g_fSpinY = 0.0f;

	bool bRMousing = false;
	float m_zoom = 2.5f;

	unsigned short	EMGcount;
	unsigned short* EMGsubmodels = NULL;
	unsigned short**IndexCount = NULL;
	unsigned short* VertexCount = NULL;
	unsigned short* VertexSize = NULL;

	ushort	DDScount;
	Byte**	DDSid = NULL;

	HRESULT init(HWND hwnd, int Width, int Height);
	HRESULT CreateBuffers(ushort EMGcount);
	HRESULT LoadEMG(ushort CurrentEMG, ushort EMGsubmodels, Byte* DDSid, ushort* IndexCount,
		ushort VertexCount, ushort VertexSize,
		ushort** IndiceArray, Byte* VertexArray);
	HRESULT LoadDDS(ushort DDScount, unsigned long* DDSsize, Byte** DDScontent);
	HRESULT Shutdown();
	HRESULT Reset();
	HRESULT ProcessFrame();
	HRESULT Resize(int Width, int Height);
	HRESULT OnMouseMove(short x, short y, bool RMousing);
	HRESULT OnMouseButtonUp();
	HRESULT OnMouseButtonDown(short x, short y);

	EMARenderer* m_emaRenderer;
	HRESULT Setup(std::string emaFileName, unsigned long emaBlockOffset)
	{
		m_emaRenderer->setup(emaFileName, emaBlockOffset);

		return S_OK;
	}

	HRESULT Update(float(&structure)[500][6], std::string(&names)[500], std::string AnimationName, int frame)
	{
		m_emaRenderer->updateDeviceObjects(AnimationName, (float)frame, structure, names);

		return S_OK;
	}
};