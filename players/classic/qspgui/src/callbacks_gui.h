// Copyright (C) 2001-2020 Valeriy Argunov (byte AT qsp DOT org)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef CALLBACKS_GUI_H
    #define CALLBACKS_GUI_H

    #include <map>
    #include <qsp_default.h>
    #include "frame.h"
    #include "msgdlg.h"
    #include "inputdlg.h"
    #include "fmod.h"

    typedef struct QSPSound_
    {
        FMOD_CHANNEL *Channel;
        FMOD_SOUND *Sound;
        int Volume;

        void Free() const
        {
            FMOD_Sound_Release(Sound);
        }
    } QSPSound;

    typedef std::map<wxString, QSPSound> QSPSounds;
    typedef std::map<wxString, wxString> QSPVersionInfoValues;

    static QSPString qspStringFromPair(const QSP_CHAR *start, const QSP_CHAR *end)
    {
        QSPString string;
        string.Str = (QSP_CHAR *)start;
        string.End = (QSP_CHAR *)end;
        return string;
    }

    static QSPString qspStringFromLen(const QSP_CHAR *s, int len)
    {
        QSPString string;
        string.Str = (QSP_CHAR *)s;
        string.End = (QSP_CHAR *)s + len;
        return string;
    }

    static bool qspIsEmpty(QSPString s)
    {
        return (s.Str == s.End);
    }

    static wxString qspToWxString(QSPString s)
    {
        return wxString(s.Str, s.End);
    }

    /* Helpers */
    #define QSP_STATIC_LEN(x) (sizeof(x) / sizeof(QSP_CHAR) - 1)
    #define QSP_STATIC_STR(x) (qspStringFromLen(x, QSP_STATIC_LEN(x)))

    class QSPCallBacks
    {
    public:
        // Methods
        static void Init(QSPFrame *frame);
        static void DeInit();
        static void SetOverallVolume(float coeff);

        // CallBacks
        static void RefreshInt(QSP_BOOL isForced);
        static void SetTimer(int msecs);
        static void SetInputStrText(QSPString text);
        static QSP_BOOL IsPlay(QSPString file);
        static void CloseFile(QSPString file);
        static void PlayFile(QSPString file, int volume);
        static void ShowPane(int type, QSP_BOOL toShow);
        static void Sleep(int msecs);
        static int GetMSCount();
        static void Msg(QSPString str);
        static int ShowMenu(QSPListItem *items, int count);
        static void Input(QSPString text, QSP_CHAR *buffer, int maxLen);
        static void ShowImage(QSPString file);
        static void OpenGame(QSPString file, QSP_BOOL isNewGame);
        static void OpenGameStatus(QSPString file);
        static void SaveGameStatus(QSPString file);
        static void Version(QSPString param, QSP_CHAR *buffer, int maxLen);
    private:
        // Internal methods
        static bool SetVolume(QSPString file, int volume);
        static void UpdateSounds();

        // Fields
        static QSPFrame *m_frame;
        static bool m_isHtml;
        static FMOD_SYSTEM *m_sys;
        static QSPSounds m_sounds;
        static float m_volumeCoeff;
        static QSPVersionInfoValues m_versionInfo;

        static const int MAX_LIST_ITEMS = 1000;
    };

#endif
