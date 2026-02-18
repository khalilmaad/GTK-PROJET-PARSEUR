#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"

// =============================================
// Fonctions pour la pile
// =============================================

void pile_push(ParserXML* parser, Widget* widget) {
    if (!parser || !widget) return;

    StackNode* node = malloc(sizeof(StackNode));
    if (!node) return;

    node->widget = widget;
    node->next = parser->pile_widget;
    parser->pile_widget = node;
}

Widget* pile_top(ParserXML* parser) {
    if (!parser || !parser->pile_widget) return NULL;
    return parser->pile_widget->widget;
}

void pile_pop(ParserXML* parser) {
    if (!parser || !parser->pile_widget) return;

    StackNode* temp = parser->pile_widget;
    parser->pile_widget = parser->pile_widget->next;
    free(temp);
}

_Bool pile_empty(ParserXML* parser) {
    return parser->pile_widget == NULL;
}

void pile_clear(ParserXML* parser) {
    while (!pile_empty(parser)) {
        pile_pop(parser);
    }
}

