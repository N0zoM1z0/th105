#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <string.h>

namespace th105 {

struct PacketResultBase4 {
    PacketResultBase4() : result_004() {}
    unsigned int result_004;
};

struct ShortDeque20CallView {
    unsigned int allocator_state_00;
    void *map_04;
    unsigned int map_size_08;
    unsigned int offset_0c;
    unsigned int size_10;

    short &at(unsigned int index);
};

class PacketSerializeView {
public:
    virtual unsigned int serialize(void *buffer);
};

class InputPacket24 : public PacketResultBase4 {
public:
    InputPacket24() {}
    virtual unsigned int serialize(void *buffer);

    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

class ReplayPacket28 : public PacketResultBase4 {
public:
    ReplayPacket28() {}
    virtual unsigned int serialize(void *buffer);
    void parse_compressed(const unsigned char *input);

    unsigned int sequence_008;
    unsigned int metadata_00c;
    unsigned char tag_010;
    unsigned char reserved_011[3];
    std::deque<short> values_014;
};

struct ReplayPacketDequeOwner28 {
    unsigned char reserved_000[0x14];
    std::deque<short> values_014;

    ~ReplayPacketDequeOwner28();
};

class RequestReplayPacket10 : public PacketResultBase4 {
public:
    virtual unsigned int serialize(void *buffer);
    void parse(const unsigned char *input);

    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
};

class NetworkClientSend4View {
public:
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *sent_size);
};

class NetworkInputSinkView {
public:
    void flush_to(void *destination);
    void reset_locked_44d700();
    void append_replay_value_42b270(unsigned short value);
    void build_replay_filename_42a560(
        char *output,
        const char *player0_name,
        const char *player1_name);
    void save_replay_428d90(const char *path);
};

struct ConnectConfigIniView {
    bool has_file_40f0b0(const char *path);
    unsigned int read_uint_40f100(const char *section, const char *key);
};

extern ConnectConfigIniView g_connect_config_ini;
extern "C" const char connect_config_file[];
extern "C" const char connect_config_section[];
extern "C" const char network_save_replay_key[];

class NetworkClientPacketOwnerView {
public:
    virtual ~NetworkClientPacketOwnerView();
    int send_simple_packet(PacketSerializeView *packet, int option);
    void pump_replay_request_44d880();
    void flush_replay_values_44d800();
    void save_replay_if_enabled_44e2c0();

    char player0_name_004[0x20];
    char player1_name_024[0x20];
    unsigned char reserved_044[0x98];
    CriticalSectionWrapper replay_critical_0dc;
    unsigned char reserved_0f8[0x2bc];
    NetworkClientSend4View sender_3b4;
    unsigned char reserved_3b5[0x200 - sizeof(NetworkClientSend4View)];
    unsigned char packet_buffer_5b4[0x100];
    NetworkInputSinkView *input_sink_6b4;
    unsigned char expected_tag_6b8;
    unsigned char reserved_6b9[3];
    unsigned int replay_sequence_6bc;
    unsigned int replay_metadata_6c0;
    unsigned char reserved_6c4[4];
    std::deque<short> replay_values_6c8;
};

class ConnectSessionRuntimeView {
public:
    void apply_profile_44d7d0(const char *profile, unsigned char side);

    unsigned char reserved_000[4];
    char profile_004[0x20];
    unsigned char reserved_024[0x384];
    unsigned char side_3a8;
};

class NetworkReplayBufferView {
public:
    void reset_428b70();
};

class ScopedNetworkCriticalSection {
public:
    explicit ScopedNetworkCriticalSection(CriticalSectionWrapper *lock)
        : lock_(lock)
    {
        lock_->enter();
    }

    ~ScopedNetworkCriticalSection()
    {
        lock_->leave();
    }

private:
    CriticalSectionWrapper *lock_;
};

class NetworkReplayStateView {
public:
    void reset_locked_44d700();

