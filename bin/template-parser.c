/*
 * balde: A microframework for C based on GLib and bad intentions.
 * Copyright (C) 2013 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <glib.h>
#include "template-parser.h"


balde_template_block_t*
balde_template_block_new(gchar *content, balde_template_block_type_t type)
{
    balde_template_block_t *block = g_new(balde_template_block_t, 1);
    block->content = g_strdup(content);
    block->type = type;
    return block;
}


GSList*
balde_template_parse(const gchar* content)
{
    GSList *blocks = NULL;
    gchar **pieces1 = g_strsplit(content, "{%", 0);
    for (guint i = 0; pieces1[i] != NULL; i++) {
        gchar **pieces2 = g_strsplit(pieces1[i], "%}", 0);
        for (guint j = 0; pieces2[j] != NULL; j++) {
            gchar **pieces3 = g_strsplit(pieces2[j], "{{", 0);
            for (guint k = 0; pieces3[k] != NULL; k++) {
                gchar **pieces4 = g_strsplit(pieces3[k], "}}", 0);
                for (guint l = 0; pieces4[l] != NULL; l++) {
                    balde_template_block_t *block;
                    if (i > 0 && j == 0 && k == 0 && l == 0)
                        block = balde_template_block_new(g_strstrip(pieces4[l]),
                            BALDE_TEMPLATE_CODE);
                    else if (k > 0 && l == 0)
                        block = balde_template_block_new(g_strstrip(pieces4[l]),
                            BALDE_TEMPLATE_VARIABLE);
                    else
                        block = balde_template_block_new(pieces4[l],
                            BALDE_TEMPLATE_CONTENT);
                    blocks = g_slist_append(blocks, block);
                }
                g_strfreev(pieces4);
            }
            g_strfreev(pieces3);
        }
        g_strfreev(pieces2);
    }
    g_strfreev(pieces1);
    return blocks;
}
