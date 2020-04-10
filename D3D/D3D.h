#pragma once

#ifdef _EXPORTING
#define CLASS_DECLSPEC    __declspec(dllexport)  // NOLINT(cppcoreguidelines-macro-usage)
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

	unsigned short	emg_count{};
	unsigned short* emg_submodels = nullptr;
	unsigned short**index_count = nullptr;
	unsigned short* vertex_count = nullptr;
	unsigned short* vertex_size = nullptr;
	unsigned short* triangle_strip = nullptr;

	ushort	dds_count{};
	byte**	dds_id = nullptr;

	HRESULT init(HWND hwnd, int width, int height);
	HRESULT create_buffers(ushort emg_amount);
	HRESULT load_emg(ushort current_emg, ushort emg_submodels, const byte* dds_id, const ushort* index_amount,
					ushort vertex_amount, ushort vertex_size, ushort triangle_strip, ushort** indices_array, byte* vertex_array) const;
	HRESULT load_dds(ushort dds_amount, unsigned long* dds_size, byte** dds_content);
	HRESULT shutdown() const;
	static HRESULT reset();
	HRESULT process_frame() const;
	HRESULT resize(int width, int height);
	HRESULT on_mouse_move(short x, short y, bool r_mousing);
	HRESULT on_mouse_button_up();
	HRESULT on_mouse_button_down(short x, short y);

	EMARenderer* m_emaRenderer;
	HRESULT setup(const std::string& ema_file_name, const unsigned long ema_block_offset) const
	{
		m_emaRenderer->setup(ema_file_name, ema_block_offset);

		return S_OK;
	}

	HRESULT update(float(&structure)[500][6], std::string(&names)[500], const std::string& animation_name, const int frame) const
	{
		m_emaRenderer->updateDeviceObjects(animation_name, float(frame), structure, names);

		return S_OK;
	}
};