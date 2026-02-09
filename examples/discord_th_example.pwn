#include <a_samp>
#include <discord-connector>

// ถ้าไฟล์นี้ถูกเซฟเป็น Windows-874 (ไทย) ให้ตั้งค่าใน server.cfg:
// discord_pawn_encoding windows-874

// เปลี่ยนเป็นชื่อห้องของคุณ (แนะนำให้เป็นตัวอักษรอังกฤษ)
#define DISCORD_CHANNEL_NAME "server-log"

new DCC_Channel:g_LogChannel = DCC_INVALID_CHANNEL;

public OnGameModeInit()
{
    print("[DCC] Thai example loaded");
    return 1;
}

public DCC_OnGuildCreate(DCC_Guild:guild)
{
    g_LogChannel = DCC_FindChannelByName(DISCORD_CHANNEL_NAME);
    if (g_LogChannel != DCC_INVALID_CHANNEL)
    {
        DCC_SendChannelMessage(g_LogChannel, "สวัสดีครับ เซิร์ฟเวอร์ออนไลน์แล้ว");
    }
    return 1;
}

public DCC_OnMessageCreate(DCC_Message:message)
{
    new content[256];
    new DCC_Channel:channel;

    DCC_GetMessageContent(message, content, sizeof content);
    DCC_GetMessageChannel(message, channel);

    if (!strcmp(content, "!ping", true))
    {
        DCC_SendChannelMessage(channel, "pong (ตอบกลับภาษาไทยได้)");
    }
    return 1;
}

