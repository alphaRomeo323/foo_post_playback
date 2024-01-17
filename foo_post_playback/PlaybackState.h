#pragma once
#include <SDK/play_callback.h>

/// <summary>
/// 
/// </summary>
class PlaybackState :
    public play_callback_static
{
	/// <summary>
	/// Flag of callback
	/// </summary>
	unsigned int m_CallFlag;
	/// <summary>
	/// Title or file name of currently playing
	/// </summary>
	pfc::string8 currentTrackTitle;
	/// <summary>
	/// Artists of currently playing
	/// </summary>
	pfc::string8 currentTrackArtist;
	/// <summary>
	/// Alubum that currently playing track including
	/// </summary>
	pfc::string8 currentTrackAlbum;
	/// <summary>
	/// POST playback status to configured URL.
	/// </summary>
	/// <param name="state">"1": playing, "2": paused, "0": stopped</param>
	void post_playback_state(const char* state);
public:
	PlaybackState(void);
	~PlaybackState(void);
	void on_playback_starting(play_control::t_track_command p_command, bool p_paused) override;
	void on_playback_new_track(metadb_handle_ptr p_track) override;
	void on_playback_stop(play_control::t_stop_reason p_reason) override;
	void on_playback_seek(double p_time) override;
	void on_playback_pause(bool p_state) override;
	void on_playback_edited(metadb_handle_ptr p_track) override;
	void on_playback_dynamic_info(const file_info& p_info) override;
	void on_playback_dynamic_info_track(const file_info& p_info) override;
	void on_playback_time(double p_time) override;
	void on_volume_change(float p_new_val) override;
	unsigned int get_flags(void) override;

};

