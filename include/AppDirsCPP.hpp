// SPDX-FileCopyrightText: 2010 ActiveState Software Inc.
// SPDX-FileCopyrightText: 2022 AppDirsCPP contributors
// SPDX-License-Identifier: MIT

#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <vector>

#ifdef _WIN32
#define _CXTSTR std::wstring
#else
#define _CXTSTR std::string
#endif

/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical user data directories are :
/// Mac OS X:              ~/Library/Application Support/<AppName>
/// Unix:                  ~/.local/share/<AppName>    # or in $XDG_DATA_HOME, if defined
/// Win XP (not roaming):  C:\Documents and Settings\<username>\Local Settings\Application Data\<AppAuthor>\<AppName>
/// Win XP (roaming):      C:\Documents and Settings\<username>\Application Data\<AppAuthor>\<AppName>
/// Win 7  (not roaming):  C:\Users\<username>\AppData\Local\<AppAuthor>\<AppName>
/// Win 7  (roaming):      C:\Users\<username>\AppData\Roaming\<AppAuthor>\<AppName>
///
/// For Unix, we follow the XDG spec and support $XDG_DATA_HOME.
/// That means, by default "~/.local/share/<AppName>".
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// </param>
/// <param name="roaming"> can be set true to use the Windows
/// <para/>&#160;&#160;&#160;&#160;roaming appdata directory.That means that for users on a Windows
/// <para/>&#160;&#160;&#160;&#160;network setup for roaming profiles, this user data will be
/// <para/>&#160;&#160;&#160;&#160;sync'd on login. See
/// <para/>&#160;&#160;&#160;&#160;http://technet.microsoft.com/en-us/library/cc766489(WS.10).aspx
/// <para/>&#160;&#160;&#160;&#160;for a discussion of issues.
/// </param>
/// <param name="error">: If returned path is NULL, check here for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-specific data dir for this application. Use free() to deallocate full path memory.</returns>
_CXTSTR user_data_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool roaming,
    int* error);


/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical site data directories are:
///   Mac OS X:   /Library/Application Support/<AppName>
///   Unix:       /usr/local/share/<AppName> or /usr/share/<AppName>
///   Win XP:     C:\Documents and Settings\All Users\Application Data\<AppAuthor>\<AppName>
///   Vista:      (Fail! "C:\ProgramData" is a hidden *system* directory on Vista.)
///   Win 7:      C:\ProgramData\<AppAuthor>\<AppName>   # Hidden, but writeable on Win 7.
///
///   For Unix, this is using the $XDG_DATA_DIRS[0] default.
///
///   WARNING: Do not use this on Windows. See the Vista-Fail note above for why.
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// <para/>&#160;&#160;&#160;&#160;Only applied when appname is present.
/// </param>
/// <param name="multipath"> is an optional parameter only applicable to *nix
/// <para/>&#160;&#160;&#160;&#160;which indicates that the entire list of data dirs should be
/// <para/>&#160;&#160;&#160;&#160;returned. By default, the first item from XDG_DATA_DIRS is
/// <para/>&#160;&#160;&#160;&#160;returned, or '/usr/local/share/&lt;AppName&gt;',
/// <para/>&#160;&#160;&#160;&#160;if XDG_DATA_DIRS is not set
/// </param>
/// <param name="error">: If returned path is NULL, check value for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-shared data dir for this application. Use free() to deallocate full path memory.</returns>
std::vector<_CXTSTR> site_data_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool multipath,
    int* error);


/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical user config directories are:
///   Mac OS X:               ~/Library/Preferences/<AppName>
///   Unix:                   ~/.config/<AppName>     # or in $XDG_CONFIG_HOME, if defined
///   Win *:                  same as user_data_dir
///
/// For Unix, we follow the XDG spec and support $XDG_CONFIG_HOME.
/// That means, by default "~/.config/<AppName>".
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// </param>
/// <param name="roaming"> can be set true to use the Windows
/// <para/>&#160;&#160;&#160;&#160;roaming appdata directory.That means that for users on a Windows
/// <para/>&#160;&#160;&#160;&#160;network setup for roaming profiles, this user data will be
/// <para/>&#160;&#160;&#160;&#160;sync'd on login. See
/// <para/>&#160;&#160;&#160;&#160;http://technet.microsoft.com/en-us/library/cc766489(WS.10).aspx
/// <para/>&#160;&#160;&#160;&#160;for a discussion of issues.
/// </param>
/// <param name="error">: If returned path is NULL, check here for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-specific config dir for this application. Use free() to deallocate full path memory.</returns>
_CXTSTR user_config_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool roaming,
    int* error);


/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical site data directories are:
///   Mac OS X:   same as site_data_dir
///   Unix:       /etc/xdg/<AppName> or $XDG_CONFIG_DIRS[i]/<AppName> for each value in
///               $XDG_CONFIG_DIRS
///   Win *:      same as site_data_dir
///   Vista:      (Fail! "C:\ProgramData" is a hidden *system* directory on Vista.)
///
///   For Unix, this is using the $XDG_CONFIG_DIRS[0] default, if multipath=false
///
///   WARNING: Do not use this on Windows. See the Vista-Fail note above for why.
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// <para/>&#160;&#160;&#160;&#160;Only applied when appname is present.
/// </param>
/// <param name="multipath"> is an optional parameter only applicable to *nix
/// <para/>&#160;&#160;&#160;&#160;which indicates that the entire list of data dirs should be
/// <para/>&#160;&#160;&#160;&#160;returned. By default, the first item from XDG_CONFIG_DIRS is
/// <para/>&#160;&#160;&#160;&#160;returned, or '/etc/xdg/&lt;AppName&gt;',
/// <para/>&#160;&#160;&#160;&#160;if XDG_CONFIG_DIRS is not set
/// </param>
/// <param name="error">: If returned path is NULL, check value for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-shared data dir for this application. Use free() to deallocate full path memory.</returns>
std::vector<_CXTSTR> site_config_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool multipath,
    int* error);


