#include "../frames.hpp"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <wx/event.h>
#include <wx/osx/stattext.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include "../../main.hpp"
#include "swift_net.h"

using frames::ServerSettingsFrame;

ServerSettingsFrame::AdminListPanel::AdminListPanel(wxPanel* parent, const uint16_t server_id) : wxPanel(parent), server_id(server_id) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    this->member_list_panel = new wxPanel(this);
    this->member_list_panel->SetSizer(new wxBoxSizer(wxVERTICAL));
    this->member_list_panel->SetMaxSize(wxSize(300, -1));

    this->admin_list_panel = new wxPanel(this);
    this->admin_list_panel->SetSizer(new wxBoxSizer(wxVERTICAL));
    this->admin_list_panel->SetMaxSize(wxSize(300, -1));

    mainSizer->Add(this->member_list_panel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 50);
    mainSizer->Add(this->admin_list_panel, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL, 50);

    this->SetSizer(mainSizer);

    this->RenderMemberList();
    this->RenderAdminList();
}

ServerSettingsFrame::AdminListPanel::~AdminListPanel() {

}

void ServerSettingsFrame::AdminListPanel::RenderAdminList() {
    this->admin_list_panel->DestroyChildren();

    auto list_sizer = this->admin_list_panel->GetSizer();

    auto users = wxGetApp().GetDatabase()->SelectHostedServerUsersByUserType(server_id, objects::Database::UserType::Admin);

    for (auto &user : *users) {
        auto user_panel = new widgets::StyledPanel(this->admin_list_panel);
        user_panel->SetMinSize(wxSize(300, 40));
        user_panel->SetMaxSize(wxSize(300, 40));

        auto username_text = new wxStaticText(user_panel, wxID_ANY, user.username);

        auto make_admin_button = new widgets::Button(user_panel, "Remove Admin", [user, this](wxMouseEvent&){
            this->RemoveUserAdmin((const char*)&user.username);
        });

        make_admin_button->SetMinSize(wxSize(-1, 40));

        auto user_panel_sizer = new wxBoxSizer(wxHORIZONTAL);

        user_panel_sizer->Add(username_text, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        user_panel_sizer->AddStretchSpacer(1);
        user_panel_sizer->Add(make_admin_button, 1, wxALIGN_CENTER_VERTICAL);

        user_panel->SetSizer(user_panel_sizer);

        list_sizer->Add(user_panel, 1);
    }

    Layout();
    Refresh();

    delete users;
}

void ServerSettingsFrame::AdminListPanel::RenderMemberList() {
    this->member_list_panel->DestroyChildren();

    auto list_sizer = this->member_list_panel->GetSizer();

    auto users = wxGetApp().GetDatabase()->SelectHostedServerUsersByUserType(server_id, objects::Database::UserType::Member);

    for (auto &user : *users) {
        auto user_panel = new widgets::StyledPanel(this->member_list_panel);
        user_panel->SetMinSize(wxSize(300, 40));
        user_panel->SetMaxSize(wxSize(300, 40));

        auto username_text = new wxStaticText(user_panel, wxID_ANY, user.username);

        auto make_member_button = new widgets::Button(user_panel, "Give Admin", [user, this](wxMouseEvent&){
            this->MakeUserAdmin((const char*)&user.username);
        });

        make_member_button->SetMinSize(wxSize(-1, 40));

        auto user_panel_sizer = new wxBoxSizer(wxHORIZONTAL);

        user_panel_sizer->Add(username_text, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        user_panel_sizer->AddStretchSpacer(1);
        user_panel_sizer->Add(make_member_button, 1, wxALIGN_CENTER_VERTICAL);

        user_panel->SetSizer(user_panel_sizer);

        list_sizer->Add(user_panel, 1);
    }

    Layout();
    Refresh();

    delete users;
}

void ServerSettingsFrame::AdminListPanel::MakeUserAdmin(const char* username) {
    wxGetApp().GetDatabase()->UpdateUserTypeByUsername(username, this->server_id, objects::Database::UserType::Admin);

    this->RenderMemberList();
    this->RenderAdminList();
}

void ServerSettingsFrame::AdminListPanel::RemoveUserAdmin(const char* username) {
    wxGetApp().GetDatabase()->UpdateUserTypeByUsername(username, this->server_id, objects::Database::UserType::Member);

    this->RenderMemberList();
    this->RenderAdminList();
}
