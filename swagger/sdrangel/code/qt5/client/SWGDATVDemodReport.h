/**
 * SDRangel
 * This is the web REST/JSON API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ (4.3+ in Windows) GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube    ---   Limitations and specifcities:    * In SDRangel GUI the first Rx device set cannot be deleted. Conversely the server starts with no device sets and its number of device sets can be reduced to zero by as many calls as necessary to /sdrangel/deviceset with DELETE method.   * Preset import and export from/to file is a server only feature.   * Device set focus is a GUI only feature.   * The following channels are not implemented (status 501 is returned): ATV and DATV demodulators, Channel Analyzer NG, LoRa demodulator   * The device settings and report structures contains only the sub-structure corresponding to the device type. The DeviceSettings and DeviceReport structures documented here shows all of them but only one will be or should be present at a time   * The channel settings and report structures contains only the sub-structure corresponding to the channel type. The ChannelSettings and ChannelReport structures documented here shows all of them but only one will be or should be present at a time    --- 
 *
 * OpenAPI spec version: 6.0.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * SWGDATVDemodReport.h
 *
 * DATVDemod
 */

#ifndef SWGDATVDemodReport_H_
#define SWGDATVDemodReport_H_

#include <QJsonObject>



#include "SWGObject.h"
#include "export.h"

namespace SWGSDRangel {

class SWG_API SWGDATVDemodReport: public SWGObject {
public:
    SWGDATVDemodReport();
    SWGDATVDemodReport(QString* json);
    virtual ~SWGDATVDemodReport();
    void init();
    void cleanup();

    virtual QString asJson () override;
    virtual QJsonObject* asJsonObject() override;
    virtual void fromJsonObject(QJsonObject &json) override;
    virtual SWGDATVDemodReport* fromJson(QString &jsonString) override;

    float getChannelPowerDb();
    void setChannelPowerDb(float channel_power_db);

    qint32 getAudioActive();
    void setAudioActive(qint32 audio_active);

    qint32 getAudioDecodeOk();
    void setAudioDecodeOk(qint32 audio_decode_ok);

    qint32 getVideoActive();
    void setVideoActive(qint32 video_active);

    qint32 getVideoDecodeOk();
    void setVideoDecodeOk(qint32 video_decode_ok);

    qint32 getUdpRunning();
    void setUdpRunning(qint32 udp_running);

    qint32 getModcodModulation();
    void setModcodModulation(qint32 modcod_modulation);

    qint32 getModcodCodeRate();
    void setModcodCodeRate(qint32 modcod_code_rate);

    qint32 getSetByModcod();
    void setSetByModcod(qint32 set_by_modcod);

    float getMer();
    void setMer(float mer);

    float getCnr();
    void setCnr(float cnr);


    virtual bool isSet() override;

private:
    float channel_power_db;
    bool m_channel_power_db_isSet;

    qint32 audio_active;
    bool m_audio_active_isSet;

    qint32 audio_decode_ok;
    bool m_audio_decode_ok_isSet;

    qint32 video_active;
    bool m_video_active_isSet;

    qint32 video_decode_ok;
    bool m_video_decode_ok_isSet;

    qint32 udp_running;
    bool m_udp_running_isSet;

    qint32 modcod_modulation;
    bool m_modcod_modulation_isSet;

    qint32 modcod_code_rate;
    bool m_modcod_code_rate_isSet;

    qint32 set_by_modcod;
    bool m_set_by_modcod_isSet;

    float mer;
    bool m_mer_isSet;

    float cnr;
    bool m_cnr_isSet;

};

}

#endif /* SWGDATVDemodReport_H_ */