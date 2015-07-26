/***
    This file is part of snapcast
    Copyright (C) 2015  Johannes Pohl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include <memory>

#include "message/pcmChunk.h"
#include "message/header.h"
#include "message/sampleFormat.h"


class Encoder;

class EncoderListener
{
public:
	virtual void onChunkEncoded(const Encoder* encoder, msg::PcmChunk* chunk, double duration) = 0;
};



class Encoder
{
public:
	Encoder(const std::string& codecOptions = "") : headerChunk_(NULL), codecOptions_(codecOptions)
	{
	}

	virtual ~Encoder()
	{
		if (headerChunk_ != NULL)
			delete headerChunk_;
	}

	virtual void init(EncoderListener* listener, const msg::SampleFormat& format)
	{
		if (codecOptions_ == "")
			codecOptions_ = getDefaultOptions();
		listener_ = listener;
		sampleFormat_ = format;
		initEncoder();
	}

	virtual void encode(const msg::PcmChunk* chunk) = 0;

	virtual std::string name() const = 0;

	virtual std::string getAvailableOptions() const
	{
		return "No codec options supported";
	}

	virtual std::string getDefaultOptions() const
	{
		return "";
	}

	virtual msg::Header* getHeader() const
	{
		return headerChunk_;
	}

protected:
	virtual void initEncoder() = 0;

	msg::SampleFormat sampleFormat_;
	msg::Header* headerChunk_;
	EncoderListener* listener_;
	std::string codecOptions_;
};


#endif