    unsigned char reserved_000[0x104];
    NetworkReplayBufferView *buffer_104;
    unsigned char reserved_108[0x1c];
    CriticalSectionWrapper critical_124;
};

struct ReplayDecoded256 {
    unsigned int sequence_000;
    unsigned int metadata_004;
    unsigned char tag_008;
    unsigned char count_009;
    short values_00a[123];
};

extern "C" void __cdecl decompress_network_replay(
    const void *source,
    unsigned int source_size,
    void *destination,
    unsigned int destination_size);
extern "C" unsigned char __cdecl compress_network_replay(
    const void *source,
    unsigned int source_size,
    void *destination,
    unsigned int destination_size);
extern "C" int g_replay_request_poll_counter;

ReplayPacketDequeOwner28::~ReplayPacketDequeOwner28()
{
}

unsigned int RequestReplayPacket10::serialize(void *buffer)
{
    unsigned char *output = static_cast<unsigned char *>(buffer);
    output[0] = 11;
    *reinterpret_cast<unsigned int *>(output + 1) = sequence_008;
    output[5] = tag_00c;
    return 6;
}

void RequestReplayPacket10::parse(const unsigned char *input)
{
    sequence_008 = *reinterpret_cast<const unsigned int *>(input + 1);
    tag_00c = input[5];
}

unsigned int InputPacket24::serialize(void *buffer)
{
    unsigned char *output = static_cast<unsigned char *>(buffer);
    *output++ = 3;
    *reinterpret_cast<unsigned int *>(output) = sequence_008;
    output += 4;
    *output++ = tag_00c;
    *output++ = static_cast<unsigned char>(values_010.size());
    if (values_010.size() < 100) {
        unsigned int index = 0;
        if (values_010.size() > 0) {
            ShortDeque20CallView *values =
                reinterpret_cast<ShortDeque20CallView *>(&values_010);
            do {
                *reinterpret_cast<unsigned short *>(output) =
                    static_cast<unsigned short>(values->at(index));
                output += 2;
                ++index;
            } while (index < values_010.size());
        }
    }
    return static_cast<unsigned int>(
        output - static_cast<unsigned char *>(buffer));
}

unsigned int ReplayPacket28::serialize(void *buffer)
{
    unsigned char *output = static_cast<unsigned char *>(buffer);
    output[0] = 9;

    ReplayDecoded256 decoded;
    decoded.sequence_000 = sequence_008;
    decoded.metadata_004 = metadata_00c;
    decoded.tag_008 = tag_010;
    const std::deque<short> &values = values_014;
    decoded.count_009 = static_cast<unsigned char>(values.size());
    short *value = decoded.values_00a;
    unsigned int index = 0;
    if (values.size() > 0) {
        do {
            *value++ = values[index];
            ++index;
        } while (index < values.size());
    }

    unsigned char compressed_size = compress_network_replay(
        &decoded,
        reinterpret_cast<unsigned char *>(value) -
            reinterpret_cast<unsigned char *>(&decoded),
        output + 2,
        254);
    output[1] = compressed_size;
    return compressed_size + 2;
}

void ReplayPacket28::parse_compressed(const unsigned char *input)
{
    ReplayDecoded256 decoded;
    decompress_network_replay(
        input + 2, input[1], &decoded, sizeof(decoded));

    sequence_008 = decoded.sequence_000;
    metadata_00c = decoded.metadata_004;
    tag_010 = decoded.tag_008;
    unsigned char count = decoded.count_009;
    const short *value = decoded.values_00a;
    values_014.clear();
    if (count > 100) {
        sequence_008 = 0;
        metadata_00c = 0;
    } else if (count > 0) {
        int remaining = count;
        do {
            values_014.push_back(*value);
            ++value;
        } while (--remaining != 0);
    }
}

int NetworkClientPacketOwnerView::send_simple_packet(
    PacketSerializeView *packet, int option)
{
    return sender_3b4.send_client(
        packet_buffer_5b4,
        packet->serialize(packet_buffer_5b4),
        option,
        0);
}

void NetworkClientPacketOwnerView::flush_replay_values_44d800()
{
    if (input_sink_6b4 != 0) {
        CriticalSectionWrapper *lock = &replay_critical_0dc;
        lock->enter();
        input_sink_6b4->flush_to(&replay_values_6c8);
        lock->leave();
    }
}

void NetworkClientPacketOwnerView::pump_replay_request_44d880()
{
    if (++g_replay_request_poll_counter % 4 == 0) {
        RequestReplayPacket10 packet;
        packet.tag_00c = expected_tag_6b8;
        packet.sequence_008 = replay_sequence_6bc;
        PacketSerializeView *request =
            reinterpret_cast<PacketSerializeView *>(&packet);
        sender_3b4.send_client(
            packet_buffer_5b4,
            request->serialize(packet_buffer_5b4),
            0x20,
            0);
    }
}

void NetworkClientPacketOwnerView::save_replay_if_enabled_44e2c0()
{
    char path[260];
    if (g_connect_config_ini.has_file_40f0b0(connect_config_file) &&
        g_connect_config_ini.read_uint_40f100(
            connect_config_section, network_save_replay_key)) {
        ScopedNetworkCriticalSection scope(&replay_critical_0dc);
        input_sink_6b4->reset_locked_44d700();
        for (std::deque<short>::iterator it = replay_values_6c8.begin();
             it != replay_values_6c8.end();
             ++it) {
            input_sink_6b4->append_replay_value_42b270(
                static_cast<unsigned short>(*it));
        }
        input_sink_6b4->build_replay_filename_42a560(
            path, player0_name_004, player1_name_024);
        input_sink_6b4->save_replay_428d90(path);
        input_sink_6b4->reset_locked_44d700();
    }
}

void ConnectSessionRuntimeView::apply_profile_44d7d0(
    const char *profile, unsigned char side)
{
    strcpy_s(profile_004, sizeof(profile_004), profile);
    side_3a8 = side;
}

void NetworkReplayStateView::reset_locked_44d700()
{
    ScopedNetworkCriticalSection scope(&critical_124);
    buffer_104->reset_428b70();
}

typedef char InputPacket24_size[
    sizeof(InputPacket24) == 0x24 ? 1 : -1];
typedef char ReplayPacket28_size[
    sizeof(ReplayPacket28) == 0x28 ? 1 : -1];
typedef char ReplayPacketDequeOwner28_size[
    sizeof(ReplayPacketDequeOwner28) == 0x28 ? 1 : -1];
typedef char ReplayDecoded256_size[
    sizeof(ReplayDecoded256) == 0x100 ? 1 : -1];
typedef char NetworkClientPacketOwnerView_replay_offset[
    offsetof(NetworkClientPacketOwnerView, replay_values_6c8) == 0x6c8 ? 1 : -1];
typedef char NetworkReplayStateView_critical_offset[
    offsetof(NetworkReplayStateView, critical_124) == 0x124 ? 1 : -1];

} // namespace th105
