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
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "winmm.lib" )

typedef unsigned short ushort;

class CLASS_DECLSPEC CD3DRender
{	
public:
	CD3DRender();
	~CD3DRender();

	LPDIRECT3D9					g_D3D = nullptr; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9			g_d3dDevice = nullptr; // Our rendering device

	LPDIRECT3DINDEXBUFFER9**	g_pIndexBuffer = nullptr; // Index buffer
	LPDIRECT3DVERTEXBUFFER9*	g_pVertexBuffer = nullptr; // Vertex buffer
	LPDIRECT3DTEXTURE9*			g_Texture = nullptr;

	D3DDISPLAYMODE				d3ddm{};
	D3DPRESENT_PARAMETERS		d3dpp{};

	POINT ptLastMousePosit{};
	POINT ptCurrentMousePosit{};
	
	bool bMousing = false;
	float g_fSpinX = 0.0f;
	float g_fSpinY = 0.0f;

	bool bRMousing = false;
	float m_zoom = 2.5f;

	unsigned short	EMGcount{};
	unsigned short* EMGsubmodels = nullptr;
	unsigned short**IndexCount = nullptr;
	unsigned short* VertexCount = nullptr;
	unsigned short* VertexSize = nullptr;

	ushort	DDScount{};
	byte**	DDSid = nullptr;

	HRESULT init(HWND hwnd, int width, int height);
	HRESULT CreateBuffers(ushort EMGcount);
	HRESULT LoadEMG(ushort CurrentEMG, ushort EMGsubmodels, byte* DDSid, ushort* index_count,
		ushort VertexCount, ushort VertexSize,
		ushort** IndiceArray, byte* VertexArray);
	HRESULT LoadDDS(ushort DDScount, unsigned long* DDSsize, byte** DDScontent);
	HRESULT Shutdown();
	HRESULT Reset();
	HRESULT ProcessFrame();
	HRESULT Resize(int width, int height);
	HRESULT OnMouseMove(short x, short y, bool RMousing);
	HRESULT OnMouseButtonUp();
	HRESULT OnMouseButtonDown(short x, short y);

	EMARenderer* m_emaRenderer;
	HRESULT Setup(const std::string& emaFileName, const unsigned long emaBlockOffset)
	{
		m_emaRenderer->setup(emaFileName, emaBlockOffset);

		return S_OK;
	}

	HRESULT Update(float(&structure)[500][6], std::string(&names)[500], const std::string& animation_name, const int frame)
	{
		m_emaRenderer->updateDeviceObjects(animation_name, float(frame), structure, names);

		return S_OK;
	}
};