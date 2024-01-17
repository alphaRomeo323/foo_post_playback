#include "stdafx.h"
#include "PlaybackState.h"
#include "Configuration.h"

#include <future>

PlaybackState::PlaybackState(void)
{
    m_CallFlag = flag_on_playback_new_track 
        + flag_on_playback_pause 
        + flag_on_playback_stop 
        + flag_on_playback_time;
}


PlaybackState::~PlaybackState(void)
{
}

void PlaybackState::on_playback_starting(play_control::t_track_command p_command, bool p_paused) 
{

}

void PlaybackState::on_playback_new_track(metadb_handle_ptr p_track)
{
    service_ptr_t<titleformat_object> format;
    static_api_ptr_t<titleformat_compiler>()->compile_safe(format, "$if2(%title%,%_filename%)");
    p_track->format_title(NULL, currentTrackTitle, format, NULL);
    static_api_ptr_t<titleformat_compiler>()->compile_safe(format, "$if2(%artist%,unknown artist)");
    p_track->format_title(NULL, currentTrackArtist, format, NULL);
    static_api_ptr_t<titleformat_compiler>()->compile_safe(format, "$if2(%album%,)");
    p_track->format_title(NULL, currentTrackAlbum, format, NULL);
    post_playback_state("1");
    std::thread t(&PlaybackState::post_playback_state, this, "1");
    t.detach();
}

void PlaybackState::on_playback_stop(play_control::t_stop_reason p_reason)
{
    if (p_reason == playback_control::stop_reason_starting_another) {
        return;
    }
    currentTrackTitle = "";
    currentTrackArtist = "";
    currentTrackAlbum = "";
    std::thread t(&PlaybackState::post_playback_state, this, "0");
    t.detach();
}

void PlaybackState::on_playback_seek(double p_time)
{
}

void PlaybackState::on_playback_pause(bool p_state)
{
    if (p_state) {
        //pause
        std::thread t(&PlaybackState::post_playback_state, this, "2");
        t.detach();
    }
    else {
        //replay
        std::thread t(&PlaybackState::post_playback_state, this, "1");
        t.detach();
    }
}

void PlaybackState::on_playback_edited(metadb_handle_ptr p_track)
{
}

void PlaybackState::on_playback_dynamic_info(const file_info& p_info)
{
}

void PlaybackState::on_playback_dynamic_info_track(const file_info& p_info)
{
}

void PlaybackState::on_playback_time(double p_time)
{
    if ((long)p_time % 300 == 0) {
        std::thread t(&PlaybackState::post_playback_state, this, "1");
        t.detach();
    }
}

void PlaybackState::on_volume_change(float p_new_val)
{
}

unsigned int PlaybackState::get_flags(void)
{
    return m_CallFlag;
}

void PlaybackState::post_playback_state(const char* state)
{
    pfc::string8 url;
    cfg_url.get(url);
    if (url == "") {
        return;
    }
    static_api_ptr_t<http_client> client;
    auto r = client->create_request("POST");
    service_ptr_t<http_request_post> post_req;
    if (r->service_query_t(post_req)) {
        abort_callback_dummy cb;
        //POST DATA
        post_req->add_post_data("state", state); 
        post_req->add_post_data("title", currentTrackTitle);
        post_req->add_post_data("artist", currentTrackArtist);
        post_req->add_post_data("album", currentTrackAlbum);
        try { //POST
            auto f = post_req->run(url, cb);
            pfc::array_t<char> arr;
            f->read_till_eof(arr, cb);//??
        }
        catch (std::exception e) { //http error handle
            console::error(e.what());
        }
    }
}

play_callback_static_factory_t<PlaybackState> g_foo;