#include "D3D.h"

CD3DRender::CD3DRender()
{
	m_emaRenderer = new EMARenderer;
}

CD3DRender::~CD3DRender()
= default;

struct vertex
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	float u{};
	float v{};

	enum fvf
	{
		fvf_flags = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

HRESULT CD3DRender::init(HWND hwnd, const int width, const int height)
{
	// Create the D3D object.
	if (nullptr == (g_D3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
	
	g_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;

	// Create the D3DDevice
	if (FAILED(g_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_d3dDevice)))
		return E_FAIL;

	g_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	D3DXMATRIX mat_proj;
	D3DXMatrixPerspectiveFovLH(&mat_proj, D3DXToRadian(45.0f),
		float(width) / float(height), 0.1f, 100.0f);
	g_d3dDevice->SetTransform(D3DTS_PROJECTION, &mat_proj);

	return S_OK;
}

HRESULT CD3DRender::create_buffers(const ushort emg_amount)
{
	g_pIndexBuffer = new LPDIRECT3DINDEXBUFFER9*[emg_amount];
	g_pVertexBuffer = new LPDIRECT3DVERTEXBUFFER9[emg_amount];

	emg_count = emg_amount;
	emg_submodels = new ushort[emg_amount];

	index_count = new ushort*[emg_amount];
	vertex_count = new ushort[emg_amount];
	vertex_size = new ushort[emg_amount];

	dds_id = new byte*[emg_amount];

	return S_OK;
}

// Filling arrays.
HRESULT CD3DRender::load_emg(const ushort current_emg, const ushort emg_submodels, const byte* dds_id, const ushort* index_amount,
                             const ushort vertex_amount, const ushort vertex_size, ushort** indices_array, byte* vertex_array) const
{
	// Filling arrays for using in ProcessFrame().
	CD3DRender::index_count[current_emg] = new ushort[emg_submodels];
	CD3DRender::vertex_count[current_emg] = vertex_amount;
	CD3DRender::vertex_size[current_emg] = vertex_size;
	CD3DRender::emg_submodels[current_emg] = emg_submodels;

	CD3DRender::dds_id[current_emg] = new byte[emg_submodels];

	g_pIndexBuffer[current_emg] = new LPDIRECT3DINDEXBUFFER9[emg_submodels];

	for (ushort i = 0; i < emg_submodels; i++)
	{
		CD3DRender::index_count[current_emg][i] = index_amount[i];
		CD3DRender::dds_id[current_emg][i] = dds_id[i];

		// Create an index buffer to use with our indexed vertex buffer...
		g_d3dDevice->CreateIndexBuffer(index_amount[i] * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIndexBuffer[current_emg][i],
			nullptr);
		WORD *pIndices = nullptr;

		g_pIndexBuffer[current_emg][i]->Lock(0, index_amount[i] * sizeof(WORD), reinterpret_cast<void**>(&pIndices), 0);
		memcpy(pIndices, indices_array[i], index_amount[i] * sizeof(WORD));
		g_pIndexBuffer[current_emg][i]->Unlock();
	}

	// Create a vertex buffer...
	g_d3dDevice->CreateVertexBuffer(vertex_amount * vertex_size,
		D3DUSAGE_WRITEONLY,
		vertex::fvf_flags,
		D3DPOOL_MANAGED,
		&(g_pVertexBuffer[current_emg]),
		nullptr);
	void *pVertices = nullptr;

	g_pVertexBuffer[current_emg]->Lock(0, vertex_amount * vertex_size, static_cast<void**>(&pVertices), 0);
	memcpy(pVertices, vertex_array, vertex_amount * vertex_size);
	g_pVertexBuffer[current_emg]->Unlock();

	return S_OK;
}

HRESULT CD3DRender::load_dds(const ushort dds_amount, unsigned long* dds_size, byte** dds_content)
{
	g_Texture = new LPDIRECT3DTEXTURE9[dds_amount];
	CD3DRender::dds_count = dds_amount;
	for (ushort i = 0; i < dds_amount; i++)
		D3DXCreateTextureFromFileInMemory(g_d3dDevice, dds_content[i], dds_size[i], &g_Texture[i]);

	return S_OK;
}

HRESULT CD3DRender::shutdown() const
{
	for (ushort i = 0; i < emg_count; i++)
	{
		for (ushort a = 0; a < emg_submodels[i]; a++)
		{
			if (g_pIndexBuffer != nullptr)
				g_pIndexBuffer[i][a]->Release();
		}		

		if (g_pVertexBuffer != nullptr)
			g_pVertexBuffer[i]->Release();
	}	

	for (ushort i = 0; i < dds_count; i++)
	{
		if (g_Texture != nullptr)
			g_Texture[i]->Release();
	}	

    if( g_d3dDevice != nullptr )
        g_d3dDevice->Release();

    if( g_D3D != nullptr )
        g_D3D->Release();	

	return S_OK;
}

HRESULT CD3DRender::on_mouse_move(const short x, const short y, const bool r_mousing)
{
	ptCurrentMousePosit.x = x;
	ptCurrentMousePosit.y = y;

	if (bMousing)
	{
		if (bRMousing != r_mousing)
		{
			m_zoom += float(ptCurrentMousePosit.y - ptLastMousePosit.y) / float(1000);
		}
		else
		{
			g_fSpinX -= float(ptCurrentMousePosit.x - ptLastMousePosit.x);
			g_fSpinY -= float(ptCurrentMousePosit.y - ptLastMousePosit.y);
		}		
	}

	ptLastMousePosit.x = ptCurrentMousePosit.x;
	ptLastMousePosit.y = ptCurrentMousePosit.y;

	return S_OK;
}

HRESULT CD3DRender::on_mouse_button_up()
{
	bMousing = false;
	bRMousing = false;

	return S_OK;
}

HRESULT CD3DRender::on_mouse_button_down(const short x, const short y)
{
	ptLastMousePosit.x = ptCurrentMousePosit.x = x;
	ptLastMousePosit.y = ptCurrentMousePosit.y = y;
	bMousing = true;
	bRMousing = false;

	return S_OK;
}

HRESULT CD3DRender::reset()
{
	return S_OK;
}

HRESULT CD3DRender::process_frame() const
{
	// Clear the backbuffer and the zbuffer
	g_d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMATRIX mat_trans;
	D3DXMATRIX mat_rot;
	D3DXMATRIX mat_world;

	D3DXMatrixTranslation(&mat_trans, 0.0f, 0.0f, m_zoom);

	D3DXMatrixRotationYawPitchRoll(	&mat_rot,
									D3DXToRadian(g_fSpinX),
									D3DXToRadian(g_fSpinY),
									0.0f);
	mat_world = mat_rot * mat_trans;
	g_d3dDevice->SetTransform(D3DTS_WORLD, &mat_world);

	// Begin the scene
	if (SUCCEEDED(g_d3dDevice->BeginScene()))
	{
		if (g_pIndexBuffer != nullptr && g_pVertexBuffer != nullptr)
		{
			for (auto i = 0; i < emg_count; i++)
			{
				g_d3dDevice->SetStreamSource(0, g_pVertexBuffer[i], 0, vertex_size[i]);
				g_d3dDevice->SetFVF(vertex::fvf_flags);				
				
				for (ushort a = 0; a < emg_submodels[i]; a++)
				{
					if (g_Texture != nullptr)
					{
						g_d3dDevice->SetTexture(0, g_Texture[dds_id[i][a]]);

						g_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
						g_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
						g_d3dDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 4);

					}

					g_d3dDevice->SetIndices(g_pIndexBuffer[i][a]);
					g_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertex_count[i], 0, index_count[i][a] - 2);		
				}
			}
		}
		// End the scene
		g_d3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

	return S_OK;
}

HRESULT CD3DRender::resize(const int width, const int height)
{
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;

	g_d3dDevice->Reset(&d3dpp);

	g_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX mat_proj;
	D3DXMatrixPerspectiveFovLH(&mat_proj, D3DXToRadian(45.0f),
		float(width) / float(height), 0.1f, 100.0f);
	g_d3dDevice->SetTransform(D3DTS_PROJECTION, &mat_proj);

	return S_OK;
}

