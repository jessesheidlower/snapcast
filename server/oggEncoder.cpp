#include "oggEncoder.h"

OggEncoder::OggEncoder()
{
}


void OggEncoder::encode(Chunk* chunk)
{
	WireChunk* wireChunk = chunk->wireChunk;
	for (size_t n=0; n<wireChunk->length; ++n)
		wireChunk->payload[n] *= 1.5;
//	return chunk;
}




