/*
 *  Copyright (C) 2012-2014 Skylable Ltd. <info-copyright@skylable.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  Special exception for linking this software with OpenSSL:
 *
 *  In addition, as a special exception, Skylable Ltd. gives permission to
 *  link the code of this program with the OpenSSL library and distribute
 *  linked combinations including the two. You must obey the GNU General
 *  Public License in all respects for all of the code used other than
 *  OpenSSL. You may extend this exception to your version of the program,
 *  but you are not obligated to do so. If you do not wish to do so, delete
 *  this exception statement from your version.
 */

#ifndef HASHOP_H
#define HASHOP_H
#include "../../../libsx/src/sxproto.h"
#include "../../../libsx/src/cluster.h"

typedef int (*hash_presence_cb_t)(const char *hash, unsigned idx, int code, void *context);
struct sxi_hashop {
  sxi_conns_t *conns;
  int queries;
  int finished;
  int ok;
  int enoent;
  int cb_fail;
  hash_presence_cb_t cb;
  void *context;
  enum sxi_hashop_kind kind;
  const char *current_host;
  unsigned int current_blocksize;
  char hexhashes[DOWNLOAD_MAX_BLOCKS * HASH_TEXT_LEN + 1];
  char hashes[DOWNLOAD_MAX_BLOCKS * (HASH_TEXT_LEN + EXPIRE_TEXT_LEN) + 1];
  unsigned hashes_count;
  unsigned hashes_pos;
  int64_t expires_at;
  char id[HASH_TEXT_LEN+1];
};

void sxi_hashop_begin(sxi_hashop_t *a, sxi_conns_t *conns, int64_t expires_at, hash_presence_cb_t cb, enum sxi_hashop_kind kind, const sx_hash_t *idhash, void *context);
int sxi_hashop_batch_add(sxi_hashop_t *a, const char *host, int64_t expires_at, unsigned idx, const unsigned char *binhash, unsigned int blocksize);
int sxi_hashop_batch_flush(sxi_hashop_t *a);
int sxi_hashop_end(sxi_hashop_t *a);
#endif
