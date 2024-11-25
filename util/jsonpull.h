/* SPDX-FileCopyrightText: 2024 Greenbone AG
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef _GVM_JSONPULL_H
#define _GVM_JSONPULL_H

#define _GNU_SOURCE

#include "json.h"

#include <glib.h>
#include <stdio.h>

/**
 * @brief Type of container the parser is currently in
 */
typedef enum
{
  GVM_JSON_PULL_CONTAINER_NONE = 0, ///< No container / document root
  GVM_JSON_PULL_CONTAINER_ARRAY,    ///< Array
  GVM_JSON_PULL_CONTAINER_OBJECT,   ///< Object
} gvm_json_pull_container_type_t;

/**
 * @brief Path element types for the JSON pull parser.
 */
typedef struct gvm_json_path_elem
{
  gvm_json_pull_container_type_t parent_type; ///< parent container type
  int index; ///< Index of the element within the parent
  char *key; ///< Key if element is in an object
  int depth; ///< Number of ancestor elements
} gvm_json_path_elem_t;

/**
 * @brief Event types for the JSON pull parser
 */
typedef enum
{
  GVM_JSON_PULL_EVENT_UNDEFINED = 0,
  GVM_JSON_PULL_EVENT_ARRAY_START,
  GVM_JSON_PULL_EVENT_ARRAY_END,
  GVM_JSON_PULL_EVENT_OBJECT_START,
  GVM_JSON_PULL_EVENT_OBJECT_END,
  GVM_JSON_PULL_EVENT_STRING,
  GVM_JSON_PULL_EVENT_NUMBER,
  GVM_JSON_PULL_EVENT_BOOLEAN,
  GVM_JSON_PULL_EVENT_NULL,
  GVM_JSON_PULL_EVENT_EOF,
  GVM_JSON_PULL_EVENT_ERROR,
} gvm_json_pull_event_type_t;

/**
 * @brief Event generated by the JSON pull parser.
 */
typedef struct
{
  gvm_json_pull_event_type_t type; ///< Type of event
  GQueue *path;                    ///< Path to the event value
  cJSON *value;                    ///< Value for non-container value events
  gchar *error_message;            ///< Error message, NULL on success
} gvm_json_pull_event_t;

/**
 * @brief Expected token state for the JSON pull parser
 */
typedef enum
{
  GVM_JSON_PULL_EXPECT_UNDEFINED = 0, ///< Undefined state
  GVM_JSON_PULL_EXPECT_VALUE,         ///< Expect start of a value
  GVM_JSON_PULL_EXPECT_KEY,           ///< Expect start of a key
  GVM_JSON_PULL_EXPECT_COMMA,         ///< Expect comma or container end brace
  GVM_JSON_PULL_EXPECT_EOF            ///< Expect end of file
} gvm_json_pull_expect_t;

#define GVM_JSON_PULL_PARSE_BUFFER_LIMIT 10485760

#define GVM_JSON_PULL_READ_BUFFER_SIZE 4096

/**
 * @brief A json pull parser
 */
typedef struct
{
  GQueue *path;                   ///< Path to the current value
  gvm_json_path_elem_t *path_add; ///< Path elem to add in next step
  gvm_json_pull_expect_t expect;  ///< Current expected token
  int keyword_pos;           ///< Position in a keyword like "true" or "null"
  FILE *input_stream;        ///< Input stream
  char *read_buffer;         ///< Stream reading buffer
  size_t read_buffer_size;   ///< Size of the stream reading buffer
  size_t last_read_size;     ///< Size of last stream read
  int last_read_char;        ///< Character last read from stream
  size_t read_pos;           ///< Position in current read
  GString *parse_buffer;     ///< Buffer for parsing values and object keys
  size_t parse_buffer_limit; ///< Maximum parse buffer size
} gvm_json_pull_parser_t;

gvm_json_path_elem_t *
gvm_json_pull_path_elem_new (gvm_json_pull_container_type_t, int);

void
gvm_json_pull_path_elem_free (gvm_json_path_elem_t *);

void
gvm_json_pull_event_init (gvm_json_pull_event_t *);

void
gvm_json_pull_event_cleanup (gvm_json_pull_event_t *);

void
gvm_json_pull_parser_init_full (gvm_json_pull_parser_t *, FILE *, size_t,
                                size_t);

void
gvm_json_pull_parser_init (gvm_json_pull_parser_t *, FILE *);

void
gvm_json_pull_parser_cleanup (gvm_json_pull_parser_t *);

void
gvm_json_pull_parser_next (gvm_json_pull_parser_t *, gvm_json_pull_event_t *);

cJSON *
gvm_json_pull_expand_container (gvm_json_pull_parser_t *, gchar **);

gchar *
gvm_json_path_to_string (GQueue *path);

#endif /* _GVM_JSONPULL_H */
