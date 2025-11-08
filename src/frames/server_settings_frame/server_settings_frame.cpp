#include "../frames.hpp"
#include "../../main.hpp"
#include <cstdint>
#include <wx/gdicmn.h>
#include <wx/osx/frame.h>

using frames::ServerSettingsFrame;

ServerSettingsFrame::ServerSettingsFrame(const uint16_t server_id, const in_addr_t ip_address) : wxFrame(wxGetApp().GetHomeFrame(), wxID_ANY, "Server Settings", wxDefaultPosition, wxSize(800, 600)), server_id(server_id), ip_address(ip_address) {

}

ServerSettingsFrame::~ServerSettingsFrame() {
    auto const server_settings_frames = wxGetApp().GetServerSettingsFrames();
    for (uint32_t i = 0; i < server_settings_frames->size(); i++) {
        if (server_settings_frames->at(i) == this) {
            server_settings_frames->erase(server_settings_frames->begin() + i);

            break;
        }
    }
}
