/*
 * balde: A microframework for C based on GLib and bad intentions.
 * Copyright (C) 2013-2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <glib.h>
#include <balde-template/template-private.h>
#include <balde-template/parser-private.h>


void
test_template_generate_source_without_vars(void)
{
    gchar *rv = balde_template_generate_source("bola", "ads qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads qwe\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup(balde_template_bola_format);\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_single_var(void)
{
    gchar *rv = balde_template_generate_source("bola", "ads {{ guda }} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s qwe\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_single_var_with_includes(void)
{
    gchar *rv = balde_template_generate_source("bola",
        "ads {{ guda }} qwe\n"
        "\n"
        "         {% include \"bola.h\" %}\n"
        "{% include \"bola/guda.h\" %}\n");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "#include <bola.h>\n"
        "#include <bola/guda.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s qwe\\n\\n         \\n\\n\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_multiple_vars(void)
{
    gchar *rv = balde_template_generate_source("bola",
        "ads {{ guda }} {{ bola }} {{balde}} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s %s %s qwe\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"),\n"
        "        balde_response_get_tmpl_var(response, \"bola\"),\n"
        "        balde_response_get_tmpl_var(response, \"balde\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_multiple_vars_and_lines(void)
{
    gchar *rv = balde_template_generate_source("bola",
        "ads {{ guda }}\n"
        "\n"
        "{{ bola }}\n"
        "{{balde}} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s\\n\\n%s\\n%s qwe\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"),\n"
        "        balde_response_get_tmpl_var(response, \"bola\"),\n"
        "        balde_response_get_tmpl_var(response, \"balde\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_multiple_vars_and_lines_with_function_calls(void)
{
    gchar *rv = balde_template_generate_source("bola",
        "ads {{ guda }}\n"
        "\n"
        "{{ bola() }}\n"
        "\n"
        "{{ chunda(quico, \"cola\", -2, 1.5, \"chaves\", TRUE, popis) }} {{ asd(\"XD\") }}\n"
        "{{balde}} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ads %s\\n\\n%s\\n\\n%s %s\\n%s qwe\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *a1 = balde_tmpl_bola(app, request);\n"
        "    gchar *a2 = balde_tmpl_chunda(app, request,\n"
        "        balde_response_get_tmpl_var(response, \"quico\"),\n"
        "        \"cola\",\n"
        "        -2,\n"
        "        1.5,\n"
        "        \"chaves\",\n"
        "        TRUE,\n"
        "        balde_response_get_tmpl_var(response, \"popis\"));\n"
        "    gchar *a3 = balde_tmpl_asd(app, request,\n"
        "        \"XD\");\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"),\n"
        "        a1,\n"
        "        a2,\n"
        "        a3,\n"
        "        balde_response_get_tmpl_var(response, \"balde\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(a1);\n"
        "    g_free(a2);\n"
        "    g_free(a3);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_source_with_percent(void)
{
    gchar *rv = balde_template_generate_source("bola", "ad %s % {{ guda }} qwe");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#include <balde.h>\n"
        "#include <glib.h>\n"
        "\n"
        "static const gchar *balde_template_bola_format = \"ad %%s %% %s qwe\";\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "void\n"
        "balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response)\n"
        "{\n"
        "    gchar *rv = g_strdup_printf(balde_template_bola_format,\n"
        "        balde_response_get_tmpl_var(response, \"guda\"));\n"
        "    balde_response_append_body(response, rv);\n"
        "    g_free(rv);\n"
        "}\n");
    g_free(rv);
}


void
test_template_generate_header(void)
{
    gchar *rv = balde_template_generate_header("bola");
    g_assert_cmpstr(rv, ==,
        "// WARNING: this file was generated automatically by balde-template-gen\n"
        "\n"
        "#ifndef __bola_balde_template\n"
        "#define __bola_balde_template\n"
        "\n"
        "#include <balde.h>\n"
        "\n"
        "extern void balde_template_bola(balde_app_t *app, balde_request_t *request, "
        "balde_response_t *response);\n"
        "\n"
        "#endif\n");
    g_free(rv);
}


void
test_template_get_name(void)
{
    gchar *rv = balde_template_get_name("bola.guda.ação.html");
    g_assert_cmpstr(rv, ==, "bola_guda_a____o");
    g_free(rv);
}


void
balde_assert_template_include(GSList *l, const gchar *include)
{
    balde_template_block_t *node = l->data;
    g_assert(node->type == BALDE_TEMPLATE_INCLUDE_BLOCK);
    balde_template_include_block_t *block = node->block;
    g_assert_cmpstr(block->include, ==, include);
}


void
balde_assert_template_content(GSList *l, const gchar *content)
{
    balde_template_block_t *node = l->data;
    g_assert(node->type == BALDE_TEMPLATE_CONTENT_BLOCK);
    balde_template_content_block_t *block = node->block;
    g_assert_cmpstr(block->content, ==, content);
}


void
balde_assert_template_print_var(GSList *l, const gchar *variable)
{
    balde_template_block_t *node = l->data;
    g_assert(node->type == BALDE_TEMPLATE_PRINT_VAR_BLOCK);
    balde_template_print_var_block_t *block = node->block;
    g_assert_cmpstr(block->variable, ==, variable);
}


void
balde_assert_template_print_function_call(GSList *l, const gchar *name, ...)
{
    va_list args;
    va_start(args, name);
    balde_template_block_t *node = l->data;
    g_assert(node->type == BALDE_TEMPLATE_PRINT_FN_CALL_BLOCK);
    balde_template_print_fn_call_block_t *block = node->block;
    g_assert_cmpstr(block->name, ==, name);
    for (GSList *tmp = block->args; tmp != NULL; tmp = g_slist_next(tmp))
        g_assert_cmpstr(((balde_template_fn_arg_t*) tmp->data)->content, ==,
            va_arg(args, const gchar*));
    va_end(args);
}


void
test_template_parse(void)
{
    GSList *blocks = balde_template_parse(
        "Test\n"
        "\n"
        "   {% include \"bola.h\" %}\n"
        "foo {{ bola(gude, TRUE, 1.5, -2, \"chun\\\"da\", FALSE, xd, +5, \"\") }}\n"
        "  {{ test }} \n"
        "bola\n");
    g_assert(blocks != NULL);
    balde_assert_template_content(blocks, "Test\n\n   ");
    balde_assert_template_include(blocks->next, "bola.h");
    balde_assert_template_content(blocks->next->next, "\nfoo ");
    balde_assert_template_print_function_call(blocks->next->next->next, "bola",
        "gude", "TRUE", "1.5", "-2", "\"chun\\\"da\"", "FALSE", "xd", "+5", "\"\"");
    balde_assert_template_content(blocks->next->next->next->next, "\n  ");
    balde_assert_template_print_var(blocks->next->next->next->next->next, "test");
    balde_assert_template_content(blocks->next->next->next->next->next->next,
        " \nbola\n");
    g_assert(blocks->next->next->next->next->next->next->next == NULL);
    balde_template_free_blocks(blocks);
}


int
main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/template/generate_source_without_vars",
        test_template_generate_source_without_vars);
    g_test_add_func("/template/generate_source_single_var",
        test_template_generate_source_single_var);
    g_test_add_func("/template/generate_source_single_var_with_includes",
        test_template_generate_source_single_var_with_includes);
    g_test_add_func("/template/generate_source_multiple_vars",
        test_template_generate_source_multiple_vars);
    g_test_add_func("/template/generate_source_multiple_vars_and_lines",
        test_template_generate_source_multiple_vars_and_lines);
    g_test_add_func("/template/generate_source_multiple_vars_and_lines_with_function_calls",
        test_template_generate_source_multiple_vars_and_lines_with_function_calls);
    g_test_add_func("/template/generate_source_with_percent",
        test_template_generate_source_with_percent);
    g_test_add_func("/template/generate_header",
        test_template_generate_header);
    g_test_add_func("/template/get_name", test_template_get_name);
    g_test_add_func("/template/parse", test_template_parse);
    return g_test_run();
}
