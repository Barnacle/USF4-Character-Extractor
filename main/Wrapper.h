#pragma once

#include "..\D3D\D3D.h"

class CD3DRender;

public ref class Wrapper
{
public:
	Wrapper();
	~Wrapper();

	HRESULT WrapInit(int hWnd, int Width, int Height);
	HRESULT WrapClose();
	HRESULT WrapRender();
	HRESULT	WrapResize(int Width, int Height);
	HRESULT	WrapOnMouseButtonUp();
	HRESULT	WrapOnMouseMove(short x, short y, bool RMousing);
	HRESULT	WrapOnMouseButtonDown(short x, short y);
	HRESULT WrapCreateBuffers(ushort EMGcount);
	HRESULT	WrapLoadEMG(ushort CurrentEMG, ushort EMGsubmodels, unsigned char* DDSid, ushort* IndexCount,
		ushort VertexCount, ushort VertexSize,
		ushort** IndiceArray, unsigned char* VertexArray);
	HRESULT WrapLoadDDS(ushort DDScount, unsigned long* DDSsize, unsigned char** DDScontent);

	HRESULT WrapSetup(System::String^ emaFileName, unsigned long emaBlockOffset);
	HRESULT WrapUpdate(float(&structure)[500][6], std::string(&names)[500], System::String^ AnimationName, int frame);

	std::string managedStrToNative(System::String^ sysstr)
	{
		using System::IntPtr;
		using System::Runtime::InteropServices::Marshal;

		IntPtr ip = Marshal::StringToHGlobalAnsi(sysstr);
		std::string outString = static_cast<const char*>(ip.ToPointer());
		Marshal::FreeHGlobal(ip);
		return outString;
	}

protected:
	CD3DRender* m_pRenderer;
};

Wrapper::Wrapper()
{
	m_pRenderer = new CD3DRender;
}

Wrapper::~Wrapper()
{
	delete m_pRenderer;
}

HRESULT Wrapper::WrapInit(int hWnd, int Width, int Height)
{
	return m_pRenderer->init((HWND)hWnd, Width, Height);
}

HRESULT Wrapper::WrapClose()
{
	return m_pRenderer->Shutdown();
}

HRESULT Wrapper::WrapRender()
{
	return m_pRenderer->ProcessFrame();
}

HRESULT Wrapper::WrapResize(int Width, int Height)
{
	return m_pRenderer->Resize(Width, Height);
}

HRESULT Wrapper::WrapOnMouseButtonUp()
{
	return m_pRenderer->OnMouseButtonUp();
}

HRESULT Wrapper::WrapOnMouseMove(short x, short y, bool RMousing)
{
	return m_pRenderer->OnMouseMove(x, y, RMousing);
}

HRESULT Wrapper::WrapOnMouseButtonDown(short x, short y)
{
	return m_pRenderer->OnMouseButtonDown(x, y);
}

HRESULT Wrapper::WrapCreateBuffers(ushort EMGcount)
{
	return m_pRenderer->CreateBuffers(EMGcount);
}

HRESULT Wrapper::WrapLoadEMG(ushort CurrentEMG, ushort EMGsubmodels, unsigned char* DDSid, ushort* IndexCount, ushort VertexSize, ushort VerteSize, ushort** IndiceArray, unsigned char* VertexArray)
{
	return m_pRenderer->LoadEMG(CurrentEMG, EMGsubmodels, DDSid, IndexCount, VertexSize, VerteSize, IndiceArray, VertexArray);
}

HRESULT Wrapper::WrapLoadDDS(ushort DDScount, unsigned long* DDSsize, unsigned char** DDScontent)
{
	return m_pRenderer->LoadDDS(DDScount, DDSsize, DDScontent);
}

HRESULT Wrapper::WrapSetup(System::String^ emaFileName, unsigned long emaBlockOffset)
{
	std::string emaFileName1 = managedStrToNative(emaFileName);
	return m_pRenderer->Setup(emaFileName1, emaBlockOffset);
}

HRESULT Wrapper::WrapUpdate(float(&structure)[500][6], std::string(&names)[500], System::String^ AnimationName, int frame)
{
	std::string AnimationName1 = managedStrToNative(AnimationName);
	return m_pRenderer->Update(structure, names, AnimationName1, frame);
}
