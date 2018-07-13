#include <micrortps/client/core/session/stream_id.h>
#include <micrortps/client/core/serialization/xrce_header.h>

#define BEST_EFFORT_STREAM_THRESHOLD 1
#define RELIABLE_STREAM_THRESHOLD  128

//==================================================================
//                             PUBLIC
//==================================================================
mrStreamId mr_stream_id(uint8_t index, mrStreamType type, mrStreamDirection direction)
{
    mrStreamId stream_id;
    stream_id.direction = direction;
    stream_id.index = index;
    stream_id.type = type;

    switch(type)
    {
        case MR_NONE_STREAM:
            stream_id.raw = index;
            break;
        case MR_BEST_EFFORT_STREAM:
            stream_id.raw = index + BEST_EFFORT_STREAM_THRESHOLD;
            break;
        case MR_RELIABLE_STREAM:
            stream_id.raw = index + RELIABLE_STREAM_THRESHOLD;
            break;
    }

    return stream_id;
}

mrStreamId mr_stream_id_from_raw(uint8_t stream_id_raw, mrStreamDirection direction)
{
    mrStreamId stream_id;
    stream_id.raw = stream_id_raw;
    stream_id.direction = direction;

    if(BEST_EFFORT_STREAM_THRESHOLD > stream_id_raw)
    {
        stream_id.index = stream_id_raw;
        stream_id.type = MR_NONE_STREAM;
    }
    else if(RELIABLE_STREAM_THRESHOLD > stream_id_raw)
    {
        stream_id.index = stream_id_raw - BEST_EFFORT_STREAM_THRESHOLD;
        stream_id.type = MR_BEST_EFFORT_STREAM;
    }
    else
    {
        stream_id.index = stream_id_raw - RELIABLE_STREAM_THRESHOLD;
        stream_id.type = MR_RELIABLE_STREAM;
    }

    return stream_id;
}
