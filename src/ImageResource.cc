/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright (C) 2005-2006  Guido de Jong <guidoj@users.sf.net>
 */

#include "Exception.h"
#include "ImageResource.h"

ImageResource::ImageResource()
: numImages(0)
{
}

ImageResource::~ImageResource()
{
  for (std::vector<Image*>::iterator it = images.begin(); it != images.end(); ++it) {
    delete (*it);
  }
  images.clear();
}

unsigned int
ImageResource::GetNumImages() const
{
  return numImages;
}

Image *
ImageResource::GetImage(unsigned int n) const
{
  return images[n];
}

void
ImageResource::Load(FileBuffer *buffer)
{
  try {
    if (buffer->GetUint16() != 0x1066 ) {
      throw DataCorruption("ImageResource::Load");
    }
    unsigned int compression = (unsigned int)buffer->GetUint16();
    numImages = (unsigned int)buffer->GetUint16();
    unsigned int *imageSize = new unsigned int[numImages];
    unsigned int *imageFlags = new unsigned int[numImages];
    buffer->Skip(2);
    unsigned int size = buffer->GetUint32();
    for (unsigned int i = 0; i < numImages; i++) {
      imageSize[i] = (unsigned int)buffer->GetUint16();
      imageFlags[i] = (unsigned int)buffer->GetUint16();
      unsigned int width;
      unsigned int height;
      width = (unsigned int)buffer->GetUint16();
      height = (unsigned int)buffer->GetUint16();
      Image *img = new Image(width, height);
      images.push_back(img);
    }
    FileBuffer *decompressed = new FileBuffer(size);
    buffer->Decompress(decompressed, compression);
    for (unsigned int i = 0; i < numImages; i++) {
      FileBuffer *imageBuffer = new FileBuffer(imageSize[i]);
      imageBuffer->Fill(decompressed);
      (images[i])->Load(imageBuffer, imageFlags[i]);
      delete imageBuffer;
    }
    delete decompressed;
    delete[] imageFlags;
    delete[] imageSize;
  } catch (Exception &e) {
    e.Print("ImageResource::Load");
  }
}

