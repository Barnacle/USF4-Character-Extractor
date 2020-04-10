#pragma once

#include "../D3D/D3D.h"

class CD3DRender;

public ref class wrapper sealed
{
public:
	wrapper();
	~wrapper();

	HRESULT init(int hwnd, int width, int height);
	HRESULT close();
	HRESULT render();
	HRESULT	resize(int width, int height);
	HRESULT	on_mouse_button_up();
	HRESULT	on_mouse_move(short x, short y, bool r_mousing);
	HRESULT	on_mouse_button_down(short x, short y);
	HRESULT create_buffers(ushort emg_count);
	HRESULT	load_emg(ushort current_emg, ushort emg_submodels, unsigned char* dds_id, ushort* index_amount,
					ushort vertex_amount, ushort vertex_size, ushort triangle_strip, ushort** indices_array, unsigned char* vertex_array);
	HRESULT load_dds(ushort dds_count, unsigned long* dds_size, unsigned char** dds_content);
	HRESULT setup_ema(System::String^ ema_file_name, unsigned long ema_block_offset);
	HRESULT update_ema(float(&structure)[500][6], std::string(&names)[500], System::String^ animation_name, int frame);

	static std::string managed_string_to_native(System::String^ str)
	{
		using System::IntPtr;
		using System::Runtime::InteropServices::Marshal;

		auto ip = Marshal::StringToHGlobalAnsi(str);
		std::string out_string = static_cast<const char*>(ip.ToPointer());
		Marshal::FreeHGlobal(ip);
		return out_string;
	}

protected:
	CD3DRender* m_pRenderer;
};

inline wrapper::wrapper()
{
	m_pRenderer = new CD3DRender;
}

inline wrapper::~wrapper()
{
	delete m_pRenderer;
}

inline HRESULT wrapper::init(const int hwnd, const int width, const int height)
{
	return m_pRenderer->init(HWND(hwnd), width, height);
}

inline HRESULT wrapper::close()
{
	return m_pRenderer->shutdown();
}

inline HRESULT wrapper::render()
{
	return m_pRenderer->process_frame();
}

inline HRESULT wrapper::resize(const int width, const int height)
{
	return m_pRenderer->resize(width, height);
}

inline HRESULT wrapper::on_mouse_button_up()
{
	return m_pRenderer->on_mouse_button_up();
}

inline HRESULT wrapper::on_mouse_move(const short x, const short y, const bool r_mousing)
{
	return m_pRenderer->on_mouse_move(x, y, r_mousing);
}

inline HRESULT wrapper::on_mouse_button_down(const short x, const short y)
{
	return m_pRenderer->on_mouse_button_down(x, y);
}

inline HRESULT wrapper::create_buffers(const ushort emg_count)
{
	return m_pRenderer->create_buffers(emg_count);
}

inline HRESULT wrapper::load_emg(const ushort current_emg, const ushort emg_submodels, unsigned char* dds_id, ushort* index_amount, const ushort vertex_amount, const ushort vertex_size, const ushort triangle_strip, ushort** indices_array, unsigned char* vertex_array)
{
	return m_pRenderer->load_emg(current_emg, emg_submodels, dds_id, index_amount, vertex_amount, vertex_size, triangle_strip, indices_array, vertex_array);
}

inline HRESULT wrapper::load_dds(ushort dds_count, unsigned long* dds_size, unsigned char** dds_content)
{
	return m_pRenderer->load_dds(dds_count, dds_size, dds_content);
}

inline HRESULT wrapper::setup_ema(System::String^ ema_file_name, const unsigned long ema_block_offset)
{
	return m_pRenderer->setup(managed_string_to_native(ema_file_name), ema_block_offset);
}

inline HRESULT wrapper::update_ema(float(&structure)[500][6], std::string(&names)[500], System::String^ animation_name, int frame)
{
	const auto AnimationName1 = managed_string_to_native(animation_name);
	return m_pRenderer->update(structure, names, AnimationName1, frame);
}
