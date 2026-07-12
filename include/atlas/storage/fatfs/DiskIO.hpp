#pragma once

#include <atlas/storage/sd/SDCard.hpp>
#include <diskio.h>
#include <ff.h>

namespace atlas::storage::fatfs
{

void Initialize(sd::SDCard& card);

}