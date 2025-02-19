/* SPDX-FileCopyrightText: 2013-2023 Greenbone AG
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

/**
 * @file
 * @brief API related to data compression (gzip format.)
 */

#ifndef _GVM_COMPRESSUTILS_H
#define _GVM_COMPRESSUTILS_H

#include <stdio.h>

void *
gvm_compress (const void *, unsigned long, unsigned long *);

void *
gvm_compress_gzipheader (const void *, unsigned long, unsigned long *);

void *
gvm_uncompress (const void *, unsigned long, unsigned long *);

FILE *
gvm_gzip_open_file_reader (const char *);

FILE *
gvm_gzip_open_file_reader_fd (int);

#endif /* not _GVM_COMPRESSUTILS_H */
