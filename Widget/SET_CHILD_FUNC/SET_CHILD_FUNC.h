#ifndef SET_CHILD_FUNC_H_INCLUDED
#define SET_CHILD_FUNC_H_INCLUDED

typedef struct wd Widget;

_Bool Controle_parente( Widget* pere, Widget* fils);

void set_child_default( Widget* pere, Widget* fils);

void set_child_fenetre( Widget* pere, Widget* fils);

void set_child_actionbar( Widget* pere, Widget* fils);

void set_child_box( Widget* pere, Widget* fils);

void set_child_overlay( Widget* pere,Widget* fils);

void set_child_menubar( Widget* pere,Widget* fils);

void set_child_menuitem( Widget* pere,Widget* fils);

void set_child_menu( Widget* pere,Widget* fils);

void set_child_grid(Widget* pere,Widget* fils);

void set_child_paned(Widget* pere,Widget* fils);

void set_child_notebook( Widget* pere, Widget* fils);

void set_child_stack( Widget* pere, Widget* fils);

void set_child_fixed(Widget* pere,Widget* fils);

void set_child_layout(Widget* pere,Widget* fils);

void set_child_listbox( Widget* pere,Widget* fils);

void set_child_flowbox( Widget* pere,Widget* fils);

void set_child_toolbar( Widget* pere,Widget* fils);

#endif // SET_CHILD_FUNC_H_INCLUDED
