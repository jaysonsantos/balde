/*
 * balde: A microframework for C based on GLib and bad intentions.
 * Copyright (C) 2013 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

#ifndef _BIN_BALDE_TEMPLATE_PARSER
#define _BIN_BALDE_TEMPLATE_PARSER

#include <glib.h>

typedef enum {
    BALDE_TEMPLATE_CONTENT,
    BALDE_TEMPLATE_CODE,
    BALDE_TEMPLATE_VARIABLE
} balde_template_block_type_t;

typedef struct {
    gchar *content;
    balde_template_block_type_t type;
} balde_template_block_t;

balde_template_block_t* balde_template_block_new(gchar *content, balde_template_block_type_t type);
GSList* balde_template_parse(const gchar* content);

#endif /* _BIN_BALDE_TEMPLATE_PARSER */