/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical user cache directories are:
///   Mac OS X:   ~/Library/Caches/<AppName>
///   Unix:       ~/.cache/<AppName> (XDG default)
///   Win XP:     C:\Documents and Settings\<username>\Local Settings\Application Data\<AppAuthor>\<AppName>\Cache
///   Vista:      C:\Users\<username>\AppData\Local\<AppAuthor>\<AppName>\Cache
///
/// On Windows the only suggestion in the MSDN docs is that local settings go in
/// the `CSIDL_LOCAL_APPDATA` directory. This is identical to the non-roaming
/// app data dir (the default returned by `user_data_dir` above). Apps typically
/// put cache data somewhere *under* the given dir here. Some examples:
///     ...\Mozilla\Firefox\Profiles\<ProfileName>\Cache
///     ...\Acme\SuperApp\Cache\1.0
/// OPINION: This function appends "Cache" to the `CSIDL_LOCAL_APPDATA` value.
/// This can be disabled with the `opinion=false` option.
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// <para/>&#160;&#160;&#160;&#160;Only applied when appname is present.
/// </param>
/// <param name="opinion"> can be false to disable the appending of
/// <para/>&#160;&#160;&#160;&#160;"Cache" to the base app data dir for Windows. See
/// <para/>&#160;&#160;&#160;&#160;discussion below.
/// </param>
/// <param name="error">: If returned path is NULL, check value for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-specific cache dir for this application. Use free() to deallocate full path memory.</returns>
_CXTSTR user_cache_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool opinion,
    int* error);


/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical user cache directories are:
///   Mac OS X:  same as user_data_dir
///   Unix:      ~/.local/state/<AppName>   # or in $XDG_STATE_HOME, if defined
///   Win *:     same as user_data_dir
///
/// For Unix, we follow this Debian proposal <https://wiki.debian.org/XDGBaseDirectorySpecification#state>
/// to extend the XDG spec and support $XDG_STATE_HOME.
///
/// That means, by default "~/.local/state/<AppName>".
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// <para/>&#160;&#160;&#160;&#160;Only applied when appname is present.
/// </param>
/// <param name="roaming"> can be set true to use the Windows
/// <para/>&#160;&#160;&#160;&#160;roaming appdata directory.That means that for users on a Windows
/// <para/>&#160;&#160;&#160;&#160;network setup for roaming profiles, this user data will be
/// <para/>&#160;&#160;&#160;&#160;sync'd on login. See
/// <para/>&#160;&#160;&#160;&#160;http://technet.microsoft.com/en-us/library/cc766489(WS.10).aspx
/// <para/>&#160;&#160;&#160;&#160;for a discussion of issues.
/// </param>
/// <param name="error">: If returned path is NULL, check value for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-specific state dir for this application. Use free() to deallocate full path memory.</returns>
_CXTSTR user_state_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool roaming,
    int* error);


/// <summary>
/// See header file for human readable chart.
/// <![CDATA[
/// Typical user cache directories are:
///   Mac OS X:  ~/Library/Logs/<AppName>
///   Unix:      ~/.cache/<AppName>/log  # or under $XDG_CACHE_HOME if defined
///   Win XP:    C:\Documents and Settings\<username>\Local Settings\Application Data\<AppAuthor>\<AppName>\Logs
///   Vista:     C:\Users\<username>\AppData\Local\<AppAuthor>\<AppName>\Logs
///
/// On Windows the only suggestion in the MSDN docs is that local settings
/// go in the `CSIDL_LOCAL_APPDATA` directory. (Note: I'm interested in
/// examples of what some windows apps use for a logs dir.)
///
/// OPINION: This function appends "Logs" to the `CSIDL_LOCAL_APPDATA`
/// value for Windows and appends "log" to the user cache dir for Unix.
/// This can be disabled with the `opinion=false` option.
/// ]]>
/// </summary>
/// <param name="appname"> is the name of the application.<br/>
/// <para/>&#160;&#160;&#160;&#160;If NULL, just the system directory is returned.
/// </param>
/// <param name="appauthor"> (only used on Windows) is the name of the
/// <para/>&#160;&#160;&#160;&#160;appauthor or distributing body for this application.Typically
/// <para/>&#160;&#160;&#160;&#160;it is the owning company name.This falls back to appname.You may
/// <para/>&#160;&#160;&#160;&#160;pass false to disable it.
/// </param>
/// <param name="version"> is an optional version path element to append to the
/// <para/>&#160;&#160;&#160;&#160;path.You might want to use this if you want multiple versions
/// <para/>&#160;&#160;&#160;&#160;of your app to be able to run independently.If used, this
/// <para/>&#160;&#160;&#160;&#160;would typically be "&lt;major&gt;.&lt;minor&gt;".
/// <para/>&#160;&#160;&#160;&#160;Only applied when appname is present.
/// </param>
/// <param name="opinion"> can be false to disable the appending of
/// <para/>&#160;&#160;&#160;&#160;"Logs" to the base app data dir for Windows, and "log" to the
/// <para/>&#160;&#160;&#160;&#160;base cache dir for Unix. See discussion below.
/// </param>
/// <param name="error">: If returned path is NULL, check value for any faults. Assumed using errno method.
/// </param>
/// <returns>Return full path to the user-specific log dir for this application.  Use free() to deallocate full path memory.</returns>
_CXTSTR user_log_dir(
    const _CXTSTR* appname,
    const _CXTSTR* appauthor,
    const _CXTSTR* version,
    const bool opinion,
    int* error);
